#include <exception>
#include <functional>

#include "sudoku.h"
#include "bitwise.h"


bool row_apply(Sudoku &sudoku, int row, int col, std::function<int(int)> func)
{
	bool changed = false;
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
		if (next != prev)
		{
			if (is_solved(prev))
			{
				throw std::exception("tried to modify an already-solved cell.");
			}
			changed = true;
			sudoku(row, i) = next;
			if (!sudoku.is_valid())
			{
				throw std::exception("invalid board.");
			}
		}
	}
	return changed;
}

bool col_apply(Sudoku &sudoku, int row, int col, std::function<int(int)> func)
{
	sudoku.transpose();
	bool changed = row_apply(sudoku, col, row, func);
	sudoku.transpose();
	return changed;
}

bool block_apply(Sudoku &sudoku, int row, int col, std::function<int(int)> func)
{
	bool changed = false;
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
			if (next != prev)
			{
				if (is_solved(prev))
				{
					throw std::exception("tried to modify an already-solved cell.");
				}
				changed = true;
				sudoku(r, c) = next;
				if (!sudoku.is_valid())
				{
					throw std::exception("invalid board.");
				}
			}
		}
	}
	return changed;
}

bool all_apply(Sudoku &sudoku, int row, int col, std::function<int(int)> func)
{
	bool row_changed = row_apply(sudoku, row, col, func);
	bool col_changed = col_apply(sudoku, row, col, func);
	bool block_changed = block_apply(sudoku, row, col, func);
	return (row_changed || col_changed || block_changed);
}

// finds cells who can only be one value,
// and eliminates that value from the cell's neighbors
bool trivial_pass(Sudoku &sudoku)
{
	bool changed = false;
	for (int row = 0; row < 9; ++row)
	{
		for (int col = 0; col < 9; ++col)
		{
			int cell = sudoku(row, col);
			if (is_solved(cell))
			{
				auto subtractor = [&cell](int a) { return subtract(a, cell); };
				bool something_changed = all_apply(sudoku, row, col, subtractor);
				changed = changed || something_changed;
			}
		}
	}
	return changed;
}