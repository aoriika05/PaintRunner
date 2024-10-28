# pragma once
# include "Common.hpp"

// リザルトシーン
class Result : public App::Scene
{
public:

	Result(const InitData& init);

	~Result();

	void update() override;

	void draw() const override;
	
	// ゴールできない罰則
	int Result_Bonus_Point = 100;

	// 片方がゴールしてからのカウントダウン
	int Result_Time_Countdown = 30;

	// 勝敗表示までの時間
	double Resukt_Bar_END = 3.75;

private:

	// INIファイル
	// INI ファイルからデータを読み込む
	INI Result_ini{ U"config.ini" };


	// Audioの設定
	// Win_Audioの番号
	uint8 Result_Audio_WinBGM_num;

	// Lose_Audioの番号
	uint8 Result_Audio_LoseBGM_num;


	// result描画
	// ストップウォッチ
	Stopwatch Result_stopwatch;


	// 勝利者・バー描画
	// 勝利したプレイヤー
	int Result_Winner;

	// 文字格納
	String Result_Who_Win;

	// Player1の総合スコア
	int Result_TotalScore_Player1;

	// Player2の総合スコア
	int Result_TotalScore_Player2;

	// Player1とPlayer2の合計スコア
	int Result_TotalScore_Player1_and_2;

	// Player1のパーセント
	double Result_percent_Player1;

	// Player2のパーセント
	double Result_percent_Player2;


	// ゲーム時間
	// Player1のゲーム時間
	int Result_GameTime_Player1;

	// Player2のゲーム時間
	int Result_GameTime_Player2;

	// ゲームプレイ時間
	int Result_GameTime_All;


	// Map描画
	// Mapのドットサイズ
	double Result_Map_DotSize;

	// Map1マスの描画時間
	double Result_GameTime_Dot;
};
