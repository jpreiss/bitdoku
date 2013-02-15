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
	int const &get(int const row, int const col) const;
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
	void hugeprint(std::ostream &out) const;

	// fills the array *output* such that
	// for each digit d, (output[d] | mask(c)) == true iff d is possible at board[row][c].
	void digit_to_column_map(int row, int output[9]) const;

	// fills the array *output* such that
	// for each digit d, (output[d] | blockmask(r, c)) == true iff d is possible at block[r][c]
	// block is specified by row_block and col_block which can take values 0, 1, or 2
	void digit_to_block_map(int row_block, int col_block, int output[9]) const;

private:
	bool change_flag;
	int board[81];
};

struct Index
{
	char row;
	char column;
};

class BlockIndexIterator
{
public:
	BlockIndexIterator(int row_block, int col_block);

	static BlockIndexIterator const end();

	bool operator==(BlockIndexIterator const other) const;
	bool operator!=(BlockIndexIterator const other) const;

	void operator++();
	Index operator*() const;

	Index withinBlock() const;

private:
	char row_;
	char col_;
	char row_base_;
	char col_base_;
};