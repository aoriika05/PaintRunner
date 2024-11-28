# pragma once
# include "Common.hpp"
# include "Maze.hpp"
# include "GameClass.hpp"

// ゲームシーン
class Game : public App::Scene
{
public:

	Game(const InitData& init);

	void update() override;
	
private:

	// INIファイル
	// INI ファイルからデータを読み込む
	INI Game_ini{ U"config.ini" };


	// Audioの設定
	// Audioの番号
	uint8 Game_Audio_BGM_num;


	//前の行動から次の行動を予測する
	inline void ActPrediction();

	int left, right, top, bottom, temp1, temp2;
	bool GOALFRAG1 = 0, GOALFRAG2 = 0, GOALTIME = 0,Time1=0,Time2=0;
	int playernum;
	Size Goal;
	LogStr log;
	GameTimer time;
	Player player;
	Player2 player2;
	bool getname;
	//琢磨
	Gen_Item GI = Gen_Item(inl_MazeSize);
	Item voidItem=Item(0);

	Array<int> ItemUsed = { 0,0,0 };
	//琢磨
	Grid<Area> area;//mazeが出来たらここ使って

	Stopwatch MapSharedSw;

	int FPS = 60; // 1秒間に1画面を書き換える回数
	Stopwatch sw;   //FPS60
	

	Texture vision_default=TextureAsset(U"vision_Image1");

	Texture vision = vision_default;

	const int Rollbackms=40;

	bool isonce = true;

	Grid<int> m_PaintArea;

	double CountDownNum = 3.0;
	Font CountDownFont = Font(50);

	Optional<Grid<int>> oldMapState;
};

void Game::ActPrediction()
{
	if ((net->enpositons[0] - net->enpositons[1]) != Size::Zero())
	{
		player2.pos.moveBy(Size(static_cast<int>(Vec2(net->enpositons[0] - net->enpositons[1]).normalize().x), static_cast<int>(Vec2(net->enpositons[0] - net->enpositons[1]).normalize().y)) * 4);
	}
}



