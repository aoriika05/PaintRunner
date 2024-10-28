#pragma once
#include"Common.hpp"

class Mapinfo{
private:
	const int8 p1tileid = 3;	//1PのタイルID
	const int8 p2tileid = 4;	//2PのタイルID
	Grid<int32> mapdata;		//マップデータ
	int32 p1tile;				//1Pのタイルの数
	int32 p2tile;				//2Pのタイルの数
	void sendmapchg(Array<int32>);
public:
	Mapinfo();
	void gridinport(Grid<int32>);
	void chgtile(Array<int32>, bool);
	void pointreset();
	Array<int32> result();
};

inline Mapinfo::Mapinfo() {
	p1tile = 0;
	p2tile = 0;
}

inline Array<int32> Mapinfo::result() {
	return { Mapinfo::p1tile, Mapinfo::p2tile };
}

/// @brief 塗ったマス数のリセット
inline void Mapinfo::pointreset() {
	p1tile = 0;
	p2tile = 0;
	mapdata.clear();
}

/// @brief マップデータのインポート 
/// @param inport マップデータのGrid
inline void Mapinfo::gridinport(Grid<int32> inport) {
	mapdata = inport;
}
