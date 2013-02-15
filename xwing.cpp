#include "passes.h"
#include "sudoku.h"
#include "bitwise.h"


// cache the digit_to_column_map for the whole board
void digit_to_column_allrows(Sudoku &sudoku, int maps[9][9])
{
	for (int i = 0; i < 9; ++i)
	{
		sudoku.digit_to_column_map(i, maps[i]);
	}
}

// doing this one as a class because it has tons of nested loops
// and conditionals that need to share the digit-to-column cache
class XWing
{
public:
	XWing(Sudoku &sudoku) :
		sudoku(sudoku)
	{
		digit_to_column_allrows(sudoku, digit_to_column_maps);
	}

	void run()
	{
		for (int row1 = 0; row1 < 8; ++row1)
		{
			for (int digit = 0; digit < 9; ++digit)
			{
				run_row_digit(row1, digit);
			}
		}
	}

	void run_row_digit(int row1, int digit)
	{
		int digit_cols = digit_to_column_maps[row1][digit];

		if (num_ones(digit_cols) != 2)
		{
			return;
		}

		for (int row2 = row1 + 1; row2 < 9; ++row2)
		{
			if (digit_to_column_maps[row2][digit] != digit_cols)
			{
				continue;
			}

			int col1, col2;
			lowest_two_set(digit_cols, col1, col2);

			clear_columns(row1, row2, col1, col2, digit);

			// digit-to-column map cache is stale.  recompute
			digit_to_column_allrows(sudoku, digit_to_column_maps);
		}
	}

	void clear_columns(int row1, int row2, int col1, int col2, int digit)
	{
		for (int otherrow = 0; otherrow < 9; ++otherrow)
		{
			if ((otherrow == row1) || (otherrow == row2))
			{
				continue;
			}

			int prev1 = sudoku(otherrow, col1);
			sudoku.set(otherrow, col1, subtract(prev1, mask(digit)));

			int prev2 = sudoku(otherrow, col2);
			sudoku.set(otherrow, col2, subtract(prev2, mask(digit)));
		}
	}

	Sudoku &sudoku;
	int digit_to_column_maps[9][9];
};

void xwing_pass(Sudoku &sudoku)
{
	XWing xwing(sudoku);
	xwing.run();
	return;
}