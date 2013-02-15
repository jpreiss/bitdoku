#include "passtools.h"

void row_op_pass(Sudoku &sudoku, std::function<void(Sudoku&, int)> row_op)
{
	for (int i = 0; i < 9; ++i)
	{
		row_op(sudoku, i);
	}
}

void block_op_pass(Sudoku &sudoku, std::function<void(Sudoku&, int, int)> block_op)
{
	for (int row_block = 0; row_block < 3; ++row_block)
	{
		for (int col_block = 0; col_block < 3; ++col_block)
		{
			block_op(sudoku, row_block, col_block);
		}
	}
}