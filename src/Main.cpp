# include "NetworkSystem.hpp"
# include "Common.hpp"
# include "Title.hpp"
# include "Game.hpp"
# include "Matching.hpp"
# include "Setting.hpp"
# include "Option.hpp"
# include "result.hpp"
# include "SoundBox.hpp"
# include "Howtoplay.hpp"
# include "About.hpp"

void Main()
{
	// ウィンドウの閉じるボタンを押すか、System::Exit() を呼ぶのを終了操作に設定,
	// エスケープキーを押しても終了しないようになる
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);


	// Window
	// シーンのサイズを固定
	Scene::SetResizeMode(ResizeMode::Keep);

	// Titlebarの設定
	Array<String> addmessage
	{
		U"Thank you for playing.",
		U"Do you enjoy playing?",
		U"Yes, Today is a good day.",
		U"Seeing is believing.",
		U"All is well that ends well.",
		U"This part imitates Terraria."
	};
	Window::SetTitle(U"Paint Runner : " + addmessage.choice());
	// Monitorの情報を獲得
	const Array<MonitorInfo> monitors = System::EnumerateMonitors();

	// UIの拡大倍率の取得
	double monitor_scaling;
	for (const auto& monitor : monitors)
	{
		if (monitor.scaling)
		{
			monitor_scaling = monitor.scaling.value();
		}
		else
		{
			throw Error{ U"Failed to load `MonitorInfo`" };
		}
	}

	//for(const auto& NG:NGword)
	//{
	//	Console.write(U"U\"{}\","_fmt(MD5::FromText(NG).asString()));
	//}

	// INIファイル
	// INI ファイルからデータを読み込む
	INI ini{ U"config.ini" };

	if (not ini) // もし読み込みに失敗したら
	{
		// セクションを追加
		ini.addSection(U"Volume");
		ini.addSection(U"Name");
		ini.addSection(U"Window");
		ini.addSection(U"Audio");

		ini.write(U"Volume", U"globalVolume", 1.0);
		ini.write(U"Volume", U"MixBus0Volume", 0.2);
		ini.write(U"Volume", U"MixBus1Volume", 0.6);
		ini.write(U"Name", U"UserName", U"Noname");
		ini.write(U"Window", U"FullScreen", false);
		ini.write(U"Window", U"width", 800);
		ini.write(U"Window", U"height", 600);
		ini.write(U"Window", U"Scale", monitor_scaling);
		ini.write(U"Audio", U"Title_BGM", 1);
		ini.write(U"Audio", U"Game_BGM", 1);
		ini.write(U"Audio", U"Setting_BGM", 0);
		ini.write(U"Audio", U"Result_Win_BGM", 0);
		ini.write(U"Audio", U"Result_Lose_BGM", 0);
		ini.write(U"Audio", U"Matching_BGM", 0);

		// 保存
		ini.save(U"config.ini");
	}

	// UIの拡大倍率の更新
	ini[U"Window.Scale"] = monitor_scaling;

	// アセットの登録
	// Audio
	//AudioAsset::Register(U"Title_BGM0", U"Audio/BGM/Title_BGM/Pink_Pico_Planet.mp3");	// Title.cpp, SoundBox.cpp
	//AudioAsset::Load(U"Title_BGM0");
	AudioAsset::Register(U"Title_BGM1", U"Audio/BGM/Title_BGM/Pink_Pico_Planet_2.mp3");	// Title.cpp, SoundBox.cpp
	AudioAsset::Load(U"Title_BGM1");
	//AudioAsset::Register(U"Title_BGM2", U"Audio/BGM/Title_BGM/ワクワクアリクイ.mp3");	// Title.cpp, SoundBox.cpp
	//AudioAsset::Load(U"Title_BGM2");
	AudioAsset::Register(U"Setting_BGM0", U"Audio/BGM/Setting_BGM/休日ショッピング的なBGM.mp3");	// Setting.cpp, Howtoplay.cpp, About.cpp, SoundBox.cpp
	AudioAsset::Load(U"Setting_BGM0");
	//AudioAsset::Register(U"Setting_BGM1", U"Audio/BGM/Setting_BGM/休日ショッピング的なBGM_2.mp3");	// Setting.cpp, Howtoplay.cpp, About.cpp, SoundBox.cpp
	//AudioAsset::Load(U"Setting_BGM1");
	//AudioAsset::Register(U"Setting_BGM2", U"Audio/BGM/Setting_BGM/8bit_Game_Menu.mp3");	// Setting.cpp, Howtoplay.cpp, About.cpp, SoundBox.cpp
	//AudioAsset::Load(U"Setting_BGM2");
	AudioAsset::Register(U"Result_Win_BGM0", U"Audio/BGM/Result_BGM/Trick_style.mp3");	// Result.cpp, SoundBox.cpp
	AudioAsset::Load(U"Result_Win_BGM0");
	AudioAsset::Register(U"Result_Lose_BGM0", U"Audio/BGM/Result_BGM/DUB_MACHINE_1.mp3");	// Result.cpp, SoundBox.cpp
	AudioAsset::Load(U"Result_Lose_BGM0");
	AudioAsset::Register(U"Matching_BGM0", U"Audio/BGM/Match_BGM/超使いやすいドラム&ベース無限BGM.mp3");	// Matching.cpp, Option.cpp, SoundBox.cpp
	AudioAsset::Load(U"Matching_BGM0");
	//AudioAsset::Register(U"Matching_BGM1", U"Audio/BGM/Match_BGM/超使いやすいドラム&ベース無限BGM_2.mp3");	// Matching.cpp, Option.cpp, SoundBox.cpp
	//AudioAsset::Load(U"Matching_BGM1");
	//AudioAsset::Register(U"Game_BGM0", U"Audio/BGM/Game_BGM/サイバーホップ.mp3");	// Game.cpp, SoundBox.cpp
	//AudioAsset::Load(U"Game_BGM0");
	AudioAsset::Register(U"Game_BGM1", U"Audio/BGM/Game_BGM/サイバーポップ_2.mp3");	// Game.cpp, SoundBox.cpp
	AudioAsset::Load(U"Game_BGM1");
	AudioAsset::Register(U"GameSE0", U"Audio/SE/se_magic_tititi.mp3");	// 
	AudioAsset::Load(U"GameSE0");
	AudioAsset::Register(U"GameSE1", U"Audio/SE/se_magic_effect1.mp3");	// 
	AudioAsset::Load(U"GameSE1");
	AudioAsset::Register(U"GameSE2", U"Audio/SE/se_down.mp3");	// 
	AudioAsset::Load(U"GameSE2");


	// Font
	FontAsset::Register(U"Medium_15", FontMethod::MSDF, 15, Typeface::Medium);	// Matching.cpp
	FontAsset::Register(U"Medium_20", FontMethod::MSDF, 20, Typeface::Medium);	// SoundBox.cpp
	FontAsset::Register(U"Medium_30", FontMethod::MSDF, 30, Typeface::Medium);	// Setting.cpp, SoundBox.cpp, Howtoplay.cpp
	FontAsset::Register(U"Medium_40", FontMethod::MSDF, 40, Typeface::Medium);	// Game.cpp, Option.cpp, Result.cpp, Setting.cpp, Title.cpp
	FontAsset::Register(U"Medium_50", FontMethod::MSDF, 50, Typeface::Medium);	// Result.cpp
	FontAsset::Register(U"Medium_60" ,FontMethod::MSDF, 60, Typeface::Medium);	// Setting.cpp, SoundBox.cpp, Howtoplay.cpp
	FontAsset::Register(U"Medium_75", FontMethod::MSDF, 75, Typeface::Medium);	// Result.cpp

	
	// Texture
	TextureAsset::Register(U"Title_Image0", U"image/Title_BackImege/dungeon.jpg");	// Title.cpp
	TextureAsset::Register(U"Item_Image0", U"image/item_icon/Direction_of_the_other_party.png");	// Result.cpp, GameClass.hpp
	TextureAsset::Register(U"Item_Image1", U"image/item_icon/Goal_direction.png");	// Result.cpp, GameClass.hpp
	TextureAsset::Register(U"Item_Image2", U"image/item_icon/shikai_kakudai.png");	// Result.cpp, GameClass.hpp
	TextureAsset::Register(U"Item_Image3", U"image/item_icon/shikai_shukusho.png");	// Result.cpp, GameClass.hpp
	TextureAsset::Register(U"Item_Image4", U"image/item_icon/speed_down.png");	// Result.cpp, GameClass.hpp
	TextureAsset::Register(U"Item_Image5", U"image/item_icon/speed_up.png");	// Result.cpp, GameClass.hpp
	TextureAsset::Register(U"Tile_Image0", U"image/all tile/wall_tile.png");	// 
	TextureAsset::Register(U"Tile_Image1", U"image/all tile/blank_tile.png");	// 
	TextureAsset::Register(U"Tile_Image2", U"image/all tile/blue_tile.png");	// 
	TextureAsset::Register(U"Tile_Image3", U"image/all tile/red_tile.png");	// 
	TextureAsset::Register(U"Tile_Image4", U"image/all tile/goal_tile.png");	// 
	//TextureAsset::Register(U"Player_Image0", U"image/blueplayer_all_motion/bp_motion.png");	// 
	//TextureAsset::Register(U"Player_Image1", U"image/redplayer_all_motion/rp_motion.png");	// 
	TextureAsset::Register(U"vision_Image0", U"image/vision/vision_scale_down.png");	// GameClass.hpp
	TextureAsset::Register(U"vision_Image1", U"image/vision/vision.png");	// Game.hpp
	TextureAsset::Register(U"vision_Image2", U"image/vision/vision_scale_up.png");	// GameClass.hpp
	TextureAsset::Register(U"How to play_Image0", U"image/Howtoplay/1.png");	// Howtoplay.cpp
	TextureAsset::Register(U"How to play_Image1", U"image/Howtoplay/2.png");	// Howtoplay.cpp
	TextureAsset::Register(U"How to play_Image2", U"image/Howtoplay/3.png");	// Howtoplay.cpp
	TextureAsset::Register(U"How to play_Image3", U"image/Howtoplay/4.png");	// Howtoplay.cpp
	TextureAsset::Register(U"How to play_Image4", U"image/Howtoplay/5.png");	// Howtoplay.cpp
	TextureAsset::Register(U"How to play_Image5", U"image/Howtoplay/6.png");	// Howtoplay.cpp
	

	// シーン管理
	App manager;
	manager.add<Title>(State::Title);
	manager.add<Option>(State::Option);
	manager.add<Game>(State::Game);
	manager.add<Matching>(State::Match);
	manager.add<Setting>(State::Setting);
	manager.add<Result>(State::Result);
	manager.add<SoundBox>(State::SoundBox);
	manager.add<Howtoplay>(State::Howtoplay);
	manager.add<About>(State::About);
	
	Print << SIV3D_VERSION_STRING;
	// オプションシーンから開始したい場合はこのコメントを外す
	//manager.init(State::Option);
	// サウンドボックスシーンから開始したい場合はこのコメントを外す
	//manager.init(State::SoundBox);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
