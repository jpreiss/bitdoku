#include <algorithm>
#include <ostream>

#include "bitwise.h"
#include "sudoku.h"

static int const all_possible = 0x1FF;

Sudoku::Sudoku()
{		
	std::fill(board, board + 81, all_possible);
}

// build our bitmask form out of the standard puzzle description.
Sudoku::Sudoku(int serialized[81])
{
	auto setup = [](int puzz)
	{
		if (0 == puzz) return all_possible;
		return mask(puzz - 1);
	};
	std::transform(serialized, serialized + 81, board, setup);
}

Sudoku &Sudoku::operator=(Sudoku const &other)
{
	std::copy(other.board, other.board + 81, board);
	return *this;
}

void Sudoku::reset_change_flag()
{
	change_flag = false;
}

bool Sudoku::is_changed() const
{
	return change_flag;
}

void Sudoku::set(int row, int col, int value)
{
	if ((*this)(row, col) != value)
	{
		board[row * 9 + col] = value;

		// this is really more of a debug assert
		// is_valid also slows us down a lot
		if (!is_valid())
		{
			throw std::exception("Change caused an invalid puzzle.");
		}

		change_flag = true;
	}
}

int const &Sudoku::operator()(int const row, int const col) const
{
	return board[row * 9 + col];
}

Sudoku Sudoku::transposed() const
{
	Sudoku temp;
	for (int row = 0; row < 9; ++row)
	{
		for (int col = 0; col < 9; ++col)
		{
			temp.board[row * 9 + col] = board[col * 9 + row];
		}
	}
	return temp;
}

void Sudoku::transpose()
{
	Sudoku xp = this->transposed();
	(*this) = xp;
}

bool Sudoku::is_solved() const
{
	return std::all_of(board, board + 81, ::is_solved);
}

bool Sudoku::row_is_valid(int row) const
{
	int singletons = 0;
	for (int i = 0; i < 9; ++i)
	{
		int cell = (*this)(row, i);
		if (::is_solved(cell))
		{
			if(singletons & cell)
			{
				return false;
			}
			singletons |= cell;
		}
	}
	return true;
}

bool Sudoku::col_is_valid(int col) const
{
	Sudoku xp = this->transposed();
	return xp.row_is_valid(col);
}

bool Sudoku::block_is_valid(int row, int col) const
{
	int singletons = 0;
	int row_block = row / 3;
	int col_block = col / 3;
	for (int r = row_block * 3; r < (row_block + 1) * 3; ++r)
	{
		for (int c = col_block * 3; c < (col_block + 1) * 3; ++c)
		{
			int cell = (*this)(r, c);
			if (::is_solved(cell))
			{
				if(singletons & cell)
				{
					return false;
				}
				singletons |= cell;
			}
		}
	}
	return true;
}

bool Sudoku::is_valid() const
{
	for (int i = 0; i < 9; ++i)
	{
		if (!row_is_valid(i)) return false;
		if (!col_is_valid(i)) return false;
		for (int j = 0; j < 0; ++j)
		{
			if (!block_is_valid(i, j)) return false;
		}
	}
	return true;
}

char Sudoku::print_cell(int cell)
{
	if (num_ones(cell) == 1)
	{
		return unmask(cell) + '0';
	}
	return '0';
}

void Sudoku::prettyprint(std::ostream &out, int row_highlight, int col_highlight) const
{
	for (int row = 0; row < 9; ++row)
	{
		if (row % 3 == 0)
		{
			out << std::endl;
		}
		for (int col = 0; col < 9; ++col)
		{
			if (col % 3 == 0)
			{
				out << ' ';
			}
			out << print_cell((*this)(row, col));
		}
		out << std::endl;
	}
}
