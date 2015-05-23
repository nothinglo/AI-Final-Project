//
//  sudoku-board.h
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2015/5/23.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#ifndef __Sudoku__sudoku_board__
#define __Sudoku__sudoku_board__

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

bool boardCheck(const int board[][sudokuSize], int x, int y, int num);
vector<int> maybeNumbers(int board[][sudokuSize], int x, int y);
int countSpace(const int board[][sudokuSize]);

void generateRandomSpaceBoard(int board[][sudokuSize], const int spaceCount);

#endif /* defined(__Sudoku__sudoku_board__) */
