#include <exception>

#include "sudoku.h"
#include "bitwise.h"

void only_in_row(Sudoku &sudoku, int row)
{
	int cols_who_contain[9] = { 0 };
	for (int col = 0; col < 9; ++col)
	{
		for (int num = 0; num < 9; ++num)
		{
			int num_mask = mask(num);
			if (sudoku(row, col) & num_mask)
			{
				int col_mask = mask(col);
				cols_who_contain[num] |= col_mask;
			}
		}
	}

	for (int num = 0; num < 9; ++num)
	{
		int cols = cols_who_contain[num];
		if (1 == num_ones(cols))
		{
			int col = unmask(cols);
			sudoku.set(row, col, mask(num));
		}
	}
}

void only_in_row_pass(Sudoku &sudoku)
{
	for (int i = 0; i < 9; ++i)
	{
		only_in_row(sudoku, i);
	}
}

void only_in_col_pass(Sudoku &sudoku)
{
	sudoku.transpose();
	only_in_row_pass(sudoku);
	sudoku.transpose();
}

void only_in_block(Sudoku &sudoku, int row_block, int col_block)
{
	int friends_who_contain[9] = { 0 };

	int row_base = row_block * 3;
	int col_base = col_block * 3;

	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			for (int num = 0; num < 9; ++num)
			{
				int num_mask = mask(num);
				if (sudoku(row_base + row, col_base + col) & num_mask)
				{
					int block_mask = blockmask(row, col);
					friends_who_contain[num] |= block_mask;
				}
			}
		}
	}

	for (int num = 0; num < 9; ++num)
	{
		int friends = friends_who_contain[num];
		if (1 == num_ones(friends))
		{
			int row, col;
			blockunmask(friends, row, col);
			if (sudoku(row_base + row, col_base + col) != mask(num))
			{
				sudoku.set(row_base + row, col_base + col, mask(num));
			}
		}
	}
}

void only_in_block_pass(Sudoku &sudoku)
{
	for (int row_block = 0; row_block < 3; ++row_block)
	{
		for (int col_block = 0; col_block < 3; ++col_block)
		{
			only_in_block(sudoku, row_block, col_block);
		}
	}
}
