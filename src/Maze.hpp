#pragma once
#include "Common.hpp" // OpenSiv3D v0.6.2
inline int DigNum;
inline Size MazeSize;

class Maze
{
private:
	Array<Size> Start; //開始地点候補

	Size RowTail(Grid<Size> A, int row)
	{
		Size last = Size(0, 0);
		for (int i = (int)A.width() - 1; i >= 0; i--)
		{
			if (A[row][i] != Size(0, 0))
			{
				last = A[row][i];
				break;
			}
		}
		return last;
	}

	//スタートとゴールをつなぐ最短経路を見つける
	Size CreateRoad()
	{
		Size p, tmp;
		Grid<Size> Roads(1, 1);
		Array<Size> Road;
		Roads[0][0] = Size(1, 1);
		bool CompleteGoal = 0, DeleteRoad = 0;

		while (1)
		{

			DeleteRoad = 0;
			for (auto i : step(Roads.height()))
			{

				Array<Direction> directions = {};
				p = RowTail(Roads, i);

				if (p == Size(MapSize.x - 2, MapSize.y - 2))
				{
					for (auto j : step(Roads.width()))
					{
						Road << Roads[i][j];
						if (Roads[i][j] == Size(MapSize.x - 2, MapSize.y - 2))
							break;
					}
					CompleteGoal = 1;
					break;
				}

				MapToSearch[p.x][p.y] = 1;

				if (MapToSearch[p.x][p.y - 1] == 0)
					directions << (Up);
				if (MapToSearch[p.x + 1][p.y] == 0)
					directions << (Right);
				if (MapToSearch[p.x][p.y + 1] == 0)
					directions << (Down);
				if (MapToSearch[p.x - 1][p.y] == 0)
					directions << (Left);

				switch (directions.size())
				{
				case 0:

					Roads.remove_row(i);
					DeleteRoad = 1;
					break;
				case 1:

					tmp = SetWall(p, directions[0]);
					Roads.resize(Roads.width() + 1, Roads.height());
					for (auto j : step(Roads.width()))
					{
						if (Roads[i][j] == Size(0, 0))
						{
							Roads[i][j] = tmp;
							break;
						}
					}
					break;
				case 2:

					Roads.resize(Roads.width() + 1, Roads.height());

					Roads.resize(Roads.width(), Roads.height() + 1);

					for (auto j : step(Roads.width()))
					{
						Roads[Roads.height() - 1][j] = Roads[i][j];
					}

					tmp = SetWall(p, directions[0]);
					for (auto j : step(Roads.width()))
					{
						if (Roads[i][j] == Size(0, 0))
						{
							Roads[i][j] = tmp;
							break;
						}
					}

					tmp = SetWall(p, directions[1]);
					for (auto j : step(Roads.width()))
					{
						if (Roads[Roads.height() - 1][j] == Size(0, 0))
						{
							Roads[Roads.height() - 1][j] = tmp;
							break;
						}
					}
					break;
				case 3:

					Roads.resize(Roads.width() + 1, Roads.height());
					Roads.resize(Roads.width(), Roads.height() + 2);

					for (auto j : step(Roads.width()))
					{
						Roads[Roads.height() - 1][j] = Roads[i][j];
					}

					for (auto j : step(Roads.width()))
					{
						Roads[Roads.height() - 2][j] = Roads[i][j];
					}

					tmp = SetWall(p, directions[0]);
					for (auto j : step(Roads.width()))
					{
						if (Roads[i][j] == Size(0, 0))
						{
							Roads[i][j] = tmp;
							break;
						}
					}

					tmp = SetWall(p, directions[1]);
					for (auto j : step(Roads.width()))
					{
						if (Roads[Roads.height() - 1][j] == Size(0, 0))
						{
							Roads[Roads.height() - 1][j] = tmp;
							break;
						}
					}

					tmp = SetWall(p, directions[2]);
					for (auto j : step(Roads.width()))
					{
						if (Roads[Roads.height() - 2][j] == Size(0, 0))
						{
							Roads[Roads.height() - 2][j] = tmp;
							break;
						}
					}

					break;
				default:
					break;
				}

				if (i > Roads.height() - 1 || DeleteRoad)
					break;
			}

			if (CompleteGoal)
				break;
		}

		return Road[(int)Road.size() / 2];
	}

	//通路にする&候補確保
	Size SetWall(Size p, int dir)
	{

		switch (dir)
		{
		case Up:
			p.y--;
			break;
		case Right:
			p.x++;
			break;
		case Down:
			p.y++;
			break;
		case Left:
			p.x--;
			break;
		}

		return p;
	}

	//迷路全体を掘り進める
	void Dig(Size p)
	{
		while (1)
		{

			//掘ることのできる方向を格納する配列
			Array<Direction> directions = {};

			//directionsへの格納
			if (p.y > 2)
				if (coordinate[p.x][p.y - 1] == 1 && coordinate[p.x][p.y - 2] == 1)
					directions << (Up);
			if (p.x < MapSize.x - 3)
				if (coordinate[p.x + 1][p.y] == 1 && coordinate[p.x + 2][p.y] == 1)
					directions << (Right);
			if (p.y < MapSize.y - 3)
				if (coordinate[p.x][p.y + 1] == 1 && coordinate[p.x][p.y + 2] == 1)
					directions << (Down);
			if (p.x > 2)
				if (coordinate[p.x - 1][p.y] == 1 && coordinate[p.x - 2][p.y] == 1)
					directions << (Left);

			//掘り進められない場合、ループを抜ける
			if (not directions)
				break;

			//pを掘る
			SetPath(p);

			//directionsの中から掘る方向をランダムに選ぶ
			int32 dirIndex = (int32)Random(directions.size() - 1);

			//選ばれた方向に2マス掘る
			switch (directions[dirIndex])
			{
			case Up:
				SetPath(p + Size(0, -1));
				p.y--;
				SetPath(p + Size(0, -1));
				p.y--;
				break;
			case Right:
				SetPath(p + Size(1, 0));
				p.x++;
				SetPath(p + Size(1, 0));
				p.x++;
				break;
			case Down:
				SetPath(p + Size(0, 1));
				p.y++;
				SetPath(p + Size(0, 1));
				p.y++;
				break;
			case Left:
				SetPath(p + Size(-1, 0));
				p.x--;
				SetPath(p + Size(-1, 0));
				p.x--;
				break;
			}
		}

		//新しく掘り進める座標を取得
		Size cell = GetStart();

		//nullでなかったら掘る
		if (cell != Size(-1, -1))
		{
			Dig(cell);
		}
	}

	//通路にする&候補確保
	void SetPath(Size p)
	{
		//壁を通路にする
		coordinate[p.x][p.y] = 0;

		//マス目がどちらも奇数であれば候補に入れる
		if (p.x % 2 == 1 && p.y % 2 == 1)
		{
			// 穴掘り候補座標
			Start << p;
		}
	}

	//掘り進めなくなった時に候補の中から開始点を選ぶ
	Size GetStart()
	{
		//候補がないなら-1,-1を返す
		if (not Start)
			return Size(-1, -1);

		//候補の中から開始点を選ぶ
		int32 index = (int32)Random(Start.size() - 1);
		Size cell = Start[index];
		//選ばれたものを消す
		Start.remove_at(index);

		return cell;
	}

	//4方向を0~3で表すための列挙
	enum Direction
	{
		Up = 0,
		Right = 1,
		Down = 2,
		Left = 3
	};

public:
	Size MapSize;
	Size Goal;
	Grid<int32> coordinate; //迷路のデータを保存するもの
	Grid<int32> MapToSearch;
	Size Start1;
	Size Start2;


	Maze(Size mazesize = Size{ MazeSize })
		: MapSize{ mazesize } //2n+1
		,
		coordinate(MazeSize.y, MazeSize.x)
	{


		MapSize = MazeSize;
		//外周をすべて通路にしてそれ以外を壁にする
		for (auto i : step(MapSize))
		{
			if ((i.y == 0) || (i.y == MapSize.y - 1) || (i.x == 0) || (i.x == MapSize.x - 1))
			{
				coordinate[i.x][i.y] = 0;
			}
			else
			{
				coordinate[i.x][i.y] = 1;
			}
		}

		//1,1から掘る
		Dig(Size(1, 1));

		//ループを作るためにランダムに壁を通路にする
		RandomDig(DigNum);

		//外周を壁にする
		for (auto i : step(MapSize))
		{
			if ((i.y == 0) || (i.y == MapSize.y - 1) || (i.x == 0) || (i.x == MapSize.x - 1))
			{
				coordinate[i.x][i.y] = 1;
			}
		}

		MapToSearch = coordinate;

		Goal = CreateRoad();
		coordinate[Goal.x][Goal.y] = 2;

		Start1 = Size{ 1,1 };
		Start2 = Size{ MapSize.x - 2,MapSize.y - 2 };
	}

	//n個ランダムに掘る
	void RandomDig(int n)
	{
		Size p;
		while (n > 0)
		{

			//(奇,偶),(偶,奇)をランダムに選ぶ
			p = Size(2 * Random(1, (MapSize.x - 3) / 2), 2 * Random(0, (MapSize.y - 3) / 2) + 1);
			//pがかべであれば壁だったら掘る
			if (coordinate[p.x][p.y] == 1)
			{
				coordinate[p.x][p.y] = 0;
				n--;
			}
			if (coordinate[p.y][p.x] == 1)
			{
				coordinate[p.y][p.x] = 0;
				n--;
			}
		}
	}

	void PrintMaze()
	{
		for (int i = 0; i < MapSize.y; i++)
		{
			Console.writeln();
			for (int j = 0; j < MapSize.x; j++)
			{
				Console.write(coordinate[i][j]);
			}
		}
	}
};



