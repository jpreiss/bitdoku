#pragma once

#include <iosfwd>

class Sudoku
{
public:
	Sudoku();
	// build our bitmask form out of the standard puzzle description.
	Sudoku(int serialized[81]);
	Sudoku &operator=(Sudoku const &other);

	// element access
	int &operator()(int const row, int const col);
	int const &operator()(int const row, int const col) const;

	Sudoku transposed();
	void transpose();

	// right now, only verifies that each cell has only one possibility!
	// TODO: make sure that it's Really Solved
	bool is_solved();

	// verifies that there aren't 2 cells "solved" with the same digit
	// TODO: verify that all digits have at least one possible location
	bool row_is_valid(int row);
	bool col_is_valid(int col);
	bool block_is_valid(int row, int col);
	bool is_valid();

	// returns the digit if cell is solved, otherwise 0
	static char print_cell(int cell);

	void prettyprint(std::ostream &out, int row_highlight = -1, int col_highlight = -1) const;

	int board[81];
};