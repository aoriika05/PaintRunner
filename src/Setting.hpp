#pragma once
# include "Common.hpp"

// タイトルシーン
class Setting : public App::Scene
{
public:

	Setting(const InitData& init);

	void update() override;//上書き

	void draw() const override;

	// メニュー選択
	// Menu番号の最大値
	uint8 Setting_Menu_Max = 7;

private:

	// INIファイル
	// INI ファイルからデータを読み込む
	INI Setting_ini{ U"config.ini" };


	// スクリーン
	// 変更可能なウィンドウサイズ
	Array<Vec2> Setting_Windows_Size;

	// Window倍率
	double Setting_Windows_Magnification;

	// 利用可能なスクリーンサイズ
	Vec2 Setting_workArea;

	// FullScreanの設定
	bool Setting_Fullscreen = false;


	// メニュー選択
	// 選択中のMenu番号
	uint8 Setting_Menu_Select;

	// 現在の選択中のウィンドウサイズの番号
	uint8 Setting_Window_Size_num;


	// Audioの設定
	// Audioの番号
	uint8 Setting_Audio_BGM_num;
};
