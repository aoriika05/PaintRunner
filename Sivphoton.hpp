#pragma once
#include "NetworkSystem.hpp"
#include "Multiplayer_Photon.hpp"
#include "Maze.hpp"
#include "RLE.hpp"
#include "Common.hpp"
#include "mapinfo.hpp"

//通信用クラスを継承して、自分用にカスタマイズしたやつ
class MyNetwork : public SivPhoton
{
public:
	using SivPhoton::SivPhoton;

	//接続の結果
	void connectReturn(int32 errorCode, const String& errorString, const String& region, const String& cluster) override
	{
		if (Set_Val::Output_Print)
		{
			Print << U"MyNetwork::connectReturn() [サーバへの接続に成功したときに(?) 呼ばれる]";
			Print << U"- error: " << errorString;
			Print << U"- region: " << region;
			Print << U"- cluster [サブ的な region]: " << cluster;
		}

		if (errorCode)
		{
			return;
		}

		isconnect = true;
		errorconnect = false;
	}

	//サーバーへの接続が失敗したら呼ばれる
	void connectionErrorReturn(const int32 errorCode) override
	{
		if (Set_Val::Output_Print)
		{
			Print << U"MyNetwork::connectionErrorReturn() [サーバへの接続が失敗したときに呼ばれる]";
			Print << U"errorCode: " << errorCode;
		}
		errorconnect = true;
	}

	//ランダムな部屋に入る、部屋がなければ作る
	void joinRandomRoomReturn(const int32 localPlayerID, const int32 errorCode, const String& errorString) override
	{
		if (Set_Val::Output_Print)
		{
			Print << U"MyNetwork::joinRandomRoomReturn() [既存のランダムなルームに参加した結果を処理する]";
			Print << U"- localPlayerID [失敗した場合は 0 (?)]: " << localPlayerID;
			Print << U"- errorCode: " << errorCode;
			Print << U"- errorString: " << errorString;
		}

		if (errorCode == NetworkSystem::NoRandomMatchFound) // 100% こうなるはず
		{
			if (Set_Val::Output_Print)
			{
				Print << U"[既存のルームが見つからなかった]";
			}

			const String roomName = m_defaultRoomName;

			// 自分でルームを新規作成する
			this->opCreateRoom(roomName, MaxPlayers);
		}
	}

	//void SivPhoton::opJoinRandomRoom(const int32 maxPlayers)
	//{
	//	if (Set_Val::Output_Print)
	//	{
	//		Print << U"SivPhoton::opJoinRandomRoom(maxPlayers = {}) [既存のランダムなルームに参加する]"_fmt(maxPlayers);
	//	}

	//	assert(InRange(maxPlayers, 0, 255));

	//	m_client->opJoinRandomRoom({}, static_cast<uint8>(Clamp(maxPlayers, 1, 255)));
	//}

	void joinwithSize(const Size size=MazeSize)
	{
		String::value_type sizechr;

		if (size == Size{73,73})
		{
			sizechr = 'B';
		}
		else if (size == Size{ 51,51 })
		{
			sizechr = 'M';
		}
		else if (size == Size{ 41,41 })
		{
			sizechr = 'S';
		}
		else
		{
			//throw Error(U"想定していない迷路のサイズが指定されました :{},{}行目"_fmt(__FILE__,__LINE__));
			return;
		}

		Array<String> NameList = getRoomNameList();
		Array<int> PlayerNums = getRoomplayernum();

		for(const auto i:step(NameList.size()))
		{
			if(sizechr==NameList[i][0]&&PlayerNums[i]==1)
			{
				opJoinRoom(NameList[i]);
				return;
			}
		}

		for(const int i:step(256))
		{
			int Randomnum = Random(0, 256);
			bool IsUnique=true;
			for (const auto j : step(NameList.size()))
			{
				if(NameList[j][0]==sizechr&&Randomnum== Parse<int>(NameList[j].substr(1, NameList[j].size())))
				{
					IsUnique == false;
				}
			}
			if(IsUnique==true)
			{
				opCreateRoom(sizechr + U"{}"_fmt(Randomnum),MaxPlayers);
				return;
			}
		}
	}

	//部屋に入った結果
	void joinRoomReturn(int32 localPlayerID, int32 errorCode, const String& errorString) override
	{
		if (Set_Val::Output_Print)
		{
		Print << U"MyNetwork::joinRoomReturn() [指定したルームに参加した結果を処理する]";
		Print << U"- localPlayerID [失敗した場合は 0 (?)]: " << localPlayerID;
		Print << U"- errorCode: " << errorCode;
		Print << U"- errorString: " << errorString;
		}

		if (errorCode)
		{
			if (Set_Val::Output_Print)
			{
				Print << U"[指定したルームに参加できなかった]";
			}
			IsPressed = false;
			return;
		}

		if (Set_Val::Output_Print)
		{
			Print << U"[指定したルームに参加できた]";
		}
	}

	//String型を受け取ったときに呼ばれる関数
	/// @brief 受信のコード(サンプル)
	/// @param playerID 送信したプレイヤーのID
	/// @param eventCode イベントコード(番号によって意味を持たせたい場合有用)
	/// @param eventContent 受信した本体
	void customEventAction(const int32 playerID, const int32 eventCode, const String& eventContent) override
	{
		RLE rle;
		if (eventCode == 1)
		{
			int a, b;
			maze = rle.reverse(eventContent, MazeSize.x, MazeSize.y, &a, &b);
			maze.value()[a][b] = 2;
		}

		if (eventCode == 2)
		{
			EnemyPlayerName = eventContent;
		}

		if(eventCode==55)
		{
			int a, b;
			EnemyMapState = rle.reverse(eventContent, MazeSize.x, MazeSize.y, &a, &b);
		}
	}

	void customEventAction(const int32 playerID, const int32 eventCode,const int32 eventContent) override
	{
		if (eventCode == 1) {
			StartTiming=eventContent+1;
		}

		if (eventCode == 100) {
			SpeedDown = eventContent;
		}

		if (eventCode == 200) {
			VisionDown = eventContent;
		}

		if (eventCode == 300) {
			UsedItem = eventContent;
		}

	}

	void customEventAction(const int32 playerID, const int32 eventCode, const bool eventContent) override
	{
		if (eventCode == 1)
		{
			EnemyGoalFrag = eventContent;
			return;
		}

		if(eventCode==2)
		{
			EnableWarp = eventContent;
		}
	}

	//double型を受け取ったときに呼ばれる関数
	/// @brief 受信のコード(サンプル)
	/// @param playerID 送信したプレイヤーのID
	/// @param eventCode イベントコード(番号によって意味を持たせたい場合有用)
	/// @param eventContent 受信した本体
	void customEventAction(const int32 playerID, const int32 eventCode, const double eventContent) override
	{
		if (eventCode == 1)
		{
			StartTiming = eventContent + 1000;
		}
	}

	//Size型を受け取ったときに呼ばれる関数
	/// @brief 受信のコード(Gridサンプル)
	/// @param playerID 送信したプレイヤーのID
	/// @param eventCode イベントコード(番号によって意味を持たせたい場合有用)
	/// @param eventContent 受信した本体
	void customEventAction(const int32 playerID, const int32 eventCode, const Size& eventContent) override
	{
		if (eventCode == 1)
		{
			enpositons.push_front(eventContent);
		}
		
		if(InRange(LagStopwatch.ms(),30,60))
		{
			syncPlayerPos();
		}

		if (enpositons.size() > 2)
		{
			LagStopwatch.restart();
		}
	}

	/// @brief 受信のコード(Gridサンプル)
	/// @param playerID 送信したプレイヤーのID
	/// @param eventCode イベントコード(番号によって意味を持たせたい場合有用)
	/// @param eventContent 受信した本体
	void customEventAction(const int32 playerID, const int32 eventCode, const Grid<double>& eventContent) override
	{
		if (Set_Val::Output_Print)
		{
			Print << U"MyNetwork::customEventAction(Grid<double>)";
			Print << U"playerID: " << playerID;
			Print << U"eventCode: " << eventCode;
			Print << U"eventContent: " << eventContent;
		}
	}

	void customEventAction(const int32 playerID, const int32 eventCode, const Array<int32>& eventContent) override
	{
		if (eventCode == 11) {
			UsedItem1 = eventContent;
		}

		if (eventCode == 12) {
			UsedItem2 = eventContent;
		}
		//map.chgtile(eventContent, false);
	}

	void customEventAction(const int32 playerID, const int32 eventCode, const Grid<int32>& eventContent) override
	{
		if(eventCode==1)
		{
			EnemyMapState = eventContent;
		}
	}

	// サンプル（誰か入ってきたら退室）
	//void joinRoomEventAction(int32 localPlayerID, const Array<int>& playerIDs, bool isSelf) override
	//{
	//	if (isSelf) // 自分だったら
	//	{
	//		return;
	//	}

	//	constexpr bool willComeBack = true;

	//	this->opLeaveRoom(willComeBack);
	//}

	//接続が切れたときに呼ばれる
	void disconnectReturn() override
	{
		isconnect = false;
		IsPressed = false;
		connect();
	}

	//部屋から出たときに呼ばれる
	void leaveRoomReturn(int32 errorCode, const String& errorString) override
	{
		IsPressed = false;
	}

	//誰かが部屋から出たら呼ばれる
	void leaveRoomEventAction(int32 playerID, bool isInactive) override
	{
		opLeaveRoom();
		IsPressed = false;
		ResetData();
	}

	//共有しているデータの初期化
	void ResetData()
	{
		LagStopwatch.reset();
		enpositons.clear();
		IsPressed = false;
		StartTiming = none;
		EnemyGoalFrag = false;
		EnableWarp = false;
		maze = none;
		VisionDown = 0;
		SpeedDown = 0;
		UsedItem1 = {0,0,0,0,0,0};
		UsedItem2 = { 0,0,0,0,0,0 };
		UsedItem = 0;
		enemypos = Size{ 0,0 };
		map.pointreset();
		EnemyMapState = none;
		EnemyPlayerName = none;
	}
	
	//共有するデータ
	Size enemypos;
	bool isconnect = false;
	bool IsPressed = false;
	bool errorconnect = false;
	bool EnemyGoalFrag = false;
	bool EnableWarp = false;
	int SpeedDown = 0;
	int VisionDown = 0;
	int UsedItem = 0;
	Array<int> UsedItem1 = {0,0,0,0,0,0};
	Array<int> UsedItem2 = { 0,0,0,0,0,0 };
	Stopwatch LagStopwatch;
	Array<Size> enpositons;
	Optional<double> StartTiming=none;
	Optional<Grid<int>> maze;
	Mapinfo map;
	Optional<Grid<int>> EnemyMapState=none;
	Optional<String> EnemyPlayerName = none;

private:

	//最大人数
	static constexpr int32 MaxPlayers = 2;

	void syncPlayerPos()
	{
		if(isMasterClient())
		{
			//迷路情報を送り出す
		}
	}
};

class MyNetWorkV2 : public Multiplayer_Photon
{
public:
	using Multiplayer_Photon::Multiplayer_Photon;
};
