#pragma once

class Sudoku;

// look for cells with only one possiblity
void trivial_pass(Sudoku &sudoku);

// look for digits that only have one possible location in {row, col, block}
void only_in_row_pass(Sudoku &sudoku);
void only_in_block_pass(Sudoku &sudoku);

// row-box interaction.
// when all of a row's possiblities for digit K lie in a single box,
// then no other cells in that box can possibly be K.
void row_box_pass(Sudoku &sudoku);

// naked or hidden doubles
void row_double_pass(Sudoku &sudoku);
void block_doubles_pass(Sudoku &sudoku);