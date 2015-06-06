
#include "sudoku-board.h"
#include "consoleUI.h"

int logicalSolver(int board[][sudokuSize]);

void updateAvalibilityData(bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], int num, int posX, int posY);
void updateWatingNumData(bool waitingNumInThisX[sudokuSize][sudokuSize], bool waitingNumInThisY[sudokuSize][sudokuSize], 
						 bool waitingNumInThisBlock[sudokuSize][sudokuSize], int num, int posX, int posY);

int posToBlockNum(int x, int y);
void blockNumToBasePos(int blockNum, int *x, int *y);

void initWaitingNum(int board[][sudokuSize], bool waitingNumInThisX[sudokuSize][sudokuSize], 
					bool waitingNumInThisY[sudokuSize][sudokuSize], bool waitingNumInThisBlock[sudokuSize][sudokuSize]);

void putNumberHere(int board[][sudokuSize], int num, int x, int y);

bool findNumXDir(bool waitingNumInThisX[sudokuSize][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], 
				 int *returnNum, int *returnX, int *returnY);

bool findNumYDir(bool waitingNumInThisY[sudokuSize][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], 
				 int *returnNum, int *returnX, int *returnY);

bool findNumBlock(bool waitingNumInThisBlock[sudokuSize][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], 
				  int *returnNum, int *returnX, int *returnY);

bool checkIfCanWriteThisHere(int board[][sudokuSize], int x, int y, int num);
