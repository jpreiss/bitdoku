#include "sudoku.h"


BlockIndexIterator::BlockIndexIterator(int row_block, int col_block) :
row_base_(row_block * 3),
col_base_(col_block * 3),
row_(0),
col_(0)
{
}
	
BlockIndexIterator const BlockIndexIterator::end()
{
	BlockIndexIterator b(0, 0);
	b.row_ = 3;
	b.col_ = 0;
	return b;
}

bool BlockIndexIterator::operator==(BlockIndexIterator const other) const
{
	return (row_ == other.row_) && (col_ == other.col_);
}

bool BlockIndexIterator::operator!=(BlockIndexIterator const other) const
{
	return !(*this == other);
}

void BlockIndexIterator::operator++()
{
	if (col_ == 2)
	{
		col_ = 0;
		++row_;
	}
	else
	{
		++col_;
	}
}

Index BlockIndexIterator::operator*() const
{
	Index idx;
	idx.row = row_base_ + row_;
	idx.column = col_base_ + col_;
	return idx;
}

Index BlockIndexIterator::withinBlock() const
{
	Index idx;
	idx.row = row_;
	idx.column = col_;
	return idx;
}
