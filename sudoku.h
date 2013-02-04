#pragma once

#include <iosfwd>

class Sudoku
{
public:
	Sudoku();
	// build our bitmask form out of the standard puzzle description.
	Sudoku(int serialized[81]);
	Sudoku &operator=(Sudoku const &other);

	// change flag, so we know when an iteration has done something
	void reset_change_flag();
	bool is_changed() const;

	// element access
	void set(int row, int col, int value);
	int const &operator()(int const row, int const col) const;

	Sudoku transposed() const;
	void transpose();

	// right now, only verifies that each cell has only one possibility!
	// TODO: make sure that it's Really Solved
	bool is_solved() const;

	// verifies that there aren't 2 cells "solved" with the same digit
	// TODO: verify that all digits have at least one possible location
	bool row_is_valid(int row) const;
	bool col_is_valid(int col) const;
	bool block_is_valid(int row, int col) const;
	bool is_valid() const;

	// returns the digit if cell is solved, otherwise 0
	static char print_cell(int cell);

	void prettyprint(std::ostream &out, int row_highlight = -1, int col_highlight = -1) const;

private:
	bool change_flag;
	int board[81];
};