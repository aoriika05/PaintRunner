#include "Howtoplay.hpp"

Howtoplay::Howtoplay(const InitData& init)
	: IScene{ init }
{
	// INIファイル
	// 全てのセクションを列挙
	for (const auto& section : Howtoplay_ini.sections())
	{
		if (section.section == U"Audio")	// Audioセクション
		{
			// セクション内のすべてのキーを列挙
			for (const auto& key : section.keys)
			{
				if (key.name == U"Setting_BGM")	// Settingキー
				{
					Howtoplay_Audio_BGM_num = Parse<uint8>(key.value);
				}
			}
		}
	}


	// メニュー選択
	// 選択中のMenu番号
	Howtoplay_Menu_Select = 0;
}


void Howtoplay::update()
{
	// 音楽
	// 曲が流れてるか判定
	if (AudioAsset(U"Setting_BGM" + Format(Howtoplay_Audio_BGM_num)).isPlaying() == false)
	{
		AudioAsset(U"Setting_BGM" + Format(Howtoplay_Audio_BGM_num)).play(MixBus0);
	}


	// 画面遷移
	// 右へ
	if (KeyRight.down())
	{
		if (Howtoplay_Menu_Select < Howtoplay_Menu_Max - 1)
		{
			Howtoplay_Menu_Select++;
		}
	}

	// 左へ
	if (KeyLeft.down())
	{
		if (Howtoplay_Menu_Select > 0)
		{
			Howtoplay_Menu_Select--;
		}
	}

	// タイトルへ
	if (KeyEscape.down())
	{
		// 音楽停止
		AudioAsset(U"Setting_BGM" + Format(Howtoplay_Audio_BGM_num)).stop();

		// タイトルシーンへ
		changeScene(State::Title);
	}
}

void Howtoplay::draw() const
{
	// 表示画像
	TextureAsset(U"How to play_Image" + Format(Howtoplay_Menu_Select)).resized(800).drawAt(Scene::Center().movedBy(0, 0));


	// 文字
	// 右へ
	if (Howtoplay_Menu_Select < Howtoplay_Menu_Max - 1)
	{
		FontAsset(U"Medium_60")(U"→").drawAt(Scene::Center().movedBy( 350, 260));
	}

	// 左へ
	if (Howtoplay_Menu_Select > 0)
	{
		FontAsset(U"Medium_60")(U"←").drawAt(Scene::Center().movedBy(-350, 260));
	}

	// Exit
	FontAsset(U"Medium_30")(U"Exit : Escape").draw(Scene::Center().movedBy(-375, -285));
}
