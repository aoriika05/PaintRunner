# pragma once
# include "Common.hpp"
// タイトルシーン
class Title : public App::Scene
{
public:

	Title(const InitData& init);

	void update() override;//上書き

	void draw() const override;

	// メニュー選択
	// Menu番号の最大値
	uint8 Title_Menu_Max = 4;

private:
	// メニュー選択
	// 選択中のMenu番号
	uint8 Title_Menu_Select;

	// Audioの設定
	// Audioの番号
	uint8 Title_Audio_BGM_num;
};
