#include "solver.h"
#include "sudoku.h"
#include "passes.h"

bool solve(Sudoku &sudoku)
{
	int n_passes = 0;

	while (!sudoku.is_solved())
	{
		sudoku.reset_change_flag();

		trivial_pass(sudoku);

		only_in_row_pass(sudoku);
		row_box_pass(sudoku);
		for (int size = 2; size < 5; ++size)
		{
			row_groups_pass(sudoku, size);
			block_groups_pass(sudoku, size);
		}

		sudoku.transpose();
		only_in_row_pass(sudoku);
		row_box_pass(sudoku);
		for (int size = 2; size < 5; ++size)
		{
			row_groups_pass(sudoku, size);
			block_groups_pass(sudoku, size);
		};
		sudoku.transpose();

		only_in_block_pass(sudoku);

		if (!sudoku.is_changed())
		{
			return false;
		}
		++n_passes;
	}
	return true;
}