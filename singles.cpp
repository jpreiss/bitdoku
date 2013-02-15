#include <exception>

#include "sudoku.h"
#include "bitwise.h"
#include "passtools.hpp"

void only_in_row(Sudoku &sudoku, int row)
{
	int cols_who_contain[9];
	sudoku.digit_to_column_map(row, cols_who_contain);

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

void only_in_block(Sudoku &sudoku, int row_block, int col_block)
{
	int friends_who_contain[9] = { 0 };

	sudoku.digit_to_block_map(row_block, col_block, friends_who_contain);

	int row_base = row_block * 3;
	int col_base = col_block * 3;

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

void only_in_row_pass(Sudoku &sudoku)
{
	row_op_pass(sudoku, only_in_row);
}

void only_in_block_pass(Sudoku &sudoku)
{
	block_op_pass(sudoku, only_in_block);
}
