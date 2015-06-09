#include <stdio.h>
#include <stdlib.h>
#include "logicalSolver.h"


// ZorinLogicSolver(board) 
// fill in all the certain number, and get stuck when none found.



void updateAvalibilityData(bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], int num, int posX, int posY)
{

	for (int numI=0; numI<sudokuSize; numI++) // this cell is occupied
	{
		canNumBeHere[numI][posX][posY]=false;
	}

	for (int i=0; i<sudokuSize; i++)	// won't see same number again in same col or row
	{
		canNumBeHere[num][i][posY]=false;
		canNumBeHere[num][posX][i]=false;
	}

	int blockMinX=(posX/3)*3;
	int blockMinY=(posY/3)*3;

	for (int count3X=0; count3X<3; count3X++)	// neither in the same block
	{
		for (int count3Y=0; count3Y<3; count3Y++)
		{
			canNumBeHere[num][blockMinX+count3X][blockMinY+count3Y]=false;
		}
	}
	return;
}

int posToBlockNum(int x, int y)
{
	return (x/3)*3+ (y/3);
}

void blockNumToBasePos(int blockNum, int *x, int *y)
{
	*y=(blockNum%3)*3;
	*x=(blockNum/3)*3;
	return;
}

void updateWatingNumData(bool waitingNumInThisX[sudokuSize][sudokuSize], bool waitingNumInThisY[sudokuSize][sudokuSize], 
						 bool waitingNumInThisBlock[sudokuSize][sudokuSize], int num, int posX, int posY)
{
	waitingNumInThisX[posX][num]=false;
	waitingNumInThisY[posY][num]=false;
	waitingNumInThisBlock[posToBlockNum(posX, posY)][num]=false;
	return;
}

void initWaitingNum(int board[][sudokuSize], bool waitingNumInThisX[sudokuSize][sudokuSize], 
					bool waitingNumInThisY[sudokuSize][sudokuSize], bool waitingNumInThisBlock[sudokuSize][sudokuSize])
{

	for (int num=0; num<sudokuSize; num++)
	{
		for (int x=0; x<sudokuSize; x++)
		{
			bool appeared=false;
			for (int y=0; y<sudokuSize; y++)
			{
				if (board[x][y]==num+1)//the number on board start from 1, here start from 0
				{
					appeared=true;
					break;
				}
			}
			if (!appeared)
			{
				waitingNumInThisX[x][num]=true;
			}
			else
			{
				waitingNumInThisX[x][num]=false;
			}
		}
	}	

	for (int num=0; num<sudokuSize; num++)
	{
		for (int y=0; y<sudokuSize; y++)
		{
			bool appeared=false;
			for (int x=0; x<sudokuSize; x++)
			{
				if (board[x][y]==num+1)
				{
					appeared=true;
					break;
				}
			}
			if (!appeared)
			{
				waitingNumInThisY[y][num]=true;
			}
			else
			{
				waitingNumInThisY[y][num]=false;
			}
		}
	}
	for (int num=0; num<sudokuSize; num++)
	{
		for (int blockNum=0; blockNum<sudokuSize; blockNum++)
		{
			bool appeared=false;
			int baseX, baseY;
			blockNumToBasePos(blockNum, &baseX, &baseY);
			for (int count3X=0; count3X<3; count3X++)
			{
				for (int count3Y=0; count3Y<3; count3Y++)
				{
					if (board[baseX+count3X][baseY+count3Y]==num+1)
					{
						appeared=true;
					}
				}
			}
			if (!appeared)
			{
				waitingNumInThisBlock[blockNum][num]=true;
			}
			else
			{
				waitingNumInThisBlock[blockNum][num]=false;
			}

		}
	}

}

// number on board start from 1, not 0, so we need to plus one.
void putNumberHere(int board[][sudokuSize], int num, int x, int y)
{
	printf("Putting %d at (%d, %d)\n", num+1, x, y);
	if (board[x][y]!=0)
	{
		printf("OOPS. Already have number here!!\n");
		getchar();
		return;
	}
	board[x][y]=num+1;
	printUIBoard(board);
}

bool findNumXDir(bool waitingNumInThisX[sudokuSize][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], 
				 int *returnNum, int *returnX, int *returnY)
{
	for (int x=0; x<sudokuSize; x++)
	{
		for (int num=0; num<sudokuSize; num++)
		{
			if (!waitingNumInThisX[x][num])	// this num is already on board. no need to check.
			{
				continue;
			}
			else
			{
				int count=0;
				for(int y=0; y<sudokuSize; y++)
				{
					if(canNumBeHere[num][x][y])
					{
						*returnX=x;
						*returnY=y;
						*returnNum=num;
						count++;
					}
				}
				if (count==1)	// found a certain place to put this number
				{
					return true;
				}
			}
		}
	}

	return false;	// didn't find any. the return values are useless in this case, just don't use them.
}

bool findNumYDir(bool waitingNumInThisY[sudokuSize][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], 
				 int *returnNum, int *returnX, int *returnY)
{
	for(int y=0; y<sudokuSize; y++)
	{

		for (int num=0; num<sudokuSize; num++)
		{
			if (!waitingNumInThisY[y][num])	// this num is already on board. no need to check.
			{
				continue;
			}
			else
			{
				int count=0;
				for (int x=0; x<sudokuSize; x++)
				{
					if(canNumBeHere[num][x][y])
					{
						*returnX=x;
						*returnY=y;
						*returnNum=num;
						count++;
					}
				}
				if (count==1)	// found a certain place to put this number
				{
					return true;
				}
			}
		}
	}

	return false;	// didn't find any. the return values are useless in this case, just don't use them.
}

bool findNumBlock(bool waitingNumInThisBlock[sudokuSize][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], 
				  int *returnNum, int *returnX, int *returnY)
{
	for (int blockNum=0; blockNum<sudokuSize; blockNum++)
	{
		int baseX, baseY;
		blockNumToBasePos(blockNum, &baseX, &baseY);

		for (int num=0; num<sudokuSize; num++)
		{
			if (!waitingNumInThisBlock[blockNum][num])	// this num is already on board. no need to check.
			{
				continue;
			}
			else{
				int count=0;
				for (int count3X=0; count3X<3; count3X++)
				{	
					for (int count3Y=0; count3Y<3; count3Y++)
					{

						if(canNumBeHere[num][baseX+count3X][baseY+count3Y])
						{

							*returnX=baseX+count3X;
							*returnY=baseY+count3Y;
							*returnNum=num;

							count++;
						}
					}
				}
				if (count==1)
				{
					return true;
				}
			}
		}

	}

	return false;	// didn't find any. the return values are useless in this case, just don't use them.
}


bool checkIfCanWriteThisHere(int board[][sudokuSize], int x, int y, int num)
{
	return (boardCheck(board, x, y, num+1) && board[x][y]==0);	// this cell must be empty, else we can't write here.
}

void fillInNumbersTillStuck(int board[][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], bool waitingNumInThisX[sudokuSize][sudokuSize], 
							bool waitingNumInThisY[sudokuSize][sudokuSize], bool waitingNumInThisBlock[sudokuSize][sudokuSize])	
{

	bool stuck=false;
	while(!stuck)
	{
		// X dir
		int returnNum, returnX, returnY;
		bool foundInX=findNumXDir(waitingNumInThisX, canNumBeHere, &returnNum, &returnX, &returnY);
		if (foundInX)
		{
			printf("found in X\n");
			putNumberHere( board, returnNum, returnX, returnY);

			// after putting this number down, other cell will be effected, update these
			updateAvalibilityData(canNumBeHere, returnNum, returnX, returnY);	
			updateWatingNumData(waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, returnNum, returnX, returnY);
		}
		else
		{
			bool foundInY=findNumYDir(waitingNumInThisY, canNumBeHere, &returnNum, &returnX, &returnY);
			if (foundInY)
			{
				printf("found in Y\n");
				putNumberHere( board, returnNum, returnX, returnY);
				updateAvalibilityData(canNumBeHere, returnNum, returnX, returnY);
				updateWatingNumData(waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, returnNum, returnX, returnY);
			}
			else{
				bool foundInBlock=findNumBlock( waitingNumInThisBlock, canNumBeHere, &returnNum, &returnX, &returnY);
				if (foundInBlock)
				{
					printf("found in Block\n");	
					putNumberHere( board, returnNum, returnX, returnY);
					updateAvalibilityData(canNumBeHere, returnNum, returnX, returnY);
					updateWatingNumData(waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, returnNum, returnX, returnY);
				}
				else
				{
					printf("Can't find a certain step\n");
					stuck=true;
					/*					for (int num=0; num<sudokuSize; num++)			
					{
					printf("Num %d: \n", num+1);
					for (int x=0; x<sudokuSize; x++)
					{
					for (int y=0; y<sudokuSize; y++)
					{
					printf("%d ", canNumBeHere[num][x][y]);
					}
					printf("\n");
					}
					}*/
				}

			}
		}
		//		getchar();
	}
	return;
}

int decideNextStep(int board[][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], int* returnX, int* returnY, bool candidate[sudokuSize])	
	//return -1 means this is dead end, we have done something wrong in the past; 0 means we cant decide which way to go; 1 means we have found the answer.
{

	int spaceNum=0;
	int minCandidateCount=sudokuSize+1;
	int bestX = -1, bestY = -1;
	bool bestCandidate[sudokuSize]={0};
	for (int x=0; x<sudokuSize; x++)
	{
		for (int y=0; y<sudokuSize; y++)
		{
			if (board[x][y]==0)	//found a space
			{
				spaceNum++;
				int candiCount=0;
				bool tempCandidate[sudokuSize]={0};
				for (int num=0; num<sudokuSize; num++)
				{
					if(canNumBeHere[num][x][y])
					{
						candiCount++;// record one candidate
						tempCandidate[num]=true;
					}
				}
				if (candiCount==0)
				{
					printf("DEAD END\n");
					return -1;	// some cell can never be filled, DEAD END
				}
				if (candiCount==2)	// we know 2 is the minimum number, if we found a cell with only 2 candidate, just return it.
				{
					*returnX=x;
					*returnY=y;
					memcpy(candidate, tempCandidate, sizeof(tempCandidate));
					printf("Branching, 2 candidates\n");
					return 0;	// means sudoku is not yet finished.
				}
				if (candiCount<minCandidateCount)
				{
					minCandidateCount=candiCount;
					bestX=x;
					bestY=y;
					memcpy(bestCandidate, tempCandidate, sizeof(tempCandidate));
				}

			}
		}
	}
	if (spaceNum==0)
	{
		printf("Ans Found\n");
		return 1;	//ans found
	}
	else	
	{
		*returnX=bestX;
		*returnY=bestY;
		memcpy(candidate, bestCandidate, sizeof(bestCandidate));
		printf("Branching, %d candidates\n", minCandidateCount);
		return 0;
	}



}

bool inSearchOfAnswer(int board[][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], bool waitingNumInThisX[sudokuSize][sudokuSize], 
					  bool waitingNumInThisY[sudokuSize][sudokuSize], bool waitingNumInThisBlock[sudokuSize][sudokuSize])
{


	fillInNumbersTillStuck(board, canNumBeHere, waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock);
	int guessX, guessY;
	bool candidate[sudokuSize];
	int boardStatus=decideNextStep(board, canNumBeHere, &guessX, &guessY, candidate);
	getchar();
	if (boardStatus==1)
	{
		return true;	// FOUND ANSWER!!
	}
	if (boardStatus==0)	// need to guess a number
	{

		// back up the data in case we need to roll back
		int backUp_board[sudokuSize][sudokuSize];
		bool backUp_canNumBeHere[sudokuSize][sudokuSize][sudokuSize];
		bool backUp_waitingNumInThisX[sudokuSize][sudokuSize];
		bool backUp_waitingNumInThisY[sudokuSize][sudokuSize];
		bool backUp_waitingNumInThisBlock[sudokuSize][sudokuSize];

		memcpy(backUp_board, board, sizeof(int)*sudokuSize*sudokuSize);
		memcpy(backUp_canNumBeHere, canNumBeHere, sizeof(bool)*sudokuSize*sudokuSize*sudokuSize);
		memcpy(backUp_waitingNumInThisX, waitingNumInThisX, sizeof(bool)*sudokuSize*sudokuSize);
		memcpy(backUp_waitingNumInThisY, waitingNumInThisY, sizeof(bool)*sudokuSize*sudokuSize);
		memcpy(backUp_waitingNumInThisBlock, waitingNumInThisBlock, sizeof(bool)*sudokuSize*sudokuSize);

		for (int candidateNum=0; candidateNum<sudokuSize; candidateNum++)	// try every candidate, if one doesn't work, undo it and try another
		{
			if (candidate[candidateNum])
			{				
				putNumberHere( board, candidateNum, guessX, guessY);
				updateAvalibilityData(canNumBeHere, candidateNum, guessX, guessY);
				updateWatingNumData(waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, candidateNum, guessX, guessY);
				bool guessSuccess = inSearchOfAnswer(board, canNumBeHere, waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock);
				if (guessSuccess)
				{
					return true;
				}
				else
				{
					// recover to the state before guessing
					memcpy(board, backUp_board, sizeof(int)*sudokuSize*sudokuSize);
					memcpy(canNumBeHere, backUp_canNumBeHere, sizeof(bool)*sudokuSize*sudokuSize*sudokuSize);
					memcpy(waitingNumInThisX, backUp_waitingNumInThisX, sizeof(bool)*sudokuSize*sudokuSize);
					memcpy(waitingNumInThisY, backUp_waitingNumInThisY, sizeof(bool)*sudokuSize*sudokuSize);
					memcpy(waitingNumInThisBlock, backUp_waitingNumInThisBlock, sizeof(bool)*sudokuSize*sudokuSize);
				}
			}
		}
		//	if tried all the candidate and haven't found the right one, something is wrong in earlier steps
		printf("Tried all Candidates but still can't find the right one. Poping out\n");
		getchar();
		return false;
	}
	if (boardStatus==-1)	// something is wrong in upper layer
	{
		printf("Got myself in a dead end. Poping out\n");
		getchar();
		return false;
	}

	printf("boardStatus should be one of -1, 0, or 1. if program reached here, something's wrong.");
	getchar();
	return false;

}

void initCanNumBeHere(int board[][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize])
{

	// initailize canNumBeHere
	for (int num=0; num<sudokuSize; num++)
	{
		for (int x=0; x<sudokuSize; x++)
		{
			for (int y=0; y<sudokuSize; y++)
			{
				canNumBeHere[num][x][y]=checkIfCanWriteThisHere(board, x, y, num);
			}
		}

	}

}

bool hintOneStep(int board[][sudokuSize], int*returnNum, int*returnX, int*returnY)
{
	bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize]; //[num][x][y]
	initCanNumBeHere(board, canNumBeHere);

	bool waitingNumInThisX[sudokuSize][sudokuSize];	// [pos][num], true means this position still doesn't have that number
	bool waitingNumInThisY[sudokuSize][sudokuSize];
	bool waitingNumInThisBlock[sudokuSize][sudokuSize];


	bool foundInX=findNumXDir(waitingNumInThisX, canNumBeHere, returnNum, returnX, returnY);
	if (foundInX)
	{
		printf("found in X\n");
		return true;

		// after putting this number down, other cell will be effected, update these

		// but since we don't expect to do this hint repeatly, we just recalculate all the data when we need to give a hint
		// instead of maintaining the datas

		//updateAvalibilityData(canNumBeHere, returnNum, returnX, returnY);	
		//updateWatingNumData(waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, returnNum, returnX, returnY);
	}
	else
	{
		bool foundInY=findNumYDir(waitingNumInThisY, canNumBeHere, returnNum, returnX, returnY);
		if (foundInY)
		{
			printf("found in Y\n");
			return true;

			//updateAvalibilityData(canNumBeHere, returnNum, returnX, returnY);
			//updateWatingNumData(waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, returnNum, returnX, returnY);
		}
		else{
			bool foundInBlock=findNumBlock( waitingNumInThisBlock, canNumBeHere, returnNum, returnX, returnY);
			if (foundInBlock)
			{
				printf("found in Block\n");	

				return true;

				//updateAvalibilityData(canNumBeHere, returnNum, returnX, returnY);
				//updateWatingNumData(waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, returnNum, returnX, returnY);
			}
			else
			{
				printf("Can't find a certain step\n");
				return false;
			}

		}
	}

}

int logicalSolver(int board[][sudokuSize])
{
	bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize]; //[num][x][y]
	initCanNumBeHere(board, canNumBeHere);

	bool waitingNumInThisX[sudokuSize][sudokuSize];	// [pos][num], true means this position still doesn't have that number
	bool waitingNumInThisY[sudokuSize][sudokuSize];
	bool waitingNumInThisBlock[sudokuSize][sudokuSize];

	initWaitingNum( board,  waitingNumInThisX,  waitingNumInThisY,  waitingNumInThisBlock);

	printf("Finished initializing data\n");
	getchar();

	bool guessSuccess = inSearchOfAnswer(board, canNumBeHere, waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock);
	if (guessSuccess)
	{
		printf("FOUND ANSWER!!!\n");
		printUIBoard(board);
	}
	else
	{
		printf("WTF??\n");	
		printUIBoard(board);
	}

	/*
	fillInNumbersTillStuck(board, canNumBeHere, waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock);
	int guessX, guessY;
	bool candidate[sudokuSize];
	int boardStatus=decideNextStep(board, canNumBeHere, &guessX, &guessY, candidate);

	if (boardStatus==0)
	{
	printf("x: %d, y: %d, candidate: ", guessX, guessY);	
	for (int num=0; num<sudokuSize; num++)
	{
	if (candidate[num])
	{
	printf(" %d", num+1);
	}
	}
	printf("\n");
	}
	if (boardStatus==-1)
	printf("fuck...");

	*/

	return 0;
}
