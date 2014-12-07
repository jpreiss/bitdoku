#include <cassert>
#include <string>
#include <iostream>
#include <fstream>

#include "bitwise.h"
#include "sudoku.h"
#include "solver.h"


void test_bitwise()
{
	for (int i = 0; i < 9; ++i)
	{
		assert(unmask(mask(i)) == i);
	}
	for (int r = 0; r < 3; ++r)
	{
		for (int c = 0; c < 3; ++c)
		{
			int row, col;
			int masked = blockmask(r, c);
			blockunmask(masked, row, col);
			assert(row == r);
			assert(col == c);
		}
	}
	int a, b;
	
	lowest_two_set(0x0, a, b);
	assert((a == -1) && (b == -1));

	lowest_two_set(0x8, a, b);
	assert((a == 3) && (b == -1));

	lowest_two_set(0x3, a, b);
	assert((a == 0) && (b == 1));

	lowest_two_set(0x110, a, b);
	assert((a == 4) && (b == 8));

	lowest_two_set(0xF30, a, b);
	assert((a == 4) && (b == 5));

	SetBitIndexIterator sbii0(0);
	assert(sbii0 == SetBitIndexIterator::end());

	SetBitIndexIterator sbii1(1);
	assert(sbii1 != SetBitIndexIterator::end());
	assert(*sbii1 == 0);
	++sbii1;
	assert(sbii1 == SetBitIndexIterator::end());

	SetBitIndexIterator sbii2(2);
	assert(sbii2 != SetBitIndexIterator::end());
	assert(*sbii2 == 1);
	++sbii2;
	assert(sbii2 == SetBitIndexIterator::end());

	SetBitIndexIterator sbii3(3);
	assert(sbii3 != SetBitIndexIterator::end());
	assert(*sbii3 == 0);
	++sbii3;
	assert(sbii3 != SetBitIndexIterator::end());
	assert(*sbii3 == 1);
	++sbii3;
	assert(sbii3 == SetBitIndexIterator::end());

	HammingWeightIterator ham1(1);
	assert(ham1.next() == 1);
	assert(ham1.next() == 2);
	assert(ham1.next() == 4);
	assert(ham1.next() == 8);

	HammingWeightIterator ham2(2);
	assert(ham2.next() == 3);
	assert(ham2.next() == 5);
	assert(ham2.next() == 6);
	assert(ham2.next() == 9);
}

void color(unsigned short color)
{
	// TODO: was using Windows stuff, figure out a way to make cross-platform
    // HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    // SetConsoleTextAttribute(hcon,color);
}

void green()
{
	// color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void red()
{
	// color(FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void white()
{
	// color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// benchmarks
int main()
{
	test_bitwise();

	std::ifstream cases("test_cases.txt");
	std::string comment;
	int nums[81];
	while (cases.good())
	{
		// relying on well-formed test case file.
		int next = cases.peek();
		if ('#' == next)
		{			
			std::getline(cases, comment);
		}
		else if (isdigit(next))
		{
			std::cout << comment << "... ";
			for (int i = 0; i < 81; ++i)
			{
				nums[i] = cases.get() - '0';
			}

			bool solved = false;
			Sudoku puzzle(nums);
			Sudoku working(nums);
			try
			{
				solved = solve(working);
			}
			catch (std::exception &e)
			{
				std::cout << "error: " << e.what() << std::endl;
			}
			if (solved)
			{
				green();
				std::cout << "PASS" << std::endl;
				white();
			}
			else
			{
				red();
				std::cout << "FAIL" << std::endl;
				//working.hugeprint(std::cout); break;
				white();
			}
		}
		else
		{
			// whitespace, throw away
			cases.get();
		}
	}
}
