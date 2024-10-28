#include <Siv3D.hpp>
#include <sstream>
#include <functional>
#include "RLE.hpp"

String RLE::make(Grid<int32> que, int col, int row)
{
	// 圧縮文字列・比較元・カウンタ作成
	int buf = -1, chacount = 0, concount = 0;
	String data, temp;
	data.clear();
	temp.clear();

	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			// 連続の場合
			if (buf == que[i][j])
			{
				if (chacount > 0)
				{
					// 異なる数とその文字列の出力
					data += U"-" + Format(chacount) + temp;
					temp.clear();
					chacount = 0;
				}
				concount++;
			}
			else	// 違う文字になった場合
			{
				switch (que[i][j])
				{
					case 0:
						if (concount > 0)
						{
							// 連続数の出力
							data += Format(concount) + U" ";
							concount = 0;
						}
						// dataに格納し、次の文字を数える
						temp += U"a";
						buf = que[i][j];
						chacount++;
						break;
					case 1:
						if (concount > 0)
						{
							data += Format(concount) + U" ";
							concount = 0;
						}
						temp += U"b";
						buf = que[i][j];
						chacount++;
						break;
					case 2:
						if (concount > 0)
						{
							data += Format(concount) + U" ";
							concount = 0;
						}
						temp += U"c";
						buf = que[i][j];
						chacount++;
						break;
				}
			}
		}
	}
	// 最後の排出
	if (concount > 0)
	{
		data += Format(concount);
	}

	return data;
}

Grid<int32> RLE::reverse(String data, int col, int row, int *goalc, int *goalr)
{
	// 展開先grid・カウンタ作成
	Grid<int32> grid(row, col, -1);
	int colc = 0, rowc = 0;


	// 圧縮文字列が空になるまで
	while (data != U"")
	{
		// Stringをstd::stringにしてstd::stringstreamに格納
		std::stringstream ssdata{data.narrow()};

		// std::stringstreamから先頭の単語を切り取り
		std::string buf;
		ssdata >> buf;
		data = data.erase(0, buf.length() + 1);

		// 異なるのマス目の数を取得
		std::stringstream Temp{buf};
		int chanum;	// 先頭の数
		Temp >> chanum;
		std::string del = std::to_string(chanum);
		buf = buf.erase(0, del.length());
		chanum *= -1;

		// 異なるマス目情報の取得・切り取り・復元
		char cbit = buf[0];
		// 出力回数
		for (int i = 0; i < chanum; i++)
		{
			cbit = buf[0];
			buf.erase(0, 1);
			switch (cbit)
			{
				case 'a':
					// オーバーフロー時
					if (colc >= col)
					{
						throw Error(U"Over");
					}
					else if (rowc >= row)	// 行のサイズ超
					{
						colc++;
						rowc = 0;
					}
					// 通常時
						grid[colc][rowc] = 0;
						rowc++;					
					break;
				case 'b':
					if (colc >= col)
					{
						throw Error(U"Over");
					}
					else if (rowc >= row)
					{
						colc++;
						rowc = 0;
					}
						grid[colc][rowc] = 1;
						rowc++;
					break;
				case 'c':
					if (colc >= col)
					{
						throw Error(U"Over");
					}
					else if (rowc >= row)
					{
						colc++;
						rowc = 0;
					}
						// ゴールの座標格納
						*goalc = colc;
						*goalr = rowc;
						grid[colc][rowc] = 1;
						rowc++;
					break;
			}
		}


		// マス目の数を取得
		int connum;
		connum = std::stoi(buf);

		switch (cbit)
		{
		case 'a':
			// 出力回数
			for(int i = 0;i < connum; i++)
			{
				// オーバーフロー時
				if (colc >= col)
				{
					Console << (U"Over");
					getchar();
				}
				else if (rowc >= row)	// 行のサイズ超
				{
					colc++;
					rowc = 0;
					i--;
				}
				else	// 通常時
				{
					grid[colc][rowc] = 0;
					rowc++;
				}
			}
			break;
		case 'b':
			for (int i = 0; i < connum; i++)
			{
				if (colc >= col)
				{
					Console << (U"Over");
					getchar();
				}
				else if (rowc >= row)
				{
					colc++;
					rowc = 0;
					i--;
				}
				else
				{
					grid[colc][rowc] = 1;
					rowc++;
				}
			}
			break;
		case 'c':
			for (int i = 0; i < connum; i++)
			{
				if (colc >= col)
				{
					Console << (U"Over");
					getchar();
				}
				else if (rowc >= row)
				{
					colc++;
					rowc = 0;
					i--;
				}
				else
				{
					*goalc = colc;
					*goalr = rowc;
					grid[colc][rowc] = 1;
					rowc++;
				}
			}
			break;
		}
	}

	return grid;
}
