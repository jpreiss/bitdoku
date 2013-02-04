#pragma once

class Sudoku;

// look for cells with only one possiblity
bool trivial_pass(Sudoku &sudoku);

// look for digits that only have one possible location in {row, col, block}
bool only_in_row_pass(Sudoku &sudoku);
bool only_in_col_pass(Sudoku &sudoku);
bool only_in_block_pass(Sudoku &sudoku);


bool row_box_pass(Sudoku &sudoku);
bool col_box_pass(Sudoku &sudoku);