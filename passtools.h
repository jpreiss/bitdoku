#pragma once

#include <functional>

class Sudoku;

void row_op_pass(Sudoku &sudoku, std::function<void(Sudoku&, int)> row_op);

void block_op_pass(Sudoku &sudoku, std::function<void(Sudoku&, int, int)> block_op);
