#include "bitwise.h"

// aka population count, hamming weight
int num_ones(int x)
{
	int count = 0;
	for (int i = 0; i < 9; ++i)
	{
		if (x & 1)
		{
			++count;
		}
		x = x >> 1;
	}
	return count;
}

bool is_solved(int x)
{
	return 1 == num_ones(x);
}

// maps the integers 0-32 to bits
int mask(int a)
{
	return 1 << a;
}
int unmask(int a)
{
	int shifts = -1;
	while (a)
	{
		a = a >> 1;
		++shifts;
	}
	return shifts;
}

// canonical form for encoding a position within a 3x3 block as an int
int blockmask(int row, int col)
{
	return mask(row * 3 + col);
}
void blockunmask(int a, int &row, int &col)
{
	int unmasked = unmask(a);
	row = unmasked / 3;
	col = unmasked % 3;
}

// unsets all bits in a that are set in b
int subtract(int a, int b)
{
	return a & (~b);
}

// gets the indices of the lowest two bits set in a.
// stored in first and second, lowest first.
// -1 if not enough bits set.
void lowest_two_set(int a, int &first, int &second)
{
	int shifts = 0;
	first = -1;
	second = -1;
	while (a && (-1 == second))
	{
		if (a & 1)
		{
			if (-1 == first)
			{
				first = shifts;
			}
			else
			{
				second = shifts;
			}
		}
		a = a >> 1;
		++shifts;
	}
}


SetBitIndexIterator::SetBitIndexIterator(int bits) :
	bits_(bits),
	index_(0)
{
	if (0 == bits_)
	{
		index_ = -1;
		return;
	}

	while (!(bits_ & 1))
	{
		advance();
	}
}

bool SetBitIndexIterator::operator!=(SetBitIndexIterator const other)
{
	return index_ != other.index_;
}

bool SetBitIndexIterator::operator==(SetBitIndexIterator const other)
{
	return !((*this) != other);
}

SetBitIndexIterator SetBitIndexIterator::end()
{
	return SetBitIndexIterator(0);
}

void SetBitIndexIterator::operator++()
{
	do
	{
		advance();
	}
	while ((!bits_ & 1) && bits_ != 0);

	if (0 == bits_)
	{
		index_ = -1;
	}
}

int SetBitIndexIterator::operator*()
{
	return index_;
}

void SetBitIndexIterator::advance()
{
	bits_ >>= 1;
	++index_;
}