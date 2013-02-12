#include "sudoku.h"
#include "passes.h"
#include "bitwise.h"


void row_doubles(Sudoku &sudoku, int row)
{
	int cols_who_contain[9];
	sudoku.digit_to_column_map(row, cols_who_contain);

	// don't go all the way to 9 because we only look forward for pairs
	for (int num = 0; num < 8; ++num)
	{
		int cols = cols_who_contain[num];
		if (2 == num_ones(cols))
		{
			for (int othernum = num + 1; othernum < 9; ++othernum)
			{
				int othercols = cols_who_contain[othernum];
				if (cols == othercols)
				{
					// found a pair! 
					// remove all other possiblities from these 2 cells
					int digit_pair_mask = mask(num) | mask(othernum);
					int col1, col2;
					lowest_two_set(cols, col1, col2);
					sudoku.set(row, col1, digit_pair_mask);
					sudoku.set(row, col2, digit_pair_mask);
				}
			}
		}
	}
}

void row_double_pass(Sudoku &sudoku)
{
	for (int i = 0; i < 9; ++i)
	{
		row_doubles(sudoku, i);
	}
}

void block_doubles(Sudoku &sudoku, int row_block, int col_block)
{
	int friends_who_contain[9];
	sudoku.digit_to_block_map(row_block, col_block, friends_who_contain);

	int row_base = row_block * 3;
	int col_base = col_block * 3;

	// don't go all the way to 9 because we only look forward for pairs
	for (int num = 0; num < 8; ++num)
	{
		int cells = friends_who_contain[num];
		if (2 == num_ones(cells))
		{
			for (int othernum = num + 1; othernum < 9; ++othernum)
			{
				int othercells = friends_who_contain[othernum];
				if (cells == othercells)
				{
					// found a pair! 
					// remove all other possiblities from these 2 cells
					int digit_pair_mask = mask(num) | mask(othernum);

					// separate out the two set bits
					int cell1, cell2;
					lowest_two_set(cells, cell1, cell2);
					int cellcode1 = mask(cell1);
					int cellcode2 = mask(cell2);

					// convert the individual set-bit numbers back to block indices
					int row1, col1, row2, col2;
					blockunmask(cellcode1, row1, col1);
					blockunmask(cellcode2, row2, col2);

					sudoku.set(row_base + row1, col_base + col1, digit_pair_mask);
					sudoku.set(row_base + row2, col_base + col2, digit_pair_mask);
				}
			}
		}
	}
}

void block_doubles_pass(Sudoku &sudoku)
{
	for (int row_block = 0; row_block < 3; ++row_block)
	{
		for (int col_block = 0; col_block < 3; ++col_block)
		{
			block_doubles(sudoku, row_block, col_block);
		}
	}
}
