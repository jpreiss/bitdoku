#include "sudoku.h"
#include "asciiart.h"
#include "bitwise.h"
#include <ostream>

void pencil_numbers(std::ostream &out, int cell, int subrow)
{
	for (int digit = subrow * 3; digit < (subrow + 1) * 3; ++digit)
	{
		if (cell & mask(digit))
		{
			out << (digit + 1);
		}
		else
		{
			out << ' ';
		}
	}
}

void Sudoku::hugeprint(std::ostream &out) const
{
	for (int row = 0; row < 9; ++row)
	{
		for (int subrow = 0; subrow < 3; ++subrow)
		{
			for (int col = 0; col < 9; ++col)
			{
				int cell = get(row, col);
				if (num_ones(cell) == 1)
				{
					int digit = unmask(cell);
					out << number_art_lookup[digit][subrow];
				}
				else
				{
					pencil_numbers(out, cell, subrow);
				}
				if ((col % 3 == 2) && (col != 8))
				{
					out << "   |   ";
				}
				else
				{
					out << "    ";
				}
			}	
			out << std::endl;
		}
		if ((row % 3 == 2) && (row != 8))
		{
			out << "                    |                       |                        " << std::endl;
			out << "--------------------+-----------------------+------------------------" << std::endl;
		}
		out << "                    |                       |                        " << std::endl;;
	}
}
