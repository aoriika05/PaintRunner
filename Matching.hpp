//マッチング画面
#pragma once

#include "Common.hpp"
#include "Maze.hpp"
#include "RLE.hpp"

class Matching :public App::Scene
{
public:
	Matching(const InitData& init);

	void update() override;

	void draw() const override;

private:

	// INIファイル
	// INI ファイルからデータを読み込む
	INI Matching_ini{ U"config.ini" };

	// Lose_Audioの番号
	uint8 Matching_Audio_BGM_num;

	//サーバーとの通信状況を表示
	void Print_NetworkData();

	//部屋の最大人数
	const static int maxplayer = 2;

	bool IsOnce = true;
	bool IsMatching=false;
	Font font = Font(50);
	Font playerfont = Font(20);
	Vec2 center = Scene::Center();
	RLE rle;

	// GUI
		//
	Font Match_MatchNow_font{ 50,Typeface::Bold };

	// 文字格納
	String Match_MatchNow;

	// 文字カウント
	double text_time = 0;

	// ボタン	
	RoundRect Match_Button{ Arg::center = Scene::Center().movedBy(0, 100), 200, 40, 20 };	// ボタンの位置設定

	// フラグ
	int Match_Flag;

	String check=U"aiueo";

	Array<String> NGwords =
	{
		U"6f0c60289458eda3058f109bc0158a16",U"87c1d0dd27660e803ffd6def29f9eb52 ",U"f058fe16f0a9ab0347930b59d6a3f407",U"b744f59ab860c62af9a85c19ee384e00",U"15c2b53459e6de75d1374a8c43ae8852",U"f99a051efaa495510167b788a715f0c4",U"362d2b9b785fd325e5410711bacc9185"
		U"ff84b78673dea73ac2dc6efa2e39751d",U"db07b81e6c8b488b9bfee4220d8ee57f",U"d15c08adfa6597ede530f3c2c8fdc30c",U"ee3b5af81e1cf6975634514cd7864a20",U"03b7506ef94c967a55ff9979a167eded",U"3a9f0d5d62725d7347c03671e9dd8dac",U"959dd0b4770693db3f6a9ee0b178d8dc",
		U"03b7506ef94c967a55ff9979a167eded",U"32f584e8e71dd0c63d0652e1be157a3a",U"f8dabf9b9b53edf3d17275c0d77cc61c",U"7b9bc94dcecf553295661ebb5469d07c",U"97347d4acc5438859ee863fa055268a5",U"55875c390147f16586557738f7582ff9",U"4e03a68016fa985f2909a05d32557e19",
		U"dc80f0a9174fa9c0ca84a80b79b5e349",U"a91a0e1ca1b7cbd539927bf308b66362"
	};

	inline bool isNGword(String PName);
};

bool Matching::isNGword(String PName)
{
	if (PName.size() < 1 || PName.size() > 6)
	{
		return true;
	}

	for (const auto P : PName)
	{
		if (!isalpha(P))
		{
			return true;
		}
	}

	PName.lowercase();

	for (int i = PName.size(); i > 0; i--)
	{
		for (int j = 0; j < PName.size() - i + 1; j++)
		{
			for (const auto& NG : NGwords)
			{
				if (MD5::FromText(PName.substr(j, i)).asString() == NG)
				{
					return true;
				}
			}
		}
	}

	return false;
}
