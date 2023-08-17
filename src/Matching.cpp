#include "Matching.hpp"
#include "Maze.hpp"

Matching::Matching(const InitData& init)
	: IScene(init)
{
	// INIファイル
	// 全てのセクションを列挙
	for (const auto& section : Matching_ini.sections())
	{
		if (section.section == U"Audio")	// Audioセクション
		{
			// セクション内のすべてのキーを列挙
			for (const auto& key : section.keys)
			{
				if (key.name == U"Matching_BGM")	// Matchingキー
				{
					Matching_Audio_BGM_num = Parse<uint8>(key.value);
				}
			}
		}
	}

	net->ResetData();
	Print << U"迷路作成中";

	//if (getData().maze.isEmpty())
	{
		Maze maze(MazeSize);
		getData().maze = maze.coordinate;
	}

	ClearPrint();

	IsMatching = false;
	
	// GUI
	// マッチング文字
	Match_MatchNow = String{ U"マッチング中・・・" };

}

void Matching::update()
{
	// 音楽
	// 曲が流れてるか判定
	if (AudioAsset(U"Matching_BGM" + Format(Matching_Audio_BGM_num)).isPlaying() == false)
	{
		AudioAsset(U"Matching_BGM" + Format(Matching_Audio_BGM_num)).play(MixBus0);
	}

	if (net != nullptr)
	{
		//ClearPrint();
		if (!IsMatching)
		{
			if (Match_Button.leftClicked() && !net->IsPressed)
			{
				net->joinwithSize();
				net->IsPressed = true;
			}
			
			//オプションシーンへ戻る
			if (SimpleGUI::Button(U"←", Vec2(30, 30), unspecified, !net->IsPressed))
			{
				changeScene(State::Option);
			}
		}

		if (net->isInRoom())
		{
			if (Match_Button.leftClicked()&& net->getPlayerCountInCurrentRoom()==1)
			{
				net->opLeaveRoom();
				net->IsPressed = false;
			}
		}

		if (net->errorconnect && Match_Button.leftClicked())
		{
			net->connect();
		}

		//部屋の参加人数が二人ならシーン遷移
		if (net->getPlayerCountInCurrentRoom() == 2&&IsOnce)
		{
			AudioAsset(U"Matching_BGM" + Format(Matching_Audio_BGM_num)).stop();
			if (net->isMasterClient())
			{
				net->opRaiseEvent(1, rle.make(getData().maze,getData().maze.size().x, getData().maze.size().y));

				if (isNGword(getData().UserName))
				{
					getData().UserName = U"NG";
				}

				net->opRaiseEvent(2, getData().UserName);
				net->map.gridinport(getData().maze);
				IsOnce = false;
				changeScene(State::Game);
			}else if (net->maze&&net->EnemyPlayerName)
			{
				getData().maze = net->maze.value();

				if (isNGword(getData().UserName))
				{
					getData().UserName = U"NG";
				}

				net->opRaiseEvent(2, getData().UserName);
				net->map.gridinport(getData().maze);
				IsOnce = false;
				changeScene(State::Game);
			}
			IsMatching = true;
		}

		if (KeyEnter.pressed())
		{
			Print_NetworkData();
		}

		if (Match_Button.mouseOver())
		{
			if (net->getPlayerCountInCurrentRoom() != 2)
				Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (Match_Button.mouseOver())
		{
			if (net->getPlayerCountInCurrentRoom() != 2)
				Cursor::RequestStyle(CursorStyle::Hand);
		}

		net->update();
	}

	// k
	text_time += Scene::DeltaTime();
	if (static_cast<size_t>(text_time / 0.2) >= Match_MatchNow.size())
	{
		text_time = 0;
	}
	// k
}

void Matching::draw() const
{
	// 背景設定
	// 背景色設定
	Scene::SetBackground(ColorF(0.3, 0.4, 0.5));

	if (net != nullptr)
	{
		if (net->isInRoom())
		{
			if (net->getPlayerCountInCurrentRoom() == 1)
			{
				// メインメッセージ
				Match_MatchNow_font(Match_MatchNow.substr(0, static_cast<size_t>(text_time / 0.2))).draw(175, 100);

				// ぐるぐる
				Circle(center, 30).drawArc(Scene::Time() * 140_deg, 240_deg, 0, 20, ColorF(0.4));

				// Cancelボタン
				Match_Button.draw(ColorF{ 1.0, 1.0, 1.0, 1.0 });
				FontAsset(U"Medium_15")(U"キャンセル").drawAt(Match_Button.center(), ColorF{ 0, 0, 0, 1.0 });
			}
			else if (net->getPlayerCountInCurrentRoom() == 2)
			{
				font(U"対戦相手が見つかりました").drawAt(center);
			}
		}
		else
		{
			if (net->errorconnect)
			{
				// メインメッセージ
				font(U"サーバーへの接続に失敗しました").drawAt(400, 135);

				// Reconnectボタン
				Match_Button.draw(ColorF{ 1.0, 1.0, 1.0, 1.0 });
				FontAsset(U"Medium_15")(U"再接続").drawAt(Match_Button.center(), ColorF{ 0, 0, 0, 1.0 });
			}
			else if (!net->isconnect)
			{
				// メインメッセージ
				font(U"サーバーに接続中です").drawAt(400, 135);
			}
			else if (net->isconnect)
			{
				// メインメッセージ
				//font(U"サーバーに接続完了しました").drawAt(400, 135);

				// MatchStartボタン
				Match_Button.draw(ColorF{ 1.0, 1.0, 1.0, 1.0 });
				FontAsset(U"Medium_15")(U"マッチング開始").drawAt(Match_Button.center(), ColorF{ 0, 0, 0, 1.0 });
			}
		}
	}
}



void Matching::Print_NetworkData()
{
	Console.writeln();
	Console << U"getRoomNameList: {}"_fmt(net->getRoomNameList());
	Console << U"getName: {}"_fmt(net->getName());
	Console << U"isInRoom: {}"_fmt(net->isInRoom());
	Console << U"getCurrentRoomName: {}"_fmt(net->getCurrentRoomName());
	Console << U"getPlayerCountInCurrentRoom: {}"_fmt(net->getPlayerCountInCurrentRoom());
	Console << U"getMaxPlayersInCurrentRoom: {}"_fmt(net->getMaxPlayersInCurrentRoom());
	Console << U"getIsOpenInCurrentRoom: {}"_fmt(net->getIsOpenInCurrentRoom());
	Console << U"localPlayerID: {}"_fmt(net->localPlayerID());
	Console << U"isMasterClient: {}"_fmt(net->isMasterClient());
	Console << U"getNumber: {}"_fmt(net->getNumber());
}
