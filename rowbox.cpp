#include "sudoku.h"
#include "bitwise.h"

// row-box interaction.
// when all of a row's possiblities for digit K lie in a single box,
// then no other cells in that box can possibly be K.
// also true: transpose "row" and "box".

void box_row_eliminate(Sudoku &sudoku, int row, int box, int eliminate_mask)
{
	for (int col = box * 3; col < (box + 1) * 3; ++col)
	{
		int cell = sudoku(row, col);
		int newcell = subtract(cell, eliminate_mask);
		sudoku.set(row, col, newcell);
	}
}

void row_box(Sudoku &sudoku, int row)
{
	int boxes_who_contain[9] = { 0 };
	for (int col = 0; col < 9; ++col)
	{
		int cell = sudoku(row, col);
		for (int num = 0; num < 9; ++num)
		{
			int mask_num = mask(num);
			if (cell & mask_num)
			{
				boxes_who_contain[num] |= mask(col / 3);
			}
		}	
	}

	for (int num = 0; num < 9; ++num)
	{
		int boxes = boxes_who_contain[num];
		if (1 == num_ones(boxes))
		{
			int box = unmask(boxes);

			// figure out the other two rows we need to deal with
			int row_base = (row / 3) * 3;
			int other_rows_mask = 0x7 << row_base;
			int other_row_1;
			int other_row_2;
			int other_rows = subtract(other_rows_mask, mask(row));
			lowest_two_set(other_rows, other_row_1, other_row_2);

			box_row_eliminate(sudoku, other_row_1, box, mask(num));
			box_row_eliminate(sudoku, other_row_2, box, mask(num));
		}
	}
}

void row_box_pass(Sudoku &sudoku)
{
	for (int i = 0; i < 9; ++i)
	{
		row_box(sudoku, i);
	}
}

void col_box_pass(Sudoku &sudoku)
{
	sudoku.transpose();
	row_box_pass(sudoku);
	sudoku.transpose();
}