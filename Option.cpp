#include "Option.hpp"
#include "ENCRYPTED_PHOTON_APP_ID.SECRET"

Option::Option(const InitData& init)
	: IScene{ init }
{
	// INIファイル
// 全てのセクションを列挙
	for (const auto& section : Matching_ini.sections())
	{
		if (section.section == U"Audio")	// Audioセクション
		{
			// セクション内のすべてのキーを列挙
			for (const auto& key : section.keys)
			{
				if (key.name == U"Matching_BGM")	// Matchingキー
				{
					Matching_Audio_BGM_num = Parse<uint8>(key.value);
				}
			}
		}
	}

	if (net == nullptr)
	{
		const std::string encryptedAppID{ SIV3D_OBFUSCATE(PHOTON_APP_ID) };
		const String appID = Unicode::WidenAscii(encryptedAppID);

		net = new MyNetwork(appID, U"1.0");

		net->connect(U"{}"_fmt(Random()));
	}
}

void Option::update()
{
	// 音楽
	// 曲が流れてるか判定
	if (AudioAsset(U"Matching_BGM" + Format(Matching_Audio_BGM_num)).isPlaying() == false)
	{
		AudioAsset(U"Matching_BGM" + Format(Matching_Audio_BGM_num)).play(MixBus0);
	}

	if (net->isconnect)
	{
		Big_GameTransition.update(Big_Button.mouseOver());
		Medium_GameTransition.update(Medium_Button.mouseOver());
		Small_GameTransition.update(Small_Button.mouseOver());
		Next_GameTransition.update(Next_Button.mouseOver());


		if (Big_Button.mouseOver()) {
			// 手のアイコンに変更
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (Medium_Button.mouseOver()) {
			// 手のアイコンに変更
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (Medium_Button.mouseOver()) {
			// 手のアイコンに変更
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		//迷路大
		if (Big_Button.leftClicked())
		{
			
			MazeSize = Size{ 73,73 };
			DigNum = 200;
			changeScene(State::Match);
		}
		//迷路中
		if (Medium_Button.leftClicked())
		{
			MazeSize = Size{ 51,51 };
			DigNum = 100;
			changeScene(State::Match);
		}
		//迷路小
		if (Small_Button.leftClicked())
		{
			MazeSize = Size{ 41,41 };
			DigNum = 50;
			changeScene(State::Match);
		}

		Roomnums = getRoomNum();
	}

	//タイトル画面へ
	if (SimpleGUI::Button(U"←", Vec2(30, 30)))
	{
		AudioAsset(U"Matching_BGM" + Format(Matching_Audio_BGM_num)).stop();
		changeScene(State::Title);
	}

	net->update();
}

void Option::draw() const
{
	if(!net->isInRoom())
	{
		if (net->errorconnect)
			FontAsset(U"Medium_40")(U"サーバーへの接続に失敗しました").drawAt(center);
		else if (!net->isconnect)
			FontAsset(U"Medium_40")(U"サーバーに接続中です").drawAt(center);
		else if (net->isconnect)
		{
			FontAsset(U"Medium_40")(U"サーバーに接続完了しました").drawAt(center+Vec2(0,-200));
		}
	}

	if (net->isconnect&&!Roomnums.empty())
	{
		// 背景
		// 背景色
		Scene::SetBackground(ColorF(0.3, 0.4, 0.5));

		// ボタン
			// 迷路大ボタン
		Big_Button.draw(ColorF{ 1.0, 1.0, 1.0, 1.0 });
		// 内部の文字
		FontAsset(U"Medium_40")(U"BIG  {}"_fmt(Roomnums.at('B').first)).drawAt(Big_Button.center(), ColorF{0, Roomnums.at('B').second?1.0:0, 0, 1.0 - Big_GameTransition.value() * 0.5});	// トランザクションによって中の色の透明度が変わる


		// 迷路中ボタン
		Medium_Button.draw(ColorF{ 1.0, 1.0, 1.0, 1.0 });
		// 内部の文字
		FontAsset(U"Medium_40")(U"MEDIUM  {}"_fmt(Roomnums.at('M').first)).drawAt(Medium_Button.center(), ColorF{ 0, Roomnums.at('M').second ? 1.0 : 0, 0, 1.0 - Medium_GameTransition.value() * 0.5 });	// トランザクションによって中の色の透明度が変わる

		// 迷路小ボタン
		Small_Button.draw(ColorF{ 1.0, 1.0, 1.0, 1.0 });
		// 内部の文字
		FontAsset(U"Medium_40")(U"SMALL  {}"_fmt(Roomnums.at('S').first)).drawAt(Small_Button.center(), ColorF{ 0, Roomnums.at('S').second ? 1.0 : 0, 0, 1.0 - Small_GameTransition.value() * 0.5});	// トランザクションによって中の色の透明度が変わる

		// NEXTボタン
		//Next_Button.draw(ColorF{ 1.0, 1.0, 1.0, 1.0 });
		// 内部の文字
		//FontAsset(U"Medium_40")(U"NEXT").drawAt(Next_Button.center(), ColorF{ 0, 0, 0, 1.0 - Next_GameTransition.value() * 0.5 });	// トランザクションによって中の色の透明度が変わる

		//迷路大
		if (Big_Button.leftClicked())
		{
			font(U"迷路の大きさ＝大").drawAt(center);
		}
		//迷路中
		if (Medium_Button.leftClicked())
		{

			font(U"迷路の大きさ＝中").drawAt(center);
		}
		//迷路小
		if (Small_Button.leftClicked())
		{
			font(U"迷路の大きさ＝小").drawAt(center);

		}
	}
}


