#pragma once
#include"Common.hpp"
#include"Maze.hpp"

//オプションシーン
class Option : public App::Scene
{
public:

	Option(const InitData& init);

	void update() override;//上書き

	void draw() const override;


private:

	// INIファイル
	// INI ファイルからデータを読み込む
	INI Matching_ini{ U"config.ini" };

	// Lose_Audioの番号
	uint8 Matching_Audio_BGM_num;

	// 大ボタン	
	Rect Big_Button{ Arg::center = Scene::Center().movedBy(0, 0), 300, 60 };	// ボタンの位置設定
	Transition Big_GameTransition{ 0.4s, 0.2s };	// ボタンのトランザクションを設定

	// 中ボタン	
	Rect Medium_Button{ Arg::center = Scene::Center().movedBy(0, 100), 300, 60 };	// ボタンの位置設定
	Transition Medium_GameTransition{ 0.4s, 0.2s };	// ボタンのトランザクションを設定

	// 小ボタン	
	Rect Small_Button{ Arg::center = Scene::Center().movedBy(0, 200), 300, 60 };	// ボタンの位置設定
	Transition Small_GameTransition{ 0.4s, 0.2s };	// ボタンのトランザクションを設定

	//次のシーンへ行くボタン
	// 小ボタン	
	Rect Next_Button{ Arg::center = Scene::Center().movedBy(100, 300), 300, 60 };	// ボタンの位置設定
	Transition Next_GameTransition{ 0.4s, 0.2s };	// ボタンのトランザクションを設定

	Font font = Font(20);
	Vec2 center = Scene::Center();
	std::map<char,std::pair<int,bool>> Roomnums;

	std::map<char,std::pair<int,bool>> getRoomNum()
	{
		Array<String> NameList = net->getRoomNameList();
		Array<int> PlayerNum = net->getRoomplayernum();
		std::map<char, std::pair<int, bool>> Roomnum;
		Roomnum['B']=std::make_pair(0,false);
		Roomnum['M']= std::make_pair(0, false);
		Roomnum['S']= std::make_pair(0, false);
		for(const auto i:step(NameList.size()))
		{
			if(NameList[i][0]=='B')
			{
				Roomnum['B'].first++;
				if (PlayerNum[i] == 1)
				{
					Roomnum['B'].second = true;
				}
			}
			else if (NameList[i][0] == 'M')
			{
				Roomnum['M'].first++;
				if (PlayerNum[i] == 1)
				{
					Roomnum['M'].second = true;
				}
			}
			else if (NameList[i][0] == 'S')
			{
				Roomnum['S'].first++;
				if (PlayerNum[i] == 1)
				{
					Roomnum['S'].second = true;
				}
			}
		}

		return Roomnum;
	}
};
