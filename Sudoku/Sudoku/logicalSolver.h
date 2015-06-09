
#include "sudoku-operateBoard.h"
#include "consoleUI.h"

int logicalSolver(int board[][sudokuSize]);
bool hintOneStep(int board[][sudokuSize], int*returnNum, int*returnX, int*returnY);

void updateAvalibilityData(bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], int num, int posX, int posY);

int posToBlockNum(int x, int y);
void blockNumToBasePos(int blockNum, int *x, int *y);

void updateWatingNumData(bool waitingNumInThisX[sudokuSize][sudokuSize], bool waitingNumInThisY[sudokuSize][sudokuSize], 
						 bool waitingNumInThisBlock[sudokuSize][sudokuSize], int num, int posX, int posY);
void initWaitingNum(int board[][sudokuSize], bool waitingNumInThisX[sudokuSize][sudokuSize], 
					bool waitingNumInThisY[sudokuSize][sudokuSize], bool waitingNumInThisBlock[sudokuSize][sudokuSize]);

void initCanNumBeHere(int board[][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize]);

void putNumberHere(int board[][sudokuSize], int num, int x, int y);
bool findNumXDir(bool waitingNumInThisX[sudokuSize][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], 
				 int *returnNum, int *returnX, int *returnY);
bool findNumYDir(bool waitingNumInThisY[sudokuSize][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], 
				 int *returnNum, int *returnX, int *returnY);
bool findNumBlock(bool waitingNumInThisBlock[sudokuSize][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], 
				  int *returnNum, int *returnX, int *returnY);

bool checkIfCanWriteThisHere(int board[][sudokuSize], int x, int y, int num);

void fillInNumbersTillStuck(int board[][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], bool waitingNumInThisX[sudokuSize][sudokuSize], 
							bool waitingNumInThisY[sudokuSize][sudokuSize], bool waitingNumInThisBlock[sudokuSize][sudokuSize]);

int decideNextStep(int board[][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], int* returnX, int* returnY, bool candidate[sudokuSize]);	
	//return -1 means this is dead end, we have done something wrong in the past; 0 means we cant decide which way to go; 1 means we have found the answer.

bool inSearchOfAnswer(int board[][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], bool waitingNumInThisX[sudokuSize][sudokuSize], 
					  bool waitingNumInThisY[sudokuSize][sudokuSize], bool waitingNumInThisBlock[sudokuSize][sudokuSize]);
