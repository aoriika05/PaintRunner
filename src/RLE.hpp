#pragma once
# include <Siv3D.hpp>
# include <functional>
# include <sstream>

class RLE
{
public:
	String make(Grid<int32> que, int col, int row);
	Grid<int32>reverse(String data, int col, int row, int *goalc, int *goalr);
};

