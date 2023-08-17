# include <Siv3D.hpp> // OpenSiv3D v0.6.2
# include "NetworkSystem.hpp"
# include "Common.hpp"
# include "Sivphoton.hpp"
# include "mapinfo.hpp"


///タイルの変更処理
///@param chginfo 座標と変更する番号(y, x, 番号)
///@param from_p プレイヤーから呼ぶ分にはデフォのままでいい
void Mapinfo::chgtile(Array<int32> chginfo, bool from_p = true) {

	if (chginfo[2] == p1tileid) {							//1Pの塗ったタイルが増えてたら増やす
		p1tile++;
		if (mapdata[chginfo[0]][chginfo[1]] == p2tileid) {	//2Pのタイルを塗り返していたら減らす
			p2tile--;
		}
	}
	else if (chginfo[2] == p2tileid) {						//2Pの塗ったタイルが増えてたら増やす
		p2tile++;
		if (mapdata[chginfo[0]][chginfo[1]] == p1tileid) {	//1Pのタイルを塗り返していたら減らす
			p1tile--;
		}
	}

	//ここまで得点処理

	mapdata[chginfo[0]][chginfo[1]] = chginfo[2];		//自マップデータの更新

	if (from_p) {				//他のプレイヤーから送られてきて実行した場合にまた送らないようにする
		sendmapchg(chginfo);
	}
}

void Mapinfo::sendmapchg(Array<int32> SendData) {
	//net->opRaiseEvent(1, SendData);
}
