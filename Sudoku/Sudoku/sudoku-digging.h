//
//  sudoku-board.h
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2015/5/23.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#ifndef __Sudoku__sudoku_digging__
#define __Sudoku__sudoku_digging__

#include <iostream>
#include <vector>
#include "globalVar.h"
#include "sudoku-operateBoard.h"

using namespace std;

void generateDiggingBoard(int board[][sudokuSize]);
bool gradientDescentDigToBoard(int board[][sudokuSize]);

#endif /* defined(__Sudoku__sudoku_board__) */
