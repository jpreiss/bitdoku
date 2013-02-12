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
		row_double_pass(sudoku);

		sudoku.transpose();
		only_in_row_pass(sudoku);
		row_box_pass(sudoku);
		row_double_pass(sudoku);
		sudoku.transpose();

		only_in_block_pass(sudoku);
		block_doubles_pass(sudoku);

		if (!sudoku.is_changed())
		{
			return false;
		}
		++n_passes;
	}
	return true;
}