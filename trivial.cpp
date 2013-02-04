#include <exception>
#include <functional>

#include "sudoku.h"
#include "bitwise.h"


void row_apply(Sudoku &sudoku, int row, int col, std::function<int(int)> func)
{
	for (int i = 0; i < 9; ++i)
	{
		if (i == col)
		{
			continue;
		}
		int prev = sudoku(row, i);
		int next = func(prev);
		if (next == 0)
		{
			throw std::exception("cell with no possibilities left.");
		}
		if (next != prev && is_solved(prev))
		{
			throw std::exception("tried to modify an already-solved cell.");
		}
		sudoku.set(row, i, next);
	}
}

void col_apply(Sudoku &sudoku, int row, int col, std::function<int(int)> func)
{
	sudoku.transpose();
	row_apply(sudoku, col, row, func);
	sudoku.transpose();
}

void block_apply(Sudoku &sudoku, int row, int col, std::function<int(int)> func)
{
	int row_block = row / 3;
	int col_block = col / 3;
	for (int r = row_block * 3; r < (row_block + 1) * 3; ++r)
	{
		for (int c = col_block * 3; c < (col_block + 1) * 3; ++c)
		{
			if ((r == row) && (c == col))
			{
				continue;
			}
			int prev = sudoku(r, c);
			int next = func(prev);
			if (next == 0)
			{
				throw std::exception("cell with no possibilities left.");
			}
			if (next != prev && is_solved(prev))
			{
				throw std::exception("tried to modify an already-solved cell.");
			}
			sudoku.set(r, c, next);
		}
	}
}

void all_apply(Sudoku &sudoku, int row, int col, std::function<int(int)> func)
{
	row_apply(sudoku, row, col, func);
	col_apply(sudoku, row, col, func);
	block_apply(sudoku, row, col, func);
}

// finds cells who can only be one value,
// and eliminates that value from the cell's neighbors
void trivial_pass(Sudoku &sudoku)
{
	for (int row = 0; row < 9; ++row)
	{
		for (int col = 0; col < 9; ++col)
		{
			int cell = sudoku(row, col);
			if (is_solved(cell))
			{
				auto subtractor = [&cell](int a) { return subtract(a, cell); };
				all_apply(sudoku, row, col, subtractor);
			}
		}
	}
}