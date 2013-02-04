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

void lowest_two_set(int a, int &first, int &second);