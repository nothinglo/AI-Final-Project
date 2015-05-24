#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>

#ifndef __Sudoku__sudoku_another__way__
#define __Sudoku__sudoku_another__way__

void randomChange2Cols(int board[sudokuSize][sudokuSize], int col1, int col2);
void randomChange2Rows(int board[sudokuSize][sudokuSize], int row1, int row2);
void randomChange2BlockCols(int board[sudokuSize][sudokuSize], int col1, int col2);
void randomChange2BlockRows(int board[sudokuSize][sudokuSize], int row1, int row2);

void randomChange2Units(int board[sudokuSize][sudokuSize]);
void genSudokuAnotherWay(int board[][sudokuSize], const int spaceCount);

#endif