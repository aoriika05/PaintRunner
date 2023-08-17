#pragma once
# include "Common.hpp"

// タイトルシーン
class Howtoplay : public App::Scene
{
public:

	Howtoplay(const InitData& init);

	void update() override;//上書き

	void draw() const override;

	// メニュー選択
	// Menu番号の最大値
	uint8 Howtoplay_Menu_Max = 6;

private:

	// INIファイル
	// INI ファイルからデータを読み込む
	INI Howtoplay_ini{ U"config.ini" };


	// メニュー選択
	// 選択中のMenu番号
	uint8 Howtoplay_Menu_Select;


	// Audioの設定
	// Audioの番号
	uint8 Howtoplay_Audio_BGM_num;
};
