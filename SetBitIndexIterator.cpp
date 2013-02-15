#include "bitwise.h"

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
	while (!(bits_ & 1) && bits_ != 0);

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