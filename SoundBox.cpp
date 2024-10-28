# include "SoundBox.hpp"

SoundBox::SoundBox(const InitData& init)
	: IScene{ init }
{
	// INIファイル
	// 全てのセクションを列挙
	for (const auto& section : SoundBox_ini.sections())
	{
		if (section.section == U"Audio")	// Audioセクション
		{
			// セクション内のすべてのキーを列挙
			for (const auto& key : section.keys)
			{
				if (key.name == U"Title_BGM")	// Title_BGMキー
				{
					// Title_BGMの設定を引き継ぐ
					SoundBox_Key_Select[0] = Parse<uint8>(key.value);
					SoundBox_Key_Select_Now[0] = SoundBox_Key_Select[0];
				}
				else if (key.name == U"Setting_BGM")	// Setting_BGMキー
				{
					// Setting_BGMの設定を引き継ぐ
					SoundBox_Key_Select[1] = Parse<uint8>(key.value);
					SoundBox_Key_Select_Now[1] = SoundBox_Key_Select[1];
				}
				else if (key.name == U"Result_Win_BGM")	// Result_Win_BGMキー
				{
					// Setting_BGMの設定を引き継ぐ
					SoundBox_Key_Select[2] = Parse<uint8>(key.value);
					SoundBox_Key_Select_Now[2] = SoundBox_Key_Select[2];
				}
				else if (key.name == U"Result_Lose_BGM")	// Result_Lose_BGMキー
				{
					// Setting_BGMの設定を引き継ぐ
					SoundBox_Key_Select[3] = Parse<uint8>(key.value);
					SoundBox_Key_Select_Now[3] = SoundBox_Key_Select[3];
				}
				else if (key.name == U"Match_BGM")	// Match_BGMキー
				{
					// Setting_BGMの設定を引き継ぐ
					SoundBox_Key_Select[4] = Parse<uint8>(key.value);
					SoundBox_Key_Select_Now[4] = SoundBox_Key_Select[4];
				}
				else if (key.name == U"Game_BGM")	// Setting_BGMキー
				{
					// Setting_BGMの設定を引き継ぐ
					SoundBox_Key_Select[5] = Parse<uint8>(key.value);
					SoundBox_Key_Select_Now[5] = SoundBox_Key_Select[1];
				}
			}
		}
	}


	// メニュー選択
	// 選択中のMenu番号
	SoundBox_Menu_Select = 0;
	SoundBox_Menu_Select_Now = SoundBox_Menu_Select;


	// Menu名
	Audio_Menu[0] = U"Title_BGM";
	Audio_Menu[1] = U"Setting_BGM";
	Audio_Menu[2] = U"Result_Win_BGM";
	Audio_Menu[3] = U"Result_Lose_BGM";
	Audio_Menu[4] = U"Matching_BGM";
	Audio_Menu[5] = U"Game_BGM";
	Audio_Menu[6] = U"GameSE";


	// 曲名
	//Audio_name[0][0] = U"Pink_Pico_Planet";
	//Audio_Writer[0][0] = U"強化トカゲ";
	//Audio_References[0][0] = U"https://dova-s.jp/bgm/play15882.html";

	Audio_name[0][1] = U"Pink_Pico_Planet_2";
	Audio_Writer[0][1] = U"強化トカゲ";
	Audio_References[0][1] = U"https://dova-s.jp/bgm/play15882.html";

	//Audio_name[0][2] = U"ワクワクアリクイ";
	//Audio_Writer[0][2] = U"かずち";
	//Audio_References[0][2] = U"https://dova-s.jp/bgm/play3347.html";

	Audio_name[1][0] = U"休日ショッピング的なBGM";
	Audio_Writer[1][0] = U"鷹尾まさき(タカオマサキ)";
	Audio_References[1][0] = U"https://dova-s.jp/bgm/play2883.html";

	//Audio_name[1][1] = U"休日ショッピング的なBGM_2";
	//Audio_Writer[1][1] = U"鷹尾まさき(タカオマサキ)";
	//Audio_References[1][1] = U"https://dova-s.jp/bgm/play2883.html";

	//Audio_name[1][2] = U"8bit_Game_Menu";
	//Audio_Writer[1][2] = U"スエノブ";
	//Audio_References[1][2] = U"https://dova-s.jp/bgm/play1444.html";

	Audio_name[2][0] = U"Trick_style";
	Audio_Writer[2][0] = U"まんぼう二等兵";
	Audio_References[2][0] = U"https://dova-s.jp/bgm/play10385.html";

	Audio_name[3][0] = U"DUB_MACHINE_1";
	Audio_Writer[3][0] = U"OK-Sounds";
	Audio_References[3][0] = U"https://dova-s.jp/bgm/play3814.html";

	Audio_name[4][0] = U"超使いやすいドラム&ベース無限BGM";
	Audio_Writer[4][0] = U"Hupple";
	Audio_References[4][0] = U"https://dova-s.jp/bgm/play12790.html";

	//Audio_name[4][1] = U"超使いやすいドラム&ベース無限BGM_2";
	//Audio_Writer[4][1] = U"Hupple";
	//Audio_References[4][1] = U"https://dova-s.jp/bgm/play12790.html";

	//Audio_name[5][0] = U"サイバーポップ";
	//Audio_Writer[5][0] = U"マニーラ";
	//Audio_References[5][0] = U"https://dova-s.jp/bgm/play15425.html";

	Audio_name[5][1] = U"サイバーポップ_2";
	Audio_Writer[5][1] = U"マニーラ";
	Audio_References[5][1] = U"https://dova-s.jp/bgm/play15425.html";

	Audio_name[6][0] = U"se_magic_tititi";
	Audio_Writer[6][0] = U"効果音工房";
	Audio_References[6][0] = U"https://umipla.com/soundeffect/1172";

	Audio_name[6][1] = U"se_magic_effect1";
	Audio_Writer[6][1] = U"効果音工房";
	Audio_References[6][1] = U"https://umipla.com/soundeffect/1400";

	Audio_name[6][2] = U"se_down";
	Audio_Writer[6][2] = U"効果音工房";
	Audio_References[6][2] = U"https://umipla.com/soundeffect/932";
	

	// 全音楽終了
	Audio_ALL_Stop();
}

SoundBox::~SoundBox()
{

}

void SoundBox::update()
{
	// Menu
// 項目選択
// 上キー
	if (KeyUp.down())
	{
		if (SoundBox_Menu_Select > 0)
		{
			SoundBox_Menu_Select = SoundBox_Menu_Select - 1;
		}
	}

	// 下キー
	if (KeyDown.down())
	{
		if (SoundBox_Menu_Select < 7)
		{
			SoundBox_Menu_Select = SoundBox_Menu_Select + 1;
		}
	}


	// 音楽
	switch (SoundBox_Menu_Select)
	{
	case 0:

		if (KeyEnter.down())
		{
			// TiTle_BGMが流れてるか判定
			if (AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).isPlaying() == false)
			{
				// 音楽を変える
				Audio_ALL_Stop();
				AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).play(MixBus0);


				// 現在の音楽情報を変える
				SoundBox_Key_Select_Now[SoundBox_Menu_Select] = SoundBox_Key_Select[SoundBox_Menu_Select];
				SoundBox_Menu_Select_Now = SoundBox_Menu_Select;
			}
		}
		/*
		// 右キー
		if (KeyRight.down())
		{
			// 上限を超えていないとき
			if (SoundBox_Key_Select[SoundBox_Menu_Select] < 2)
			{
				// 足す
				SoundBox_Key_Select[SoundBox_Menu_Select]++;
			}
		}

		// 左キー
		if (KeyLeft.down())
		{
			// 下限を超えていないとき
			if (SoundBox_Key_Select[SoundBox_Menu_Select] > 0)
			{
				// 減らす
				SoundBox_Key_Select[SoundBox_Menu_Select]--;
			}
		}
		*/
		break;
		
	case 1:
		if (KeyEnter.down())
		{
			// TiTle_BGMが流れてるか判定
			if (AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).isPlaying() == false)
			{
				// 音楽を変える
				Audio_ALL_Stop();
				AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).play(MixBus0);


				// 現在の音楽情報を変える
				SoundBox_Key_Select_Now[SoundBox_Menu_Select] = SoundBox_Key_Select[SoundBox_Menu_Select];
				SoundBox_Menu_Select_Now = SoundBox_Menu_Select;
			}
		}
		/*
		// 右キー
		if (KeyRight.down())
		{
			// 上限を超えていないとき
			if (SoundBox_Key_Select[SoundBox_Menu_Select] < 2)
			{
				// 足す
				SoundBox_Key_Select[SoundBox_Menu_Select]++;
			}
		}

		// 左キー
		if (KeyLeft.down())
		{
			// 下限を超えていないとき
			if (SoundBox_Key_Select[SoundBox_Menu_Select] > 0)
			{
				// 減らす
				SoundBox_Key_Select[SoundBox_Menu_Select]--;
			}
		}
		*/
		break;

	case 2:

		if (KeyEnter.down())
		{
			// TiTle_BGMが流れてるか判定
			if (AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).isPlaying() == false)
			{
				// 音楽を変える
				Audio_ALL_Stop();
				AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).play(MixBus0);


				// 現在の音楽情報を変える
				SoundBox_Key_Select_Now[SoundBox_Menu_Select] = SoundBox_Key_Select[SoundBox_Menu_Select];
				SoundBox_Menu_Select_Now = SoundBox_Menu_Select;
			}
		}

		break;

	case 3:

		if (KeyEnter.down())
		{
			// TiTle_BGMが流れてるか判定
			if (AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).isPlaying() == false)
			{
				// 音楽を変える
				Audio_ALL_Stop();
				AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).play(MixBus0);


				// 現在の音楽情報を変える
				SoundBox_Key_Select_Now[SoundBox_Menu_Select] = SoundBox_Key_Select[SoundBox_Menu_Select];
				SoundBox_Menu_Select_Now = SoundBox_Menu_Select;
			}
		}

		break;

	case 4:
		if (KeyEnter.down())
		{
			// TiTle_BGMが流れてるか判定
			if (AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).isPlaying() == false)
			{
				// 音楽を変える
				Audio_ALL_Stop();
				AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).play(MixBus0);


				// 現在の音楽情報を変える
				SoundBox_Key_Select_Now[SoundBox_Menu_Select] = SoundBox_Key_Select[SoundBox_Menu_Select];
				SoundBox_Menu_Select_Now = SoundBox_Menu_Select;
			}
		}
		/*
		// 右キー
		if (KeyRight.down())
		{
			// 上限を超えていないとき
			if (SoundBox_Key_Select[SoundBox_Menu_Select] < 1)
			{
				// 足す
				SoundBox_Key_Select[SoundBox_Menu_Select]++;
			}
		}

		// 左キー
		if (KeyLeft.down())
		{
			// 下限を超えていないとき
			if (SoundBox_Key_Select[SoundBox_Menu_Select] > 0)
			{
				// 減らす
				SoundBox_Key_Select[SoundBox_Menu_Select]--;
			}
		}
		*/
		break;

	case 5:
		if (KeyEnter.down())
		{
			// TiTle_BGMが流れてるか判定
			if (AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).isPlaying() == false)
			{
				// 音楽を変える
				Audio_ALL_Stop();
				AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).play(MixBus0);


				// 現在の音楽情報を変える
				SoundBox_Key_Select_Now[SoundBox_Menu_Select] = SoundBox_Key_Select[SoundBox_Menu_Select];
				SoundBox_Menu_Select_Now = SoundBox_Menu_Select;
			}
		}
		/*
		// 右キー
		if (KeyRight.down())
		{
			// 上限を超えていないとき
			if (SoundBox_Key_Select[SoundBox_Menu_Select] < 1)
			{
				// 足す
				SoundBox_Key_Select[SoundBox_Menu_Select]++;
			}
		}

		// 左キー
		if (KeyLeft.down())
		{
			// 下限を超えていないとき
			if (SoundBox_Key_Select[SoundBox_Menu_Select] > 0)
			{
				// 減らす
				SoundBox_Key_Select[SoundBox_Menu_Select]--;
			}
		}
		*/
		break;

	case 6:
		if (KeyEnter.down())
		{
			// TiTle_BGMが流れてるか判定
			if (AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).isPlaying() == false)
			{
				// 音楽を変える
				Audio_ALL_Stop();
				AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).play(MixBus1);


				// 現在の音楽情報を変える
				SoundBox_Key_Select_Now[SoundBox_Menu_Select] = SoundBox_Key_Select[SoundBox_Menu_Select];
				SoundBox_Menu_Select_Now = SoundBox_Menu_Select;
			}
		}
		
		// 右キー
		if (KeyRight.down())
		{
			// 上限を超えていないとき
			if (SoundBox_Key_Select[SoundBox_Menu_Select] < 2)
			{
				// 足す
				SoundBox_Key_Select[SoundBox_Menu_Select]++;
			}
		}

		// 左キー
		if (KeyLeft.down())
		{
			// 下限を超えていないとき
			if (SoundBox_Key_Select[SoundBox_Menu_Select] > 0)
			{
				// 減らす
				SoundBox_Key_Select[SoundBox_Menu_Select]--;
			}
		}
		
		break;

	case 7:
		if (KeyEnter.down())
		{
			// 全音楽終了
			Audio_ALL_Stop();

			// タイトルシーンへ
			changeScene(State::Title);
		}

		break;

	default:

		break;
	}
}

void SoundBox::draw() const
{
	// 背景
	// 背景色
	Scene::SetBackground(ColorF(0.3, 0.4, 0.5));


	// タイトル文字
	// タイトル文字
	FontAsset(U"Medium_60")(U"Sound Box").drawAt(Scene::Center().movedBy(0, -250), Color{ 255, 255, 255, 255 });

	
	// 現在の再生位置
	FontAsset(U"Medium_20")(Audio_name[SoundBox_Menu_Select_Now][SoundBox_Key_Select_Now[SoundBox_Menu_Select_Now]] +
		U"\n{:.1f}sec ({}samples) / {:.1f}sec ({}samples)"_fmt(
			AudioAsset(Audio_Menu[SoundBox_Menu_Select_Now] + Format(SoundBox_Key_Select_Now[SoundBox_Menu_Select_Now])).posSec(),
			AudioAsset(Audio_Menu[SoundBox_Menu_Select_Now] + Format(SoundBox_Key_Select_Now[SoundBox_Menu_Select_Now])).posSample(),
			AudioAsset(Audio_Menu[SoundBox_Menu_Select_Now] + Format(SoundBox_Key_Select_Now[SoundBox_Menu_Select_Now])).lengthSec(),
			AudioAsset(Audio_Menu[SoundBox_Menu_Select_Now] + Format(SoundBox_Key_Select_Now[SoundBox_Menu_Select_Now])).samples()))
		.drawAt(Scene::Center().movedBy(0, -175), Color{ 255, 255, 255, 255 });;


	// Menu文字
	// TitleBGMメニュー
	if (SoundBox_Menu_Select == 0)
	{
		// menu内容文字
		switch (SoundBox_Key_Select[SoundBox_Menu_Select])
		{
		case 1:

			FontAsset(U"Medium_20")(U"　 " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" 　")
				.draw(Scene::Center().movedBy(0, -120), Color{ 255, 255, 255, 255 });

			break;
			/*
		case 0:

			// 曲名
			FontAsset(U"Medium_20")(U"　 " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" →")
				.draw(Scene::Center().movedBy(0, -120), Color{ 255, 255, 255, 255 });

			break;

		case 1:

			FontAsset(U"Medium_20")(U"← " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" →")
				.draw(Scene::Center().movedBy(0, -120), Color{ 255, 255, 255, 255 });

			break;

		case 2:

			FontAsset(U"Medium_20")(U"← " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" 　")
				.draw(Scene::Center().movedBy(0, -120), Color{ 255, 255, 255, 255 });

			break;
			*/
		}


		// Menuバー文字
		FontAsset(U"Medium_30")(U"TitleBGM").draw(Scene::Center().movedBy(-300, -125), Color{ 255, 255, 255, 255 });
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"TitleBGM").draw(Scene::Center().movedBy(-300, -125), Color{ 255, 255, 255, 127 });
	}

	// SettingBGMメニュー
	if (SoundBox_Menu_Select == 1)
	{
		// menu内容文字
		switch (SoundBox_Key_Select[SoundBox_Menu_Select])
		{
		case 0:
			// 曲名
			FontAsset(U"Medium_20")(U"　 " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" 　")
				.draw(Scene::Center().movedBy(0, -80), Color{ 255, 255, 255, 255 });

			break;
			/*
		case 0:

			// 曲名
			FontAsset(U"Medium_20")(U"　 " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" →")
				.draw(Scene::Center().movedBy(0, -80), Color{ 255, 255, 255, 255 });

			break;

		case 1:

			FontAsset(U"Medium_20")(U"← " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" →")
				.draw(Scene::Center().movedBy(0, -80), Color{ 255, 255, 255, 255 });

			break;

		case 2:

			FontAsset(U"Medium_20")(U"← " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" 　")
				.draw(Scene::Center().movedBy(0, -80), Color{ 255, 255, 255, 255 });

			break;
			*/
		}


		// Menuバー文字
		FontAsset(U"Medium_30")(U"SettingBGM").draw(Scene::Center().movedBy(-300, -85), Color{ 255, 255, 255, 255 });
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"SettingBGM").draw(Scene::Center().movedBy(-300, -85), Color{ 255, 255, 255, 127 });
	}

	// Result_WinBGMメニュー
	if (SoundBox_Menu_Select == 2)
	{
		// menu内容文字
		switch (SoundBox_Key_Select[SoundBox_Menu_Select])
		{
		case 0:

			// 曲名
			FontAsset(U"Medium_20")(U"　 " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" 　")
				.draw(Scene::Center().movedBy(0, -40), Color{ 255, 255, 255, 255 });

			break;
		}


		// Menuバー文字
		FontAsset(U"Medium_30")(U"Result_WinBGM").draw(Scene::Center().movedBy(-300, -45), Color{ 255, 255, 255, 255 });
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"Result_WinBGM").draw(Scene::Center().movedBy(-300, -45), Color{ 255, 255, 255, 127 });
	}

	// Result_LoseBGMメニュー
	if (SoundBox_Menu_Select == 3)
	{
		// menu内容文字
		switch (SoundBox_Key_Select[SoundBox_Menu_Select])
		{
		case 0:

			// 曲名
			FontAsset(U"Medium_20")(U"　 " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" 　")
				.draw(Scene::Center().movedBy(0, 0), Color{ 255, 255, 255, 255 });

			break;
		}


		// Menuバー文字
		FontAsset(U"Medium_30")(U"Result_LoseBGM").draw(Scene::Center().movedBy(-300, -5), Color{ 255, 255, 255, 255 });
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"Result_LoseBGM").draw(Scene::Center().movedBy(-300, -5), Color{ 255, 255, 255, 127 });
	}

	// Player Nameメニュー
	if (SoundBox_Menu_Select == 4)
	{
		// menu内容文字
		switch (SoundBox_Key_Select[SoundBox_Menu_Select])
		{
		case 0:

			// 曲名
			FontAsset(U"Medium_20")(U"　 " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" 　")
				.draw(Scene::Center().movedBy(0, 40), Color{ 255, 255, 255, 255 });

			break;
			/*
		case 0:

			// 曲名
			FontAsset(U"Medium_20")(U"　 " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" →")
				.draw(Scene::Center().movedBy(0, 40), Color{ 255, 255, 255, 255 });

			break;

		
		case 1:

			FontAsset(U"Medium_20")(U"← " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" 　")
				.draw(Scene::Center().movedBy(0, 40), Color{ 255, 255, 255, 255 });

			break;
			*/
		}


		// Menuバー文字
		FontAsset(U"Medium_30")(U"MatchingBGM").draw(Scene::Center().movedBy(-300, 35), Color{ 255, 255, 255, 255 });
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"MatchingBGM").draw(Scene::Center().movedBy(-300, 35), Color{ 255, 255, 255, 127 });
	}

	// Player Nameメニュー
	if (SoundBox_Menu_Select == 5)
	{
		// menu内容文字
		switch (SoundBox_Key_Select[SoundBox_Menu_Select])
		{
		case 1:

			// 曲名
			FontAsset(U"Medium_20")(U"　 " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" 　")
				.draw(Scene::Center().movedBy(0, 80), Color{ 255, 255, 255, 255 });

			break;
			/*
		case 0:

			// 曲名
			FontAsset(U"Medium_20")(U"　 " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" →")
				.draw(Scene::Center().movedBy(0, 80), Color{ 255, 255, 255, 255 });

			break;


		case 1:

			FontAsset(U"Medium_20")(U"← " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" 　")
				.draw(Scene::Center().movedBy(0, 80), Color{ 255, 255, 255, 255 });

			break;
			*/
		}


		// Menuバー文字
		FontAsset(U"Medium_30")(U"GameBGM").draw(Scene::Center().movedBy(-300, 75), Color{ 255, 255, 255, 255 });
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"GameBGM").draw(Scene::Center().movedBy(-300, 75), Color{ 255, 255, 255, 127 });
	}

	// GameSEメニュー
	if (SoundBox_Menu_Select == 6)
	{
		// menu内容文字
		switch (SoundBox_Key_Select[SoundBox_Menu_Select])
		{
		case 0:

			// 曲名
			FontAsset(U"Medium_20")(U"　 " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" →")
				.draw(Scene::Center().movedBy(0, 120), Color{ 255, 255, 255, 255 });

			break;

		case 1:

			FontAsset(U"Medium_20")(U"← " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" →")
				.draw(Scene::Center().movedBy(0, 120), Color{ 255, 255, 255, 255 });

			break;

		case 2:

			FontAsset(U"Medium_20")(U"← " + Audio_name[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U" 　")
				.draw(Scene::Center().movedBy(0, 120), Color{ 255, 255, 255, 255 });

			break;
		}


		// Menuバー文字
		FontAsset(U"Medium_30")(U"GameSE").draw(Scene::Center().movedBy(-300, 115), Color{ 255, 255, 255, 255 });
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"GameSE").draw(Scene::Center().movedBy(-300, 115), Color{ 255, 255, 255, 127 });
	}

	// EXITメニュー
	if (SoundBox_Menu_Select == 7)
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"EXIT").draw(Scene::Center().movedBy(-300, 155), Color{ 255, 255, 255, 255 });
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"EXIT").draw(Scene::Center().movedBy(-300, 155), Color{ 255, 255, 255, 127 });


		// 音楽説明
		// 合計再生時間
		FontAsset(U"Medium_20")(Audio_Writer[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]] + U"\n{:.1f} sec ({} samples)\n"_fmt(
			AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).lengthSec(),
			AudioAsset(Audio_Menu[SoundBox_Menu_Select] + Format(SoundBox_Key_Select[SoundBox_Menu_Select])).samples())
			+ Audio_References[SoundBox_Menu_Select][SoundBox_Key_Select[SoundBox_Menu_Select]])
			.drawAt(Scene::Center().movedBy(0, 250), Color{ 255, 255, 255, 255 });;
	}
	
}

void  SoundBox::Audio_ALL_Stop()
{
	//AudioAsset(U"Title_BGM0").stop();
	AudioAsset(U"Title_BGM1").stop();
	//AudioAsset(U"Title_BGM2").stop();
	AudioAsset(U"Setting_BGM0").stop();
	//AudioAsset(U"Setting_BGM1").stop();
	//AudioAsset(U"Setting_BGM2").stop();
	AudioAsset(U"Result_Win_BGM0").stop();
	AudioAsset(U"Result_Lose_BGM0").stop();
	AudioAsset(U"Matching_BGM0").stop();
	//AudioAsset(U"Matching_BGM1").stop();
	//AudioAsset(U"Game_BGM0").stop();
	AudioAsset(U"Game_BGM1").stop();
	AudioAsset(U"SE0").stop();
	AudioAsset(U"SE1").stop();
	AudioAsset(U"SE2").stop();
}
