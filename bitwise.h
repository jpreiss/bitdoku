#pragma once

// aka population count, hamming weight
int num_ones(int x);

// if a cell only has one possible digit
bool is_solved(int x);

// maps the cell possibilities (0 - 8) to bits
int mask(int a);
int unmask(int a);

// canonical form for encoding a position within a 3x3 block as an int
int blockmask(int row, int col);
void blockunmask(int a, int &row, int &col);

// unsets all bits in a that are set in b
int subtract(int a, int b);

// gets the indices of the lowest two bits set in a.
// stored in first and second, lowest first.
// -1 if not enough bits set.
void lowest_two_set(int a, int &first, int &second);

//
// iterates over the indices of the 1 bits in an integer.
//
class SetBitIndexIterator
{
public:
	SetBitIndexIterator(int bits);

	static SetBitIndexIterator end();

	bool operator!=(SetBitIndexIterator const other);
	bool operator==(SetBitIndexIterator const other);

	void operator++();

	int operator*();

private:
	void advance();
	int bits_;
	int index_;
};

//
// iterates over all numbers through 0x1FF
// with a specified hamming weight
//
class HammingWeightIterator
{
public:
	HammingWeightIterator(int weight);

	// returns -1 when the set is exhausted
	int next();

private:
	static int const MAX = 0x1FF;
	int const weight_;
	int state_;
};