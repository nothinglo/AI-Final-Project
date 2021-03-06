#ifndef LogicalSolver_h
#define LogicalSolver_h
#include "sudoku-operateBoard.h"

struct actionCount
{
	int theOnlyCandidate;
	int loneRanger;
	int twinEliminate;
	int wildGuess;
	int possibleBranchNum;
};

int logicalSolver(int board[][sudokuSize]);

bool hintOneStep(int board[][sudokuSize], int*returnNum, int*returnX, int*returnY, int*gotHintFrom);

int howHard(struct actionCount actionsDone);

int posToBlockNum(int x, int y);
void blockNumToBasePos(int blockNum, int *x, int *y);
void cellNumToOffset(int cellNum, int *x, int *y);

void initWaitingNum(int board[][sudokuSize], bool waitingNumInThisX[sudokuSize][sudokuSize], 
					bool waitingNumInThisY[sudokuSize][sudokuSize], bool waitingNumInThisBlock[sudokuSize][sudokuSize]);
void initCanNumBeHere(int board[][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize]);

void updateAvalibilityData(bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], int num, int posX, int posY);
void updateWatingNumData(bool waitingNumInThisX[sudokuSize][sudokuSize], bool waitingNumInThisY[sudokuSize][sudokuSize], 
						 bool waitingNumInThisBlock[sudokuSize][sudokuSize], int num, int posX, int posY);

void putNumberHere(int board[][sudokuSize], int num, int x, int y);
bool findNumSelf(bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], 
				 int *returnNum, int *returnX, int *returnY);
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
					  bool waitingNumInThisY[sudokuSize][sudokuSize], bool waitingNumInThisBlock[sudokuSize][sudokuSize], struct actionCount actionsDone);

bool twinElimination( bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize]);

bool twinsEliminationInX(bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize]);
bool twinsEliminationInY(bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize]);
bool twinsEliminationInBlock(bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize]);

vector<int> getCandidateList(int x, int y, bool candidates[][sudokuSize][sudokuSize]);

/* use simple elimination & lone ranger to solve board till stuck */
void eliminateTillStuck(int board[][sudokuSize], int &blankCount);
/*********************************************/

/* generate really random complete sudoku board */
bool generateRealRandomCompleteBoard(int board[][sudokuSize]);
/*********************************************/

#endif