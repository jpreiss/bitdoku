#include <cassert>
#include <string>
#include <iostream>
#include <fstream>

// ughhh.... for output coloring
#include <Windows.h>

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
}

void color(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon,color);
}

void green()
{
	color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void red()
{
	color(FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void white()
{
	color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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

			bool solved;
			try
			{
				Sudoku su(nums);
				solved = solve(su);
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
				white();
			}
		}
		else
		{
			// whitespace, throw away
			cases.get();
		}
	}

	std::string in;
	std::cin >> in;
}