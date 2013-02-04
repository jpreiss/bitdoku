#include "solver.h"
#include "sudoku.h"
#include "passes.h"

bool solve(Sudoku &sudoku)
{
	int n_passes = 0;
	while (!sudoku.is_solved())
	{
		bool trivial = trivial_pass(sudoku);
		bool row = only_in_row_pass(sudoku);
		bool col = only_in_col_pass(sudoku);
		bool block = only_in_block_pass(sudoku);
		bool rowbox = row_box_pass(sudoku);
		bool colbox = col_box_pass(sudoku);
		bool changed = trivial || row || col || block || rowbox || colbox;
		if (!changed)
		{
			return false;
		}
		++n_passes;
	}
	return true;
}