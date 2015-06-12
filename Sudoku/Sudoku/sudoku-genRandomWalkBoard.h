#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>

#ifndef __Sudoku__sudoku_genRandomWalkBoard__
#define __Sudoku__sudoku_genRandomWalkBoard__

void generateRandomWalkBoard(int board[][sudokuSize], const int spaceCount);

vector<pair<int, int> >
generateRandomWalkBoard_noBackTrack(int board[][sudokuSize], const int spaceCount, const int Threshold);

void generatePerfectRandomWalkBoard(int board[][sudokuSize], const int spaceCount);
#endif