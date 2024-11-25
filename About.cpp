#include "About.hpp"

About::About(const InitData& init)
	: IScene{ init }
{
	// 初期化
	About_Audio_BGM_num = 0;

	// INIファイル
	// 全てのセクションを列挙
	for (const auto& section : About_ini.sections())
	{
		if (section.section == U"Audio")	// Audioセクション
		{
			// セクション内のすべてのキーを列挙
			for (const auto& key : section.keys)
			{
				if (key.name == U"Setting_BGM")	// Settingキー
				{
					About_Audio_BGM_num = Parse<uint8>(key.value);
				}
			}
		}
	}


	// メニュー選択
	// 選択中のMenu番号
	About_Menu_Select = 0;
}


void About::update()
{
	// 音楽
	// 曲が流れてるか判定
	if (AudioAsset(U"Setting_BGM" + Format(About_Audio_BGM_num)).isPlaying() == false)
	{
		AudioAsset(U"Setting_BGM" + Format(About_Audio_BGM_num)).play(MixBus0);
	}


	// 画面遷移
	// 右へ
	if (KeyRight.down())
	{
		if (About_Menu_Select < About_Menu_Max - 1)
		{
			About_Menu_Select++;
		}
	}

	// 左へ
	if (KeyLeft.down())
	{
		if (About_Menu_Select > 0)
		{
			About_Menu_Select--;
		}
	}

	// タイトルへ
	if (KeyEscape.down())
	{
		// 音楽停止
		AudioAsset(U"Setting_BGM" + Format(About_Audio_BGM_num)).stop();

		// タイトルシーンへ
		changeScene(State::Title);
	}
}

void About::draw() const
{
	// 表示画像
	//TextureAsset(U"How to play_Image" + Format(About_Menu_Select)).resized(800).drawAt(Scene::Center().movedBy(0, 0));


	// タイトル文字
	// タイトル文字
	FontAsset(U"Medium_60")(U"About").drawAt(Scene::Center().movedBy(0, -200), Color{ 255, 255, 255, 255 });


	// 文字

	// 1ページ目
	if (About_Menu_Select == 0)
	{
		FontAsset(U"Medium_40")(U"製作者").draw(Scene::Center().movedBy(-350, -150));
		FontAsset(U"Medium_30")(U"札束人間").draw(Scene::Center().movedBy(-250, -100));
		FontAsset(U"Medium_30")(U"転起").draw(Scene::Center().movedBy(0, -100));
		FontAsset(U"Medium_30")(U"HARUNOKI").draw(Scene::Center().movedBy(-250, -50));
		FontAsset(U"Medium_30")(U"幻創").draw(Scene::Center().movedBy(0, -50));
		FontAsset(U"Medium_30")(U"detteiu").draw(Scene::Center().movedBy(-250, 0));
		FontAsset(U"Medium_30")(U"ooi").draw(Scene::Center().movedBy(0, 0));
		FontAsset(U"Medium_30")(U"aoriika").draw(Scene::Center().movedBy(-250, 50));
		FontAsset(U"Medium_30")(U"poruti").draw(Scene::Center().movedBy(0, 50));
	}

	// 2ページ目
	if (About_Menu_Select == 1)
	{
		FontAsset(U"Medium_40")(U"Siv3D").draw(Scene::Center().movedBy(-350, -150));
		FontAsset(U"Medium_30")(U"F1キーでブラウザ表示").draw(Scene::Center().movedBy(-250, -100));
		FontAsset(U"Medium_40")(U"SivPhoton").draw(Scene::Center().movedBy(-350, 0));
		FontAsset(U"Medium_30")(U"制作者 : mak1a様 Luke様").draw(Scene::Center().movedBy(-250, 50));
		FontAsset(U"Medium_40")(U"使用エンジン").draw(Scene::Center().movedBy(-350, 150));
		FontAsset(U"Medium_30")(U"Photon Realtime SDK v5.0.1.1 ").draw(Scene::Center().movedBy(-250, 200));
	}

	// 3ページ目
	if (About_Menu_Select == 2)
	{
		FontAsset(U"Medium_40")(U"タイトルのBGM").draw(Scene::Center().movedBy(-350, -100));
		FontAsset(U"Medium_30")(U"曲名 : Pink_Pico_Planet").draw(Scene::Center().movedBy(-250, -50));
		FontAsset(U"Medium_30")(U"作曲者 : 強化トカゲ").draw(Scene::Center().movedBy(-250, 0));
		FontAsset(U"Medium_30")(U"ダウンロード元 :").draw(Scene::Center().movedBy(-250, 50));
		FontAsset(U"Medium_20")(U"	https://dova-s.jp/bgm/play15882.html").draw(Scene::Center().movedBy(-250, 100));
	}

	// 4ページ目
	if (About_Menu_Select == 3)
	{
		FontAsset(U"Medium_40")(U"設定,遊び方,ライセンスのBGM").draw(Scene::Center().movedBy(-350, -100));
		FontAsset(U"Medium_30")(U"曲名 : 休日ショッピング的なBGM").draw(Scene::Center().movedBy(-250, -50));
		FontAsset(U"Medium_30")(U"作曲者 : 鷹尾まさき(タカオマサキ)").draw(Scene::Center().movedBy(-250, 0));
		FontAsset(U"Medium_30")(U"ダウンロード元 :").draw(Scene::Center().movedBy(-250, 50));
		FontAsset(U"Medium_20")(U"	https://dova-s.jp/bgm/play2883.html").draw(Scene::Center().movedBy(-250, 100));
	}

	// 5ページ目
	if (About_Menu_Select == 4)
	{
		FontAsset(U"Medium_40")(U"リザルトの勝利BGM").draw(Scene::Center().movedBy(-350, -100));
		FontAsset(U"Medium_30")(U"曲名 : Trick_style").draw(Scene::Center().movedBy(-250, -50));
		FontAsset(U"Medium_30")(U"作曲者 : まんぼう二等兵").draw(Scene::Center().movedBy(-250, 0));
		FontAsset(U"Medium_30")(U"ダウンロード元 :").draw(Scene::Center().movedBy(-250, 50));
		FontAsset(U"Medium_20")(U"	https://dova-s.jp/bgm/play10385.html").draw(Scene::Center().movedBy(-250, 100));
	}

	// 6ページ目
	if (About_Menu_Select == 5)
	{
		FontAsset(U"Medium_40")(U"リザルトの敗北BGM").draw(Scene::Center().movedBy(-350, -100));
		FontAsset(U"Medium_30")(U"曲名 : DUB_MACHINE_1").draw(Scene::Center().movedBy(-250, -50));
		FontAsset(U"Medium_30")(U"作曲者 : OK-Sounds").draw(Scene::Center().movedBy(-250, 0));
		FontAsset(U"Medium_30")(U"ダウンロード元 :").draw(Scene::Center().movedBy(-250, 50));
		FontAsset(U"Medium_20")(U"	https://dova-s.jp/bgm/play3814.html").draw(Scene::Center().movedBy(-250, 100));
	}

	// 7ページ目
	if (About_Menu_Select == 6)
	{
		FontAsset(U"Medium_40")(U"マップ選択,マッチング画面のBGM").draw(Scene::Center().movedBy(-350, -100));
		FontAsset(U"Medium_30")(U"曲名 : 超使いやすいドラム&ベース無限BGM").draw(Scene::Center().movedBy(-250, -50));
		FontAsset(U"Medium_30")(U"作曲者 : Hupple").draw(Scene::Center().movedBy(-250, 0));
		FontAsset(U"Medium_30")(U"ダウンロード元 :").draw(Scene::Center().movedBy(-250, 50));
		FontAsset(U"Medium_20")(U"	https://dova-s.jp/bgm/play12790.html").draw(Scene::Center().movedBy(-250, 100));
	}

	// 8ページ目
	if (About_Menu_Select == 7)
	{
		FontAsset(U"Medium_40")(U"ゲームのBGM").draw(Scene::Center().movedBy(-350, -100));
		FontAsset(U"Medium_30")(U"曲名 : サイバーポップ").draw(Scene::Center().movedBy(-250, -50));
		FontAsset(U"Medium_30")(U"作曲者 : マニーラ").draw(Scene::Center().movedBy(-250, 0));
		FontAsset(U"Medium_30")(U"ダウンロード元 :").draw(Scene::Center().movedBy(-250, 50));
		FontAsset(U"Medium_20")(U"	https://dova-s.jp/bgm/play15425.html").draw(Scene::Center().movedBy(-250, 100));
	}

	// 右へ
	if (About_Menu_Select < About_Menu_Max - 1)
	{
		FontAsset(U"Medium_60")(U"→").drawAt(Scene::Center().movedBy(350, 260));
	}

	// 左へ
	if (About_Menu_Select > 0)
	{
		FontAsset(U"Medium_60")(U"←").drawAt(Scene::Center().movedBy(-350, 260));
	}

	// Exit
	FontAsset(U"Medium_30")(U"Exit : Escape").draw(Scene::Center().movedBy(-375, -285));
}

