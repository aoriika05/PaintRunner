# include "Title.hpp"

Title::Title(const InitData& init)
	: IScene{ init }
{
	Print << U"Now Loading";

	// INIファイル
	// INIファイルからデータを読み込む
	INI Title_ini{ U"config.ini" };

	// 全てのセクションを列挙
	for (const auto& section : Title_ini.sections())
	{
		if (section.section == U"Volume")	// セクション
		{
			// セクション内のすべてのキーを列挙
			for (const auto& key : section.keys)
			{
				if (key.name == U"globalVolume")	// キー
				{
					getData().globalVolume = Parse<double>(key.value);

					// グローバルオーディオの音量を変更
					GlobalAudio::SetVolume(getData().globalVolume);
				}
				else if (key.name == U"MixBus0Volume")
				{
					getData().MixBus0Volume = Parse<double>(key.value);

					// MixBus0 の音量を変更
					GlobalAudio::BusSetVolume(MixBus0, getData().MixBus0Volume);
				}
				else if (key.name == U"MixBus1Volume")
				{
					getData().MixBus1Volume = Parse<double>(key.value);

					// MixBus0 の音量を変更
					GlobalAudio::BusSetVolume(MixBus1, getData().MixBus1Volume);
				}
			}
		}
		else if (section.section == U"Name")
		{
			for (const auto& key : section.keys)
			{
				if (key.name == U"UserName")
				{
					getData().UserName = key.value;
				}
			}
		}
		else if(section.section == U"Window")
		{
			// Windowリサイズ用変数
			double Title_Window_width = -1;
			double Title_Window_height = -1;
			double Title_Window_Scale = -1;
			bool Title_Fullscreen = false;

			for (const auto& key : section.keys)
			{
				if (key.name == U"FullScrean")
				{
					if (key.value == U"true")
					{
						Title_Fullscreen = true;
					}
					else if (key.value == U"false")
					{
						Title_Fullscreen = false;
					}
					else
					{
						throw Error{ U"Failed to load `config.ini`_[Window]_FullScrean" };
					}
				}
				else if (key.name == U"width")
				{
					Title_Window_width = Parse<double>(key.value);
				}
				else if (key.name == U"height")
				{
					Title_Window_height = Parse<double>(key.value);
				}
				else if (key.name == U"Scale")
				{
					Title_Window_Scale = Parse<double>(key.value);
				}
			}

			// Windowのサイズ
			if (Title_Fullscreen)
			{
				// FullScreanに
				Window::SetFullscreen(Title_Fullscreen);
			}
			else
			{
				// Windowのサイズをリサイズ
				Window::Resize((int32)(Title_Window_width / Title_Window_Scale), (int32)(Title_Window_height / Title_Window_Scale));
			}
		}
		else if (section.section == U"Audio")
		{
			for (const auto& key : section.keys)
			{
				if (key.name == U"Title_BGM")
				{
					Title_Audio_BGM_num = Parse<uint8>(key.value);
				}
			}
		}
	}

	
	// メニュー選択
	// 選択中のMenu番号
	Title_Menu_Select = 0;
}

void Title::update()
{
	// Debug
	if (1)
	{
		if (1s <= KeyNum0.pressedDuration())
		{
			AudioAsset(U"Title_BGM" + Format(Title_Audio_BGM_num)).stop();
			changeScene(State::SoundBox);
		}
	}

	ClearPrint();
	// 音楽
	// 曲が流れてるか判定
	if(AudioAsset(U"Title_BGM" + Format(Title_Audio_BGM_num)).isPlaying() == false)
	{
		AudioAsset(U"Title_BGM" + Format(Title_Audio_BGM_num)).play(MixBus0);
	}

	// Menu
	// 上ボタン
	if (KeyUp.down())
	{
		if (Title_Menu_Select > 0)
		{
			Title_Menu_Select = Title_Menu_Select - 1;
		}
	}

	if (KeyDown.down())
	{
		if (Title_Menu_Select < Title_Menu_Max - 1)
		{
			Title_Menu_Select = Title_Menu_Select + 1;
		}
	}
	// シーン変更
	// Enterキーが押されたとき
	if (KeyEnter.down())
	{
		// Titleの曲を停止
		AudioAsset(U"Title_BGM" + Format(Title_Audio_BGM_num)).stop();
		switch (Title_Menu_Select)
		{
		case 0:
			// オプションシーンへ
			changeScene(State::Option);
			break;

		case 1:
			// 使い方シーンへ
			changeScene(State::Howtoplay);
			break;

		case 2:
			// 設定シーンへ
			changeScene(State::Setting);
			break;

		case 3:
			// ライセンスへ
			changeScene(State::About);
			break;

		case 4:
				// 終了
				System::Exit();
				break;
		}
	}

	if(net!=nullptr)
	{
		net->update();
	}
}

void Title::draw() const
{
	// 背景
	// 背景色
	Scene::SetBackground(ColorF(0.3, 0.4, 0.5));

	// 背景画像
	TextureAsset(U"Title_Image0").resized(800).drawAt(Scene::Center().movedBy(0, 0));
	

	// タイトル



	// MenuBar
	// Gameキー
	// 文字
	if (Title_Menu_Select == 0)
	{
		FontAsset(U"Medium_40")(U"PLAY").draw(Scene::Center().movedBy(100, -50), Color{ 255, 255, 255, 255 });
	}
	else
	{
		FontAsset(U"Medium_40")(U"PLAY").draw(Scene::Center().movedBy(100, -50), Color{ 255, 255, 255, 127 });
	}

	// Howtoplayキー
	// 文字
	if (Title_Menu_Select == 1)
	{
		FontAsset(U"Medium_40")(U"How to Play").draw(Scene::Center().movedBy(100, 0), Color{ 255, 255, 255, 255 });
	}
	else
	{
		FontAsset(U"Medium_40")(U"How to Play").draw(Scene::Center().movedBy(100, 0), Color{ 255, 255, 255, 127 });
	}

	// Settingキー
	// 文字
	if (Title_Menu_Select == 2)
	{
		FontAsset(U"Medium_40")(U"SETTING").draw(Scene::Center().movedBy(100, 50), Color{ 255, 255, 255, 255 });
	}
	else
	{
		FontAsset(U"Medium_40")(U"SETTING").draw(Scene::Center().movedBy(100, 50), Color{ 255, 255, 255, 127 });
	}

	// Aboutキー
	// 文字
	if (Title_Menu_Select == 3)
	{
		FontAsset(U"Medium_40")(U"About").draw(Scene::Center().movedBy(100, 100), Color{ 255, 255, 255, 255 });
	}
	else
	{
		FontAsset(U"Medium_40")(U"About").draw(Scene::Center().movedBy(100, 100), Color{ 255, 255, 255, 127 });
	}

	// Exitキー
	// 文字
	if (Title_Menu_Select == 4)
	{
		FontAsset(U"Medium_40")(U"EXIT").draw(Scene::Center().movedBy(100, 150), Color{ 255, 255, 255, 255 });
	}
	else
	{
		FontAsset(U"Medium_40")(U"EXIT").draw(Scene::Center().movedBy(100, 150), Color{ 255, 255, 255, 127 });
	}
}
