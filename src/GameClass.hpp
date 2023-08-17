#pragma once
#include "Common.hpp"

class Area
{
	int AreaSize = 100;
public:
	int areainfo;
	Rect wall;
	Texture wallpng;
	Texture blank;
	Texture blue;
	Texture red;
	Texture goal;
	Area()
		:wallpng(U"image/all tile/wall_tile.png")
		, blank(U"image/all tile/blank_tile.png")
		, blue(U"image/all tile/blue_tile.png")
		, red(U"image/all tile/red_tile.png")
		, goal(U"image/all tile/goal_tile.png")
		//, areainfo(Random(0, 2))//mazeが出来たら消して@maze
	{}
	void draw(int i, int j, int x, int y)
	{
		wall.pos = Point(i * AreaSize - x, j * AreaSize - y);
		wall.size = Point(AreaSize, AreaSize);
		if (areainfo == 0)
		{
			blank.resized(100).draw(wall.pos);
		}
		if (areainfo == 1)//その座標が壁なら壁を描画
		{
			wallpng.resized(100).draw(wall.pos);
		}
		if (areainfo == 2)
		{
			goal.resized(100).draw(wall.pos);
		}
		if (areainfo == 3)
		{
			blue.resized(100).draw(wall.pos);
		}
		if (areainfo == 4)
		{
			red.resized(100).draw(wall.pos);
		}
	}
};

class Player
{
	int speed=0;
	Circle play;
	Texture red;
	Texture blue;
	Texture main;
	Area area;
	int t;
	int direc;
	int patterns[4];
	Font font;
	bool Domove;
	int olddirec;
	int n;
public:
	Player()
		:play(Scene::Center(), 20)
	,basespeed(4)
		,direc(0)
		,t(0)
		,patterns{1,2,1,0}
		,Domove(0)
		,font(25)
		,olddirec(100)
		,blue(U"image/blueplayer_all_motion/bp_motion.png")
	,red(U"image/redplayer_all_motion/rp_motion.png"){}
	Size pos;
	Size oldpos;
	int basespeed;
	String name;
	void draw(int p)//描画
	{
		font(name).drawAt(Scene::Center().x, Scene::Center().y -30,Palette::Black);
		t++;
		if (direc != 0)
		{
			n = t / 15 % 4;
		}
		else
		{
			n = 0;
		}
		if (p == 2)
		{
			main = red;
		}
		else
		{
			main = blue;
		}
		if (Domove == 0)
		{
			if (olddirec == 1)
			{
				main(patterns[n] * 20, 56, 20, 28).scaled(2).drawAt(Scene::Center());
			}
			else if (olddirec == 11)
			{
				main((patterns[n] + 3) * 20, 56, 20, 28).scaled(2).drawAt(Scene::Center());
			}
			else if (olddirec == 10)
			{
				main(patterns[n] * 20, 84, 20, 28).scaled(2).drawAt(Scene::Center());
			}
			else if (olddirec == 110)
			{
				main((patterns[n] + 3) * 20, 84, 20, 28).scaled(2).drawAt(Scene::Center());
			}
			else if (olddirec == 1100)
			{
				main((patterns[n] + 3) * 20, 0, 20, 28).scaled(2).drawAt(Scene::Center());
			}
			else if (olddirec == 1000)
			{
				main(patterns[n] * 20, 28, 20, 28).scaled(2).drawAt(Scene::Center());
			}
			else if (olddirec == 1001)
			{
				main((patterns[n] + 3) * 20, 28, 20, 28).scaled(2).drawAt(Scene::Center());
			}
			else if (olddirec == 100)
			{
				main(patterns[n] * 20, 0, 20, 28).scaled(2).drawAt(Scene::Center());
			}
		}
		else if (direc == 1)
		{
			main(patterns[n] * 20, 56, 20, 28).scaled(2).drawAt(Scene::Center());
			olddirec = direc;
		}
		else if (direc == 11)
		{
			main((patterns[n] + 3) * 20, 56, 20, 28).scaled(2).drawAt(Scene::Center());
			olddirec = direc;
		}
		else if (direc == 10)
		{
			main(patterns[n] * 20, 84, 20, 28).scaled(2).drawAt(Scene::Center());
			olddirec = direc;
		}
		else if (direc == 110)
		{
			main((patterns[n] + 3) * 20, 84, 20, 28).scaled(2).drawAt(Scene::Center());
			olddirec = direc;
		}
		else if (direc == 1100)
		{
			main((patterns[n] + 3) * 20, 0, 20, 28).scaled(2).drawAt(Scene::Center());
			olddirec = direc;
		}
		else if (direc == 1000)
		{
			main(patterns[n] * 20, 28, 20, 28).scaled(2).drawAt(Scene::Center());
			olddirec = direc;
		}
		else if (direc == 1001)
		{
			main((patterns[n] + 3) * 20, 28, 20, 28).scaled(2).drawAt(Scene::Center());
			olddirec = direc;
		}
		else if (direc == 100)
		{
			main(patterns[n] * 20, 0, 20, 28).scaled(2).drawAt(Scene::Center());
			olddirec = direc;
		}
		else
		{
			if (olddirec == 1)
			{
				main(patterns[n] * 20, 56, 20, 28).scaled(2).drawAt(Scene::Center());
			}
			else if (olddirec == 11)
			{
				main((patterns[n] + 3) * 20, 56, 20, 28).scaled(2).drawAt(Scene::Center());
			}
			else if (olddirec == 10)
			{
				main(patterns[n] * 20, 84, 20, 28).scaled(2).drawAt(Scene::Center());
			}
			else if (olddirec == 110)
			{
				main((patterns[n] + 3) * 20, 84, 20, 28).scaled(2).drawAt(Scene::Center());
			}
			else if (olddirec == 1100)
			{
				main((patterns[n] + 3) * 20, 0, 20, 28).scaled(2).drawAt(Scene::Center());
			}
			else if (olddirec == 1000)
			{
				main(patterns[n] * 20, 28, 20, 28).scaled(2).drawAt(Scene::Center());
			}
			else if (olddirec == 1001)
			{
				main((patterns[n] + 3) * 20, 28, 20, 28).scaled(2).drawAt(Scene::Center());
			}
			else if (olddirec == 100)
			{
				main(patterns[n] * 20, 0, 20, 28).scaled(2).drawAt(Scene::Center());
			}
		}
		if (Domove == 1)
		{
			//olddirec = direc;
			direc = 0;
		}
		Domove = 0;
	}
	Size getpos()//本当の座標の取得
	{
		return Size{ pos.x + 400,pos.y + 300 };
	}
	Size getareapos()//マス目単位での座標の取得
	{
		return Size{ getpos() / 100 };
	}
	void setareapos(int i,int j)
	{
		pos = { i * 100 - 350,j * 100 - 250 };
	}
	bool getgoal(int info)
	{
		if (info == 2)
		{
			if (KeyEnter.pressed())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	void GearChange(int info,int p)//速度変更
	{
		if (p == 1)
		{
			if (info == 3)
			{
				speed = basespeed*1.5;
			}
			else if (info == 4)
			{
				speed = basespeed*0.5;
			}
			else
			{
				speed = basespeed;
			}
		}
		if (p == 2)
		{
			if (info == 4)
			{
				speed = basespeed*1.5;
			}
			else if (info == 3)
			{
				speed = basespeed*0.5;
			}
			else
			{
				speed = basespeed;
			}
		}
	}
	void GetRoad(int p,int &info)
	{
		if (p == 1)
		{
			if (info == 0 || info == 4)
			{
				info =3;
			}
			else
			{
				info= info;
			}
		}
		if (p == 2)
		{
			if (info == 0 || info == 3)
			{
				info= 4;
			}
			else
			{
				info= info;
			}
		}
	}
	int collision(Line b,int c)//壁の辺に触れたら０を出力
	{
		if (!play.intersects(b))
		{
			return 1;
		}
		else
		{
			if (c == 1)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}
	void TouchWall(int left, int right, int top, int bottom)
	{
		if (bottom == 0)
		{
			pos.y = pos.y + speed;
		}
		if (top == 0)
		{
			pos.y = pos.y - speed;
		}
		if (left == 0)
		{
			pos.x = pos.x - speed;
		}
		if (right == 0)
		{
			pos.x = pos.x + speed;
		}
	}
	void move()//動き
	{
		if (KeyUp.pressed())
		{
			pos.y = pos.y - speed;
		}
		if (KeyDown.pressed())
		{
			pos.y = pos.y + speed;
		}
		if (KeyRight.pressed())
		{
			pos.x = pos.x + speed;
		}
		if (KeyLeft.pressed())
		{
			pos.x = pos.x - speed;
		}
	}
	void GetDirection()
	{
		if (getpos().y < oldpos.y)
		{
			direc += 1;
			Domove = 1;
		}
		if (getpos().y > oldpos.y)
		{
			direc += 100;
			Domove = 1;
		}
		if (getpos().x < oldpos.x)
		{
			direc += 1000;
			Domove = 1;
		}
		if (getpos().x > oldpos.x)
		{
			direc += 10;
			Domove = 1;
		}
	}
};

class GameTimer
{
	const Font font=100;
	//分数*60*fps
	int time = 5*60*60;
	int Etime = 0;
public:
	void update()
	{
		time--;
		Etime++;
	}
	int gettime()
	{
		return time/60;
	}
	int getEtime()
	{
		return Etime/60;
	}
	//残り時間の描画
	void draw()
	{
		if (time > 0)
		{
			if ((time / 60 % 60) < 10)
			{
				font(time / 60 / 60, U":0", time / 60 % 60).draw(0, 0);
			}
			else
			{
				font(time / 60 / 60, U":", time / 60 % 60).draw(0, 0);
			}
		}
	}
	void GameClearTime()//片方がクリア時に時間変更
	{
		if (time >= 30 * 60)
		{
			time = 30 * 60;
		}
	}
	bool  TimeOver()//時間切れ
	{
		if (time == 0)
		{
			return 1;
		}

		return 0;
	}
};

class Player2
{
	Circle p2;
	Texture red;
	Texture blue;
	Texture main;
	int t;
	int direc;
	int patterns[4];
	bool Domove;
	Font font;
	int olddirec;
	int n;
public:
	Player2()
		:red(U"image/redplayer_all_motion/rp_motion.png")
		,blue(U"image/blueplayer_all_motion/bp_motion.png")
		, pos{0,0}
		, oldpos{0,0}
		, direc(0)
		, t(0)
		, patterns{ 1,2,1,0 }
		,font(25)
		, Domove(0)
		, olddirec(100){}
	Size pos;
	Size oldpos;
	String name;
	void draw(Size p1pos,int p)
	{
		p2.center = pos-p1pos;
		p2.r = 10;
		//p2.draw();t++;
		t++;
		font(name).drawAt(pos.x - p1pos.x,pos.y-p1pos.y-30,Palette::Black);
		if (direc != 0)
		{
			n = t / 15 % 4;
		}
		else
		{
			n = 0;
		}
		if (p == 1)
		{
			main = red;
		}
		else
		{
			main = blue;
		}
		if (Domove == 0)
		{
			if (olddirec == 1)
			{
				main(patterns[n] * 20, 56, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
			else if (olddirec == 11)
			{
				main((patterns[n] + 3) * 20, 56, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
			else if (olddirec == 10)
			{
				main(patterns[n] * 20, 84, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
			else if (olddirec == 110)
			{
				main((patterns[n] + 3) * 20, 84, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
			else if (olddirec == 1100)
			{
				main((patterns[n] + 3) * 20, 0, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
			else if (olddirec == 1000)
			{
				main(patterns[n] * 20, 28, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
			else if (olddirec == 1001)
			{
				main((patterns[n] + 3) * 20, 28, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
			else if (olddirec == 100)
			{
				main(patterns[n] * 20, 0, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
		}
		else if (direc == 1)
		{
			main(patterns[n] * 20, 56, 20, 28).scaled(2).drawAt(pos - p1pos);
			olddirec = direc;
		}
		else if (direc == 11)
		{
			main((patterns[n] + 3) * 20, 56, 20, 28).scaled(2).drawAt(pos - p1pos);
			olddirec = direc;
		}
		else if (direc == 10)
		{
			main(patterns[n] * 20, 84, 20, 28).scaled(2).drawAt(pos - p1pos);
			olddirec = direc;
		}
		else if (direc == 110)
		{
			main((patterns[n] + 3) * 20, 84, 20, 28).scaled(2).drawAt(pos - p1pos);
			olddirec = direc;
		}
		else if (direc == 1100)
		{
			main((patterns[n] + 3) * 20, 0, 20, 28).scaled(2).drawAt(pos - p1pos);
			olddirec = direc;
		}
		else if (direc == 1000)
		{
			main(patterns[n] * 20, 28, 20, 28).scaled(2).drawAt(pos - p1pos);
			olddirec = direc;
		}
		else if (direc == 1001)
		{
			main((patterns[n] + 3) * 20, 28, 20, 28).scaled(2).drawAt(pos - p1pos);
			olddirec = direc;
		}
		else if (direc == 100)
		{
			main(patterns[n] * 20, 0, 20, 28).scaled(2).drawAt(pos - p1pos);
			olddirec = direc;
		}
		else
		{
			if (olddirec == 1)
			{
				main(patterns[n] * 20, 56, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
			else if (olddirec == 11)
			{
				main((patterns[n] + 3) * 20, 56, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
			else if (olddirec == 10)
			{
				main(patterns[n] * 20, 84, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
			else if (olddirec == 110)
			{
				main((patterns[n] + 3) * 20, 84, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
			else if (olddirec == 1100)
			{
				main((patterns[n] + 3) * 20, 0, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
			else if (olddirec == 1000)
			{
				main(patterns[n] * 20, 28, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
			else if (olddirec == 1001)
			{
				main((patterns[n] + 3) * 20, 28, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
			else if (olddirec == 100)
			{
				main(patterns[n] * 20, 0, 20, 28).scaled(2).drawAt(pos - p1pos);
			}
		}
		if (Domove == 1)
		{
			//olddirec = direc;
			direc = 0;
		}
		Domove = 0;
	}
	void GetRoad(int p, int &info)
	{
		if (p == 2)
		{
			if (info == 0 || info == 4)
			{
				info= 3;
			}
			else
			{
				info=info;
			}
		}
		if (p == 1)
		{
			if (info == 0 || info == 3)
			{
				info=4;
			}
			else
			{
				info=info;
			}
		}
	}
	void GetDirection()
	{
		if ( pos.y < oldpos.y)
		{
			direc += 1;
			Domove = 1;
		}
		if (pos.y > oldpos.y)
		{
			direc += 100;
			Domove = 1;
		}
		if (pos.x < oldpos.x)
		{
			direc += 1000;
			Domove = 1;
		}
		if (pos.x > oldpos.x)
		{
			direc += 10;
			Domove = 1;
		}
	}
};

class LogStr//左下に表示するログのクラス
{
	Array<String> i;
	//String i[5];
	int val;
	Font font;
public:
	LogStr()
		:font(25)
		, val(5)
	{
		i.resize(val, U"");
	}

	void StringIn(String a)//表示したい文章を打ち込めばok
	{
		//for (int j = val - 1; j > 0; j--)
		//{
		//	i[j] = i[j - 1];
		//}
		//i[0] = a;

		i.pop_back();
		i.push_front(a);
	}

	void update()
	{
		for (int j = 0; j < val; j++)
		{
			font(i[j]).draw(0, 560 - j * 25, Palette::White);
		}
	}
};

//琢磨
class Item {

public:
	enum type {
		nothing = -1,
		speedup = 0,
		speeddown,
		visionup,
		visiondown,
		dir_to_player,
		dir_to_goal,
	};

	Texture img, vision_scale_up, vision_scale_down;
	Rect decision;
	Size pos, message_pos;
	int Situation;// 0->持っていない 1->持ってる 2->使ってる 3->使用済み
	int availableTime;
	type info;
	String message;

	Item(int tmp_type)
		:decision(Scene::Center(), 40, 40)
		, Situation(0)
		, pos(3, 3)
		, availableTime(10 * 60)//秒*フレーム
		, info((type)tmp_type)
		, message_pos(0, -250)
	{
		vision_scale_up = TextureAsset(U"vision_Image2");
		vision_scale_down = TextureAsset(U"vision_Image0");
		switch (info)
		{
		case Item::speedup:
			img = TextureAsset(U"Item_Image5");
			availableTime = 10 * 60;

			break;
		case Item::speeddown:
			img = TextureAsset(U"Item_Image4");
			availableTime = 10 * 60;

			break;
		case Item::visionup:
			img = TextureAsset(U"Item_Image2");
			availableTime = 10 * 60;

			break;
		case Item::visiondown:
			img = TextureAsset(U"Item_Image3");
			availableTime = 10 * 60;

			break;
		case Item::dir_to_player:
			img = TextureAsset(U"Item_Image0");
			availableTime = 10 * 60;

			break;
		case Item::dir_to_goal:
			img = TextureAsset(U"Item_Image1");
			availableTime = 5 * 60;

			break;
		default:
			break;
		}
	}

	bool Obtain(Size AreaPos) {
		if (AreaPos == pos && Situation == 0) {
			Situation = 1;
			return true;
		}
		else {
			return false;
		}

	}

	void Time() {
		if (Situation == 2)availableTime--;

		if (availableTime <= 0) Situation = 3;
	}

	void draw(Size PlayerPos) {
		decision.pos = pos * 100 - PlayerPos + Size{ 50,50 } - decision.size / 2;

		switch (Situation)
		{
		case 0:
			img.scaled(.1).drawAt(pos * 100 - PlayerPos + Size{ 50,50 });

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		default:
			break;
		}

	}

	void draw_dirToGoal(Size player, Size goal) {
		Line{ Size(goal.y,goal.x) * 100 - player + Size{50,50},400,300 }.draw(LineStyle::SquareDot, 10, Palette::Greenyellow);
	}

	void draw_dirToPl2(Size player, Size Pl2) {
		Line{ Pl2 - player ,400,300 }.draw(LineStyle::SquareDot, 10, Palette::Greenyellow);
	}

	String get_message() {
		switch (Situation)
		{
		case 0:
			message = U"";

			break;
		case 1:
			message = U"使用できます";

			break;
		case 2:
			message = (U"あと{}秒"_fmt((int)availableTime / 60));

			break;
		case 3:
			message = U"";

			break;
		default:
			break;
		}

		return message;
	}



private:



protected:
	Player pl;

};

class Gen_Item {

public:
	Array<Item> items;
	Array<Item> own_items;
	Array<int> used_items;
	Array<int> type_ar;
	int gen_num;
	Font font;

	Gen_Item(Size MapSize)
		:gen_num(10)
		, font(40)
	{

		own_items = { Item(-1),Item(-1),Item(-1) };
		
		for (auto i : step(gen_num)) {
			type_ar << Random(5);
			items << Item(type_ar[i]);
			items[i].pos = GetPos(MapSize);
		}
	}

	void draw_inventory() {
		for (auto i : step(3)) {
			if (own_items.size() > i && own_items[i].info>=0) {
					if (own_items[i].Situation == 1) {
						own_items[i].img.scaled(.1).drawAt(i*50+650, 550, Palette::Green);
					}
					else if (own_items[i].Situation == 2) {
							FontAsset(U"Medium_40")(U"{}"_fmt((int)own_items[i].availableTime / 60)).drawAt(i*50+650, 550, Palette::Yellow);
					}
			}
			else {
				FontAsset(U"Medium_40")(U"✖").drawAt(i * 50 + 650, 550);
			}

		}
	}

private:

	Size GetPos(Size MapSize) {
		return Size(Random((MapSize.x - 3) / 2) * 2 + 1, Random((MapSize.x - 3) / 2) * 2 + 1);
	}

};
//琢磨
