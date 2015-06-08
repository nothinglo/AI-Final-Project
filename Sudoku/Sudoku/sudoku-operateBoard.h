//
//  sudoku-operateBoard.h
//  Sudoku
//
//  Created by uglyman.nothinglo on 2015/6/8.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#ifndef __Sudoku__sudoku_operateBoard__
#define __Sudoku__sudoku_operateBoard__

#include <iostream>
#include <vector>
#include "globalVar.h"
using namespace std;

class boardCell {
public:
    int x, y, num, solutions;
    boardCell(int s) {
        solutions = s;
    }
    boardCell(int xx, int yy, int nn, int ss) : x(xx), y(yy), num(nn), solutions(ss) {
    }
    bool operator < (const boardCell & p) const {
        return this->solutions < p.solutions;
    }
};

void generateByFileInputBoard(int board[][sudokuSize], const char *fileName);

int sudoku_answer_count(int board[][sudokuSize]);
bool boardCheck(const int board[][sudokuSize], int x, int y, int num);
vector<int> maybeNumbers(int board[][sudokuSize], int x, int y);
int countSpace(const int board[][sudokuSize]);

void randomChange2Cols(int board[sudokuSize][sudokuSize], int col1, int col2);
void randomChange2Rows(int board[sudokuSize][sudokuSize], int row1, int row2);
void randomChange2BlockCols(int board[sudokuSize][sudokuSize], int col1, int col2);
void randomChange2BlockRows(int board[sudokuSize][sudokuSize], int row1, int row2);
void randomChange2Units(int board[sudokuSize][sudokuSize]);

bool generateSpaceBoard_NonUniqueSolution(int board[][sudokuSize], const int spaceCount);
bool generateSpaceBoard_NonUniqueSolution_ByData(int board[][sudokuSize], const int spaceCount);
#endif /* defined(__Sudoku__sudoku_operateBoard__) */
