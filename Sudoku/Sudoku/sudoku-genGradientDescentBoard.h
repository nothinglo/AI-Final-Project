//
//  sudoku-genGradientDescentBoard.h
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2015/5/23.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#ifndef __Sudoku__sudoku_genGradientDescentBoard__
#define __Sudoku__sudoku_genGradientDescentBoard__

#include "globalVar.h"
#include "sudoku-operateBoard.h"

const boardCell descentBoardCell(int board[][sudokuSize]);
const boardCell descentBoardCell(int board[][sudokuSize], int & Threshold);
bool gradientDescentToBoard(int board[][sudokuSize]);
void generateGradientDescentBoard(int board[][sudokuSize], const int spaceCount);

void generateGradientDescentBoard_Back(int board[][sudokuSize], const int spaceCount);
void newGD(int board[][sudokuSize], const int spaceCount);
#endif /* defined(__Sudoku__sudoku_genGradientDescentBoard__) */

