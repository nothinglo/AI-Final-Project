#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>

#ifndef __Sudoku__sudoku_genRandomWalkBoard__
#define __Sudoku__sudoku_genRandomWalkBoard__

void generateRandomWalkBoard(int board[][sudokuSize], const int spaceCount);
void generateRandomWalkBoardWithConstraint(int board[][sudokuSize], vector<vector<bool> > pattern);

vector<pair<int, int> >
generateRandomWalkBoard_noBackTrack(int board[][sudokuSize], const int spaceCount, const int Threshold, const int level = -1);

void generateLevelBoard(int board[][sudokuSize], const int level);
#endif