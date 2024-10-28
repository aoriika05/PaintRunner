#pragma once
# include "Common.hpp"

// タイトルシーン
class About : public App::Scene
{
public:

	About(const InitData& init);

	void update() override;//上書き

	void draw() const override;

	// メニュー選択
	// Menu番号の最大値
	uint8 About_Menu_Max = 8;


private:

	// INIファイル
	// INI ファイルからデータを読み込む
	INI About_ini{ U"config.ini" };


	// メニュー選択
	// 選択中のMenu番号
	uint8 About_Menu_Select;


	// Audioの設定
	// Audioの番号
	uint8 About_Audio_BGM_num;
};
