# include "Setting.hpp"

Setting::Setting(const InitData& init)
	: IScene{ init }
{
	// INIファイル
	// 全てのセクションを列挙
	for (const auto& section : Setting_ini.sections())
	{
		if (section.section == U"Window")	// Windowセクション
		{
			// セクション内のすべてのキーを列挙
			for (const auto& key : section.keys)
			{
				if (key.name == U"Scale")	// Scaleキー
				{
					// 画面の倍率を定義
					Setting_Windows_Magnification = Parse<double>(key.value);
				}
				if (key.name == U"FullScreen")	// FullScreenキー
				{
					if (key.value == U"true")
					{
						Setting_Fullscreen = true;
					}
					else if (key.value == U"false")
					{
						Setting_Fullscreen = false;
					}
					else
					{
						throw Error{ U"Failed to load `config.ini`_[Window]_FullScreen" };
					}
				}
			}
		}
		else if (section.section == U"Audio")
		{
			for (const auto& key : section.keys)
			{
				if (key.name == U"Setting_BGM")
				{
					Setting_Audio_BGM_num = Parse<uint8>(key.value);
				}
			}
		}
	}

	// スクリーン
	// ウインドウサイズ
	Setting_Windows_Size = { Vec2{ 0, 0}, Vec2{ 800, 600}, Vec2{ 1000, 750 }, Vec2{ 1024, 768},
		Vec2{ 1200, 900}, Vec2{ 1280, 960}, Vec2{ 1400, 1050}, Vec2{ 1600, 1200} };
	
	// 画面サイズ定義
	Setting_Window_Size_num = 0;

	// 現在のサイズ定義
	Setting_Windows_Size[0] = Window::GetState().frameBufferSize;

	// Monitorの情報を獲得
	const Array<MonitorInfo> monitors = System::EnumerateMonitors();

	// 利用可能な領域のサイズの取得
	for (const auto& monitor : monitors)
	{
		// 現在の
		Setting_workArea.x = monitor.workArea.w;
		Setting_workArea.y = monitor.workArea.h;
	}


	// メニュー選択
	// 選択中のMenu番号
	Setting_Menu_Select = 0;
}

void Setting::update()
{
	// 音楽
	// 曲が流れてるか判定
	if (AudioAsset(U"Setting_BGM" + Format(Setting_Audio_BGM_num)).isPlaying() == false)
	{
		AudioAsset(U"Setting_BGM" + Format(Setting_Audio_BGM_num)).play(MixBus0);
	}


	// Menu
	// 項目選択
	// 上キー
	if (KeyUp.down())
	{
		if (Setting_Menu_Select > 0)
		{
			Setting_Menu_Select = Setting_Menu_Select - 1;
		}
	}

	// 下キー
	if (KeyDown.down())
	{
		if (Setting_Menu_Select < Setting_Menu_Max - 1)
		{
			Setting_Menu_Select = Setting_Menu_Select + 1;
		}
	}


	// 内容選択
	switch (Setting_Menu_Select)
	{
	case 0:
		TextInput::UpdateText(getData().UserName, TextInputMode::AllowBackSpace);

		if (getData().UserName.length() > 6)
		{
			getData().UserName.pop_back();
		}

		// INIファイルの更新
		Setting_ini[U"Name.UserName"] = getData().UserName;

		break;

	case 1:	// Windowサイズメニュー
		// フルスクリーンではないとき
		if (!Setting_Fullscreen)
		{
			// 右キー
			if (KeyRight.down())
			{
				// 上限を超えていないとき
				if (Setting_Window_Size_num < Setting_Windows_Size.size() - 1)
				{
					// 現在の選択中のウィンドウサイズの番号を上げる
					Setting_Window_Size_num++;

					// 表示されているサイズにする
					Window::Resize(Setting_Windows_Size[Setting_Window_Size_num].x / Setting_Windows_Magnification,
						Setting_Windows_Size[Setting_Window_Size_num].y / Setting_Windows_Magnification);

					// INIファイルの更新
					Setting_ini[U"Window.width"] = Setting_Windows_Size[Setting_Window_Size_num].x;
					Setting_ini[U"Window.height"] = Setting_Windows_Size[Setting_Window_Size_num].y;

				}
			}

			// 左キー
			if (KeyLeft.down())
			{
				// フルスクリーンじゃなく下限を超えていないとき
				if (Setting_Window_Size_num > 1)
				{
					// 現在の選択中のウィンドウサイズの番号を下げる
					Setting_Window_Size_num--;

					// 表示されているサイズにする
					Window::Resize(Setting_Windows_Size[Setting_Window_Size_num].x / Setting_Windows_Magnification,
						Setting_Windows_Size[Setting_Window_Size_num].y / Setting_Windows_Magnification);

					// INIファイルの更新
					Setting_ini[U"Window.width"] = Setting_Windows_Size[Setting_Window_Size_num].x;
					Setting_ini[U"Window.height"] = Setting_Windows_Size[Setting_Window_Size_num].y;
				}
			}
		}

		break;

	case 2:	// Windowフルスクリーンメニュー
		// 左キー
		if (KeyRight.down())
		{
			// FullScreen設定解除
			Setting_Fullscreen = false;
			Window::SetFullscreen(false);

			Setting_ini.write(U"Window", U"FullScreen", false);
		}
		// 右キー
		if (KeyLeft.down())
		{
			// FullScreen設定
			Setting_Fullscreen = true;
			Window::SetFullscreen(true);

			Setting_ini.write(U"Window", U"FullScreen", true);
		}

		break;

	case 3:	// MasterVolumeメニュー

		// 左キー
		if (KeyRight.down())
		{
			if (getData().globalVolume <= 0.9)
			{
				// 音量を10%プラス
				getData().globalVolume = getData().globalVolume + 0.1;
			}
			else
			{
				// 最大音量
				getData().globalVolume = 1.0;
			}
		}

		// 右キー
		if (KeyLeft.down())
		{
			if (getData().globalVolume >= 0.1)
			{
				// 音量を10%マイナス
				getData().globalVolume = getData().globalVolume - 0.1;
			}
			else
			{
				// 最大音量
				getData().globalVolume = 0.0;
			}
		}
		
		// 調節用スライダー
		SimpleGUI::Slider(U"{:>3.0f}%"_fmt(getData().globalVolume * 100), getData().globalVolume, 0.00, 1.00, Scene::Center().movedBy(0, 25), 60, 150);

		// グローバルオーディオの音量を変更
		GlobalAudio::SetVolume(getData().globalVolume);

		// INIファイルの更新
		Setting_ini[U"Volume.globalVolume"] = getData().globalVolume;

		break;

	case 4:	// BGMVolumeメニュー

		// 左キー
		if (KeyRight.down())
		{
			if (getData().MixBus0Volume <= 0.9)
			{
				// 音量を10%プラス
				getData().MixBus0Volume = getData().MixBus0Volume + 0.1;
			}
			else
			{
				// 最大音量
				getData().MixBus0Volume = 1.0;
			}
		}

		// 右キー
		if (KeyLeft.down())
		{
			if (getData().MixBus0Volume >= 0.1)
			{
				// 音量を10%マイナス
				getData().MixBus0Volume = getData().MixBus0Volume - 0.1;
			}
			else
			{
				// 最大音量
				getData().MixBus0Volume = 0.0;
			}
		}

		// 調節用スライダー
		SimpleGUI::Slider(U"{:>3.0f}%"_fmt(getData().MixBus0Volume * 100), getData().MixBus0Volume, 0.00, 1.00, Scene::Center().movedBy(0, 75), 60, 150);

		// MixBus0 の音量を変更
		GlobalAudio::BusSetVolume(MixBus0, getData().MixBus0Volume);

		// INIファイルの更新
		Setting_ini[U"Volume.MixBus0Volume"] = getData().MixBus0Volume;

		break;

	case 5:	// SEVolumeメニュー

		// 左キー
		if (KeyRight.down())
		{
			if (getData().MixBus1Volume <= 0.9)
			{
				// 音量を10%プラス
				getData().MixBus1Volume = getData().MixBus1Volume + 0.1;
			}
			else
			{
				// 最大音量
				getData().MixBus1Volume = 1.0;
			}
		}

		// 右キー
		if (KeyLeft.down())
		{
			if (getData().MixBus1Volume >= 0.1)
			{
				// 音量を10%マイナス
				getData().MixBus1Volume = getData().MixBus1Volume - 0.1;
			}
			else
			{
				// 最大音量
				getData().MixBus1Volume = 0.0;
			}
		}

		// 調節用スライダー
		SimpleGUI::Slider(U"{:>3.0f}%"_fmt(getData().MixBus1Volume * 100), getData().MixBus1Volume, 0.00, 1.00, Scene::Center().movedBy(0, 125), 60, 150);

		// MixBus1 の音量を変更
		GlobalAudio::BusSetVolume(MixBus1, getData().MixBus1Volume);

		// INIファイルの更新
		Setting_ini[U"Volume.MixBus1Volume"] = getData().MixBus1Volume;

		break;

	case 6:	// EXIT
		if (KeyEnter.down())
		{
			AudioAsset(U"Setting_BGM" + Format(Setting_Audio_BGM_num)).stop();

			// 保存
			Setting_ini.save(U"config.ini");

			// タイトルシーンへ
			changeScene(State::Title);
			break;
		}
	}
}

void Setting::draw() const
{
// 背景
	// 背景色
	Scene::SetBackground(ColorF(0.3, 0.4, 0.5));


// 文字
	// タイトル文字
	FontAsset(U"Medium_60")(U"SETTING").drawAt(50, Scene::Center().movedBy( 0, -200));

	// Menu文字
	// Player Nameメニュー
	if (Setting_Menu_Select == 0)
	{
		int i;
		// menu内容文字
		for (i = 0; i < getData().UserName.length(); i++)
		{
			// 一文字ずつ
			FontAsset(U"Medium_30")(getData().UserName[i]).drawAt(Scene::Center().movedBy( 20 + i * 25, -105), Color{ 255, 255, 255, 255 });
		}
		if (getData().UserName.length() < 6)
		{
			FontAsset(U"Medium_30")(U"_").drawAt(Scene::Center().movedBy(20 + i * 25, -105), Color{ 255, 255, 255, 255 });
		}

		if (getData().UserName.length() > 6)
		{
			FontAsset(U"Medium_20")(U"Do you enjoy doing things like that?").
				draw(Scene::Center().movedBy(0, -150), Color{ 255, 255, 255, 255 });
		}

		// Menuバー文字
		FontAsset(U"Medium_30")(U"Name").draw(Scene::Center().movedBy(-300, -125), Color{ 255, 255, 255, 255 });
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"Name").draw(Scene::Center().movedBy(-300, -125), Color{ 255, 255, 255, 127 });
	}
	
	// Windowサイズメニュー
	if (Setting_Menu_Select == 1)
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"Window Size").draw(Scene::Center().movedBy(-300, -75), Color{ 255, 255, 255, 255 });

		// menu内容文字
		if (Setting_Window_Size_num >= Setting_Windows_Size.size() - 1)
		{
			FontAsset(U"Medium_30")(U"← " + Format(Setting_Windows_Size[Setting_Window_Size_num].x) + U" × " + Format(Setting_Windows_Size[Setting_Window_Size_num].y) + U" 　")
				.draw(Scene::Center().movedBy(0, -75), Color{ 255, 255, 255, 255 });
		}
		else if (Setting_Window_Size_num <= 1)
		{
			FontAsset(U"Medium_30")(U"　 " + Format(Setting_Windows_Size[Setting_Window_Size_num].x) + U" × " + Format(Setting_Windows_Size[Setting_Window_Size_num].y) + U" →")
				.draw(Scene::Center().movedBy(0, -75), Color{ 255, 255, 255, 255 });
		}
		else
		{
			FontAsset(U"Medium_30")(U"← " + Format(Setting_Windows_Size[Setting_Window_Size_num].x) + U" × " + Format(Setting_Windows_Size[Setting_Window_Size_num].y) + U" →")
				.draw(Scene::Center().movedBy(0, -75), Color{ 255, 255, 255, 255 });
		}
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"Window Size").draw(Scene::Center().movedBy(-300, -75), Color{ 255, 255, 255, 127 });
	}

	// Windowフルスクリーンメニュー
	if (Setting_Menu_Select == 2)
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"FullScreen").draw(Scene::Center().movedBy(-300, -25), Color{ 255, 255, 255, 255 });

		// menu内容文字
		if (Setting_Fullscreen)
		{
			FontAsset(U"Medium_30")(U"　 Yes →").draw(Scene::Center().movedBy(0, -25), Color{ 255, 255, 255, 255 });
		}
		else if (!Setting_Fullscreen)
		{
			FontAsset(U"Medium_30")(U"← No  　").draw(Scene::Center().movedBy(0, -25), Color{ 255, 255, 255, 255 });
		}
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"FullScreen").draw(Scene::Center().movedBy(-300, -25), Color{ 255, 255, 255, 127 });
	}

	// MasterVolumeメニュー
	if (Setting_Menu_Select == 3)
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"MasterVolume").draw(Scene::Center().movedBy(-300, 25), Color{ 255, 255, 255, 255 });
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"MasterVolume").draw(Scene::Center().movedBy(-300, 25), Color{ 255, 255, 255, 127 });
	}

	// BGMVolumeメニュー
	if (Setting_Menu_Select == 4)
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"BGMVolume").draw(Scene::Center().movedBy(-300, 75), Color{ 255, 255, 255, 255 });
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"BGMVolume").draw(Scene::Center().movedBy(-300, 75), Color{ 255, 255, 255, 127 });
	}

	// SEVolumeメニュー
	if (Setting_Menu_Select == 5)
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"SEVolume").draw(Scene::Center().movedBy(-300, 125), Color{ 255, 255, 255, 255 });
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"SEVolume").draw(Scene::Center().movedBy(-300, 125), Color{ 255, 255, 255, 127 });
	}

	// EXITメニュー
	if (Setting_Menu_Select == 6)
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"EXIT").draw(Scene::Center().movedBy(-300, 175), Color{ 255, 255, 255, 255 });
	}
	else
	{
		// Menuバー文字
		FontAsset(U"Medium_30")(U"EXIT").draw(Scene::Center().movedBy(-300, 175), Color{ 255, 255, 255, 127 });
	}
}
