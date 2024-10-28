# include "Result.hpp"

Result::Result(const InitData& init)
	: IScene{ init }
{
	// INIファイル
	// 全てのセクションを列挙
	for (const auto& section : Result_ini.sections())
	{
		if (section.section == U"Audio")	// Audioセクション
		{
			// セクション内のすべてのキーを列挙
			for (const auto& key : section.keys)
			{
				if (key.name == U"Result_Win_BGM")	// ResultWinキー
				{
					Result_Audio_WinBGM_num = Parse<uint8>(key.value);
				}
				else if (key.name == U"Result_Lose_BGM")
				{
					Result_Audio_LoseBGM_num = Parse<uint8>(key.value);
				}
			}
		}
	}


	// 文字格納
	Result_Who_Win = String{ U"...." };


	// ストップウォッチ
	Result_stopwatch = Stopwatch{ StartImmediately::Yes };


	// Player1,Player2の総合スコア
	// リセット
	Result_TotalScore_Player1 = 0;
	Result_TotalScore_Player2 = 0;

	// マス目カウント
	for (auto i : step(getData().ClearMaze.width()))
	{
		for (auto j : step(getData().ClearMaze.height()))
		{
			if (getData().ClearMaze[i][j] == 3)
			{
				Result_TotalScore_Player1++;
			}
			else if (getData().ClearMaze[i][j] == 4)
			{
				Result_TotalScore_Player2++;
			}
		}
	}

	// ボーナスポイント
	if (getData().goal[0] != getData().goal[1])
	{
		Result_TotalScore_Player1 += (Result_Bonus_Point * getData().goal[0]);
		Result_TotalScore_Player2 += (Result_Bonus_Point * getData().goal[1]);
	}

	// Bar計算
	// Player1とPlayer2の合計スコア
	Result_TotalScore_Player1_and_2 = Result_TotalScore_Player1 + Result_TotalScore_Player2;

	// Player1のパーセント
	Result_percent_Player1 = double(Result_TotalScore_Player1) / Result_TotalScore_Player1_and_2;

	// Player2のパーセント
	Result_percent_Player2 = double(Result_TotalScore_Player2) / Result_TotalScore_Player1_and_2;

	// 勝利者
	if (Result_TotalScore_Player1 > Result_TotalScore_Player2)
	{
		if (getData().pnum == 1)
		{
			Result_Winner = 1;
		}
		else if (getData().pnum == 2)
		{
			Result_Winner = 2;
		}
	}
	else if (Result_TotalScore_Player1 < Result_TotalScore_Player2)
	{
		if (getData().pnum == 1)
		{
			Result_Winner = 2;
		}
		else if (getData().pnum == 2)
		{
			Result_Winner = 1;
		}
	}
	else if (Result_TotalScore_Player1 == Result_TotalScore_Player2)
	{
		Result_Winner = 0;
	}


	// Game時間
	// Player1のゲーム時間
	Result_GameTime_Player1 = getData().ClearTime[0];

	// Player2のゲーム時間
	Result_GameTime_Player2 = getData().ClearTime[1];

	// 合計プレイ時間
	if (getData().goal[0] * getData().goal[1] == 1)	// AND
	{
		if (Result_GameTime_Player1 >= Result_GameTime_Player2)
		{
			Result_GameTime_All = Result_GameTime_Player1;
		}
		else
		{
			Result_GameTime_All = Result_GameTime_Player2;
		}
	}
	else if (getData().goal[0] + getData().goal[1] == 0)	// NOR
	{
		// Gameの最大時間
		Result_GameTime_All = int(getData().ChangeMaze.size());
	}
	else
	{
		if (getData().goal[0])
		{
			if (Result_GameTime_Player1 + Result_Time_Countdown < getData().ChangeMaze.size())
			{
				// 1Pのクリア時間+その後のカウントダウン
				Result_GameTime_All = Result_GameTime_Player1 + Result_Time_Countdown;
			}
			else
			{
				// Gameの最大時間
				Result_GameTime_All = getData().ChangeMaze.size();
			}
		}
		else
		{
			if (Result_GameTime_Player2 + Result_Time_Countdown < getData().ChangeMaze.size())
			{
				// 2Pのクリア時間+その後のカウントダウン
				Result_GameTime_All = Result_GameTime_Player2 + Result_Time_Countdown;
			}
			else
			{
				// Gameの最大時間
				Result_GameTime_All = getData().ChangeMaze.size();
			}
		}
	}


	// Map
	// Mapのドットサイズ
	Result_Map_DotSize = 350 / (double)getData().maze.width();

	// Map1マスの描画時間
	Result_GameTime_Dot = Resukt_Bar_END / Result_GameTime_All;
	}

Result::~Result()
{


}

void Result::update()
{
	// 音楽
	if (Result_Winner == 0 || Result_Winner == 1)
	{
		// 曲が流れてるか判定
		if (AudioAsset(U"Result_Win_BGM" + Format(Result_Audio_WinBGM_num)).isPlaying() == false)
		{
			if (Result_stopwatch.sF() > Resukt_Bar_END)
			{
				AudioAsset(U"Result_Win_BGM" + Format(Result_Audio_WinBGM_num)).play(MixBus0);
			}
		}
		else
		{
			if (Result_stopwatch.sF() <= Resukt_Bar_END)
			{
				AudioAsset(U"Result_Win_BGM" + Format(Result_Audio_WinBGM_num)).stop();
			}
		}
	}
	else if (Result_Winner == 2)
	{
		// 曲が流れてるか判定
		if (AudioAsset(U"Result_Lose_BGM" + Format(Result_Audio_LoseBGM_num)).isPlaying() == false)
		{
			if (Result_stopwatch.sF() > Resukt_Bar_END)
			{
				AudioAsset(U"Result_Lose_BGM" + Format(Result_Audio_LoseBGM_num)).play(MixBus0);
			}
		}
		else
		{
			if (Result_stopwatch.sF() <= Resukt_Bar_END)
			{
				AudioAsset(U"Result_Lose_BGM" + Format(Result_Audio_LoseBGM_num)).stop();
			}
		}
	}


	// Enterで
	if (KeyEnter.down() && Result_stopwatch.sF() > Resukt_Bar_END)
	{
		// 音楽停止
		AudioAsset(U"Result_Win_BGM" + Format(Result_Audio_WinBGM_num)).stop();
		AudioAsset(U"Result_Lose_BGM" + Format(Result_Audio_LoseBGM_num)).stop();

		net->opLeaveRoom();

		// タイトルシーンに遷移
		changeScene(State::Title);
	}

	if (net != nullptr)
	{
		net->update();
	}
}

void Result::draw() const
{
	// 名前の表示
	if (getData().pnum == 1)
	{
		FontAsset(U"Medium_50")(getData().UserName).drawAt(100, 50);
		FontAsset(U"Medium_50")(getData().Opponent_name).drawAt(700, 50);
	}
	else if (getData().pnum == 2)
	{
		FontAsset(U"Medium_50")(getData().UserName).drawAt(700, 50);
		FontAsset(U"Medium_50")(getData().Opponent_name).drawAt(100, 50);
	}


	// 勝ち負けの表示
	if (Result_stopwatch.sF() > 1.0 && Result_stopwatch.sF() < Resukt_Bar_END)
	{
		FontAsset(U"Medium_75")(Result_Who_Win.substr(0, static_cast<size_t>((Result_stopwatch.sF() - 1.0) / (Resukt_Bar_END / 4)))).drawAt(400, 50);
	}
	else if (Result_stopwatch.sF() > Resukt_Bar_END)
	{
		if (Result_Winner == 0)	// 引き分け
		{
			FontAsset(U"Medium_75")(U"Drow").drawAt(400, 50);
		}
		else if (Result_Winner == 1)	// 勝利時
		{
			FontAsset(U"Medium_75")(U"Win").drawAt(400, 50);
		}
		else if (Result_Winner == 2)	// 敗北時
		{
			FontAsset(U"Medium_75")(U"Lose").drawAt(400, 50);
		}
	}


	// 経過時間の表示
	if (Result_stopwatch.sF() > Resukt_Bar_END)
	{
		// 左の人
		if (getData().goal[0])
		{
			FontAsset(U"Medium_40")(Format(Result_GameTime_Player1 / 60) + U" : " + U"{:0>2}"_fmt(Format(Result_GameTime_Player1 % 60))).drawAt(100, 210);
		}
		else
		{
			FontAsset(U"Medium_40")(U"Over").drawAt(100, 210);
		}
		// 右の人
		if (getData().goal[1])
		{
			FontAsset(U"Medium_40")(Format(Result_GameTime_Player2 / 60) + U" : " + U"{:0>2}"_fmt(Format(Result_GameTime_Player2 % 60))).drawAt(700, 210);
		}
		else
		{
			FontAsset(U"Medium_40")(U"Over").drawAt(700, 210);
		}
	}


	// ScoreBar
	// ScoreBarそのもの
	RoundRect{ Arg::center(400, 150), 400, 60, 10 }.draw(Color(0, 0, 0, 127)).drawFrame(0, 3, Color(0, 0, 0, 255));

	// 最初のスライド(暗転終了(1.0[s])から途中停止(3.5[s])まで)
	if (Result_stopwatch.sF() > 1.0 && Result_stopwatch.sF() < Resukt_Bar_END - 0.25)
	{
		// 左の人
		RoundRect{ 200, 120, 40 * (Result_stopwatch.sF() - 1.0), 60, 10 }.draw(Color(255, 0, 0, 127));
		// 右の人
		RoundRect{ 600 - 40 * (Result_stopwatch.sF() - 1.0), 120, 40 * (Result_stopwatch.sF() - 1.0), 60, 10 }.draw(Color(0, 0, 255, 127));

		// Barのポイント
		// 左の人
		FontAsset(U"Medium_40")(Format(int(20 * (Result_stopwatch.sF() - 1.0))) + U"pt").drawAt(100, 150);
		// 右の人
		FontAsset(U"Medium_40")(Format(int(20 * (Result_stopwatch.sF() - 1.0))) + U"pt").drawAt(700, 150);
	}
	else if (Result_stopwatch.sF() > Resukt_Bar_END - 0.25 && Result_stopwatch.sF() < Resukt_Bar_END)
	{
		// Barの中身
		// 左の人
		RoundRect{ 200, 120, (((Result_percent_Player1 * 400) - 100) * ((Result_stopwatch.sF() - 3.5) * 4) + 100), 60, 10 }.draw(Color(255, 0, 0, 127));
		// 右の人
		RoundRect{ 600 - (((Result_percent_Player2 * 400) - 100) * ((Result_stopwatch.sF() - 3.5) * 4) + 100), 120, (((Result_percent_Player2 * 400) - 100) * ((Result_stopwatch.sF() - 3.5) * 4) + 100), 60, 10 }.draw(Color(0, 0, 255, 127));

		// Barのポイント
		// 左の人
		FontAsset(U"Medium_40")(Format(int(((Result_TotalScore_Player1 - 50) * ((Result_stopwatch.sF() - 3.5) * 4)) + 50)) + U"pt").drawAt(100, 150);
		// 右の人
		FontAsset(U"Medium_40")(Format(int(((Result_TotalScore_Player2 - 50) * ((Result_stopwatch.sF() - 3.5) * 4)) + 50)) + U"pt").drawAt(700, 150);
	}
	else if (Result_stopwatch.sF() > Resukt_Bar_END)
	{
		// Barの中身
		// 左の人
		RoundRect{ 200, 120, (Result_percent_Player1 * 400), 60, 10 }.draw(Color(0, 0, 255, 127));
		// 右の人
		RoundRect{ 600 - (Result_percent_Player2 * 400), 120, (Result_percent_Player2 * 400), 60, 10 }.draw(Color(255, 0, 0, 127));

		// 左の人
		FontAsset(U"Medium_40")(Format(Result_TotalScore_Player1) + U"pt").drawAt(100, 150);
		// 右の人
		FontAsset(U"Medium_40")(Format(Result_TotalScore_Player2) + U"pt").drawAt(700, 150);
	}


	// Map表示
	// 全体マップの表示場所
	Rect(Arg::center(400, 400), 400, 400).draw(Color(139, 69, 19, 255));

	// 全体マップ
	// 外枠フレーム
	RectF(400 - (double)getData().ClearMaze.width() / 2 * Result_Map_DotSize,
	400 - (double)getData().ClearMaze.width() / 2 * Result_Map_DotSize, Result_Map_DotSize * getData().ClearMaze.width(),
	Result_Map_DotSize * getData().ClearMaze.height()).drawFrame(0, Result_Map_DotSize / 2, Palette::Black);

	// Mapの中身
	if (Result_stopwatch.sF() <= Resukt_Bar_END)
	{
		for (auto i : step(getData().ClearMaze.width()))
		{
			for (auto j : step(getData().ClearMaze.height()))
			{
				if (getData().ChangeMaze[int(Result_stopwatch.sF() / Result_GameTime_Dot)][i][j] == 0)	// 塗られていない床
				{
					RectF(400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + i * Result_Map_DotSize,
						400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + j * Result_Map_DotSize,
						Result_Map_DotSize, Result_Map_DotSize).draw(Palette::White);
				}
				else if (getData().ChangeMaze[int(Result_stopwatch.sF() / Result_GameTime_Dot)][i][j] == 1)	// 壁
				{
					RectF(400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + i * Result_Map_DotSize,
						400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + j * Result_Map_DotSize,
						Result_Map_DotSize, Result_Map_DotSize).draw(Palette::Brown);
				}
				else if (getData().ChangeMaze[int(Result_stopwatch.sF() / Result_GameTime_Dot)][i][j] == 2)	// ゴール
				{
					RectF(400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + i * Result_Map_DotSize,
						400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + j * Result_Map_DotSize,
						Result_Map_DotSize, Result_Map_DotSize).draw(Palette::Gold);
				}
				else if (getData().ChangeMaze[int(Result_stopwatch.sF() / Result_GameTime_Dot)][i][j] == 3)	// 青の塗ったマス
				{
					RectF(400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + i * Result_Map_DotSize,
						400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + j * Result_Map_DotSize,
						Result_Map_DotSize, Result_Map_DotSize).draw(Palette::Blue);
				}
				else if (getData().ChangeMaze[int(Result_stopwatch.sF() / Result_GameTime_Dot)][i][j] == 4)	// 赤の塗ったマス
				{
					RectF(400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + i * Result_Map_DotSize,
						400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + j * Result_Map_DotSize,
						Result_Map_DotSize, Result_Map_DotSize).draw(Palette::Red);
				}
			}
		}
	}
	else
	{
		for (auto i : step(getData().ClearMaze.width()))
		{
			for (auto j : step(getData().ClearMaze.height()))
			{
				if (getData().ClearMaze[i][j] == 0)	// 塗られていない床
				{
					RectF(400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + i * Result_Map_DotSize,
						400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + j * Result_Map_DotSize,
						Result_Map_DotSize, Result_Map_DotSize).draw(Palette::White);
				}
				else if (getData().ClearMaze[i][j] == 1)	// 壁
				{
					RectF(400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + i * Result_Map_DotSize,
						400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + j * Result_Map_DotSize,
						Result_Map_DotSize, Result_Map_DotSize).draw(Palette::Brown);
				}
				else if (getData().ClearMaze[i][j] == 2)	// ゴール
				{
					RectF(400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + i * Result_Map_DotSize,
						400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + j * Result_Map_DotSize,
						Result_Map_DotSize, Result_Map_DotSize).draw(Palette::Gold);
				}
				else if (getData().ClearMaze[i][j] == 3)	// 青の塗ったマス
				{
					RectF(400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + i * Result_Map_DotSize,
						400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + j * Result_Map_DotSize,
						Result_Map_DotSize, Result_Map_DotSize).draw(Palette::Blue);
				}
				else if (getData().ClearMaze[i][j] == 4)	// 赤の塗ったマス
				{
					RectF(400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + i * Result_Map_DotSize,
						400 - getData().ClearMaze.width() / (double)2 * Result_Map_DotSize + j * Result_Map_DotSize,
						Result_Map_DotSize, Result_Map_DotSize).draw(Palette::Red);
				}
			}
		}
	}


	// Item
	// 上が数 下が画像
	if (Result_stopwatch.sF() > 3.75)
	{
		for (int i = 0; i < 6; i++)
		{
			// 左の人
			FontAsset(U"Medium_40")(U"    :  " + Format(getData().Used1[i])).drawAt(100, 275 + i * 50);
			TextureAsset(U"Item_Image" + Format(i)).resized(45).drawAt(50, 275 + i * 50);

			// 右の人
			FontAsset(U"Medium_40")(U"    :  " + Format(getData().Used2[i])).drawAt(700, 275 + i * 50);
			TextureAsset(U"Item_Image" + Format(i)).resized(45).drawAt(650, 275 + i * 50);
		}
	}


	// MenuBar
	// Exitキー
	// 文字
	if (Result_stopwatch.sF() > 3.75)
	{
		FontAsset(U"Medium_40")(U"EXIT").drawAt(Scene::Center().movedBy(300, 275), Color{ 255, 255, 255, 255 });
	}
	else
	{
		FontAsset(U"Medium_40")(U"EXIT").drawAt(Scene::Center().movedBy(300, 275), Color{ 255, 255, 255, 127 });
	}
}
