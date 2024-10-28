# pragma once
#include "Sivphoton.hpp"

// シーンの名前
enum class State//enumは列挙型上から値がインクリメントされる classをいれることによって値が代入できなくなり安全になる
{

	Title,   // 0
	Option,  // 1 
	Match,   // 2
	Game,    // 3
	Result,  // 4
	Setting, // 5
	SoundBox,	// 6
	Howtoplay,	// 7
	About,	// 8	
};

// 共有するデータ
struct GameData
{
	//constは値が固定されて変更できなくなるので注意

	Grid<int32> maze;
	Grid<int32> ClearMaze;
	Array<int32> ClearTime=Array<int32>(2);
	Array<int32> goal=Array<int32>(2);
	Array<Grid<int>> ChangeMaze;


	// プレイヤー番号
	int pnum;


	//ネットワーク
	MyNetwork* mynetwork;
	int highscore;
	

	//使ったアイテム
	Array<int32> Used1;
	Array<int32> Used2;


	// 音量
	// 全体音量
	double globalVolume;

	// BGM音量
	double MixBus0Volume;

	// SE音量
	double MixBus1Volume;

	// プレイヤーの名前
	// プレイヤー自身の名前
	String UserName;

	// 対戦相手の名前
	String Opponent_name;
};

using App = SceneManager<State, GameData>;//ScenManagerでシーン管理ができる。usingは名前空間内の変数や関数を個別に指定する等
inline MyNetwork* net;

