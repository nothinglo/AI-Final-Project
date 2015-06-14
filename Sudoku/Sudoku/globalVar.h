//
//  globalVar.h
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2015/5/23.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#ifndef Sudoku_globalVar_h
#define Sudoku_globalVar_h

#include <cmath>
#include <limits>

const int sudoku_Sub_Size = 3;
const int sudokuSize = sudoku_Sub_Size * sudoku_Sub_Size; // 9
const int sudokuLength = sudokuSize * sudokuSize; // 81
const int block_size = sqrt(sudokuSize);

const int DisturbCount = 100;

const int minLevel = 1;
const int maxLevel = 12;

const int levelSpaceStep = 5;

const int InfiniteSolution = std::numeric_limits<int>::max();

const int UpperBoundOfFindSolution = 50000;

const int MaxSpaceCount = 64;
#endif
