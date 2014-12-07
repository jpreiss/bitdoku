#include "solver.h"
#include "sudoku.h"
#include "passes.h"
#include <functional>

bool solve(Sudoku &sudoku)
{
	int n_passes = 0;

	auto group_size_loop = [](Sudoku &sudoku, std::function<void(Sudoku&, int)> func)
	{
		for (int size = 2; size < 5; ++size)
		{
			func(sudoku, size);
		}
	};

	while (!sudoku.is_solved())
	{
		sudoku.reset_change_flag();

		trivial_pass(sudoku);

		only_in_row_pass(sudoku);
		row_box_pass(sudoku);
		group_size_loop(sudoku, row_groups_pass);
		xwing_pass(sudoku);

		sudoku.transpose();
		{
			only_in_row_pass(sudoku);
			row_box_pass(sudoku);
			group_size_loop(sudoku, row_groups_pass);
			xwing_pass(sudoku);
		}
		sudoku.transpose();

		only_in_block_pass(sudoku);
		group_size_loop(sudoku, block_groups_pass);

		if (!sudoku.is_changed())
		{
			return false;
		}
		++n_passes;
	}
	return true;
}
