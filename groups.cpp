#include "sudoku.h"
#include "passes.h"
#include "bitwise.h"
#include "passtools.hpp"


// gets the union of all possiblities
// for the supplied columns in the row
/* not needed?
int column_union(Sudoku const &sudoku, int row, int columns)
{
	int accumulator = 0;

	SetBitIndexIterator column_iter(columns);
	auto end = SetBitIndexIterator::end();

	for (; column_iter != end; ++column_iter);
	{
		accumulator |= sudoku(row, *column_iter);
	}

	return accumulator;
}
*/

// gets the set of columns
// that contain any one of the bits set in digits
int columns_containing_any(Sudoku const &sudoku, int row, int digits)
{
	int column_accumulator = 0;

	for (int col = 0; col < 9; ++col)
	{
		int cell = sudoku(row, col);
		if (cell & digits)
		{
			column_accumulator |= mask(col);
		}
	}

	return column_accumulator;
}

void row_groups(Sudoku &sudoku, int group_size, int row)
{
	HammingWeightIterator subset_iter(group_size);
	int digit_subset;

	// for each set of n numbers S = {k1, k2, ... kn}:
	while ((digit_subset = subset_iter.next()) != -1)
	{
		// C(k) == set of columns containing k
		// C(S) == union of C(k) over k in S
		int cols_containing = columns_containing_any(sudoku, row, digit_subset);

		// if size(C(S)) == n
		if (num_ones(cols_containing) == group_size)
		{
			// remove all other possibilities from columns in C(S)
			SetBitIndexIterator col_iter(cols_containing);
			auto end = SetBitIndexIterator::end();

			for (; col_iter != end; ++col_iter)
			{
				int prev = sudoku(row, *col_iter);
				sudoku.set(row, *col_iter, prev & digit_subset);
			}
		}
	}
}

int blockcells_containing_any(Sudoku const &sudoku, int row_block, int col_block, int digits)
{
	int block_accumulator = 0;

	BlockIndexIterator iter(row_block, col_block);
	auto end = BlockIndexIterator::end();

	for (; iter != end; ++iter)
	{
		Index idx = *iter;

		int cell = sudoku(idx.row, idx.column);
		if (cell & digits)
		{
			Index within_block = iter.withinBlock();
			block_accumulator |= blockmask(within_block.row, within_block.column);
		}
	}

	return block_accumulator;
}

void block_groups(Sudoku &sudoku, int group_size, int row_block, int col_block)
{
	HammingWeightIterator subset_iter(group_size);
	int digit_subset;

	// for each set of n numbers S = {k1, k2, ... kn}:
	while ((digit_subset = subset_iter.next()) != -1)
	{
		// C(k) == set of columns containing k
		// C(S) == union of C(k) over k in S
		int blocks_containing = blockcells_containing_any(sudoku, row_block, col_block, digit_subset);

		// if size(C(S)) == n
		if (num_ones(blocks_containing) == group_size)
		{
			// remove all other possibilities from columns in C(S)
			SetBitIndexIterator block_iter(blocks_containing);
			auto end = SetBitIndexIterator::end();

			for (; block_iter != end; ++block_iter)
			{
				int row, col;
				blockunmask(mask(*block_iter), row, col);
				row += row_block * 3;
				col += col_block * 3;
				int prev = sudoku(row, col);
				sudoku.set(row, col, prev & digit_subset);
			}
		}
	}
}

void block_groups_pass(Sudoku &sudoku, int group_size)
{
	auto block_op = [&](Sudoku &sudoku, int row_block, int col_block)
	{
		block_groups(sudoku, group_size, row_block, col_block);
	};

	block_op_pass(sudoku, block_op);
}

void row_groups_pass(Sudoku &sudoku, int group_size)
{
	auto row_op = [&](Sudoku &sudoku, int row)
	{
		row_groups(sudoku, group_size, row);
	};

	row_op_pass(sudoku, row_op);
}