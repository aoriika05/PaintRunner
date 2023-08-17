#pragma once
# include "Common.hpp"

// タイトルシーン
class SoundBox : public App::Scene
{
public:

	SoundBox(const InitData& init);

	~SoundBox();

	void update() override;//上書き

	void draw() const override;


private:

	// INIファイル
	// INI ファイルからデータを読み込む
	INI SoundBox_ini{ U"config.ini" };


	// メニュー選択
	// 選択中のMenu番号
	uint8 SoundBox_Menu_Select;

	// 選択中ののkey番号
	uint8 SoundBox_Key_Select[7];


	// Audio
	// 現在再生中のMenu番号
	uint8 SoundBox_Menu_Select_Now;

	// 現在再生中ののkey番号
	uint8 SoundBox_Key_Select_Now[7];

	// Menu名
	String Audio_Menu[7];

	// 曲名
	String Audio_name[7][4];

	// 作曲者
	String Audio_Writer[7][4];

	// 引用元
	String Audio_References[7][4];


	// 関数
	//
	void Audio_ALL_Stop();
};
