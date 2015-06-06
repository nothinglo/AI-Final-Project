#include <stdio.h>
#include <stdlib.h>
#include "logicalSolver.h"


// ZorinLogicSolver(board) 
// fill in all the certain number, and get stuck when none found.

// gonna use this to write a dfs


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
int logicalSolver(int board[][sudokuSize])
{
	bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize]; //[num][x][y]

	for (int num=0; num<sudokuSize; num++)
	{
		for (int x=0; x<sudokuSize; x++)
		{
			for (int y=0; y<sudokuSize; y++)
			{
				canNumBeHere[num][x][y]=checkIfCanWriteThisHere(board, x, y, num);
			}
		}

		printf("Num %d: \n", num+1);
		for (int x=0; x<sudokuSize; x++)
		{
			for (int y=0; y<sudokuSize; y++)
			{
				printf("%d ", canNumBeHere[num][x][y]);
			}
			printf("\n");
		}

	}

	bool waitingNumInThisX[sudokuSize][sudokuSize];	// [pos][num], true means this position still doesn't have that number
	bool waitingNumInThisY[sudokuSize][sudokuSize];
	bool waitingNumInThisBlock[sudokuSize][sudokuSize];

	initWaitingNum( board,  waitingNumInThisX,  waitingNumInThisY,  waitingNumInThisBlock);
	for (int x=0; x<sudokuSize; x++)
	{
		for (int num=0; num<sudokuSize; num++)
		{
			if (waitingNumInThisX[x][num])
				printf("%d ", num+1);
		}
		printf("\n");
	}


	printUIBoard(board);
	bool finishedSolving=false;
	while(!finishedSolving)
	{
		// X dir
		int returnNum, returnX, returnY;
		bool foundInX=findNumXDir(waitingNumInThisX, canNumBeHere, &returnNum, &returnX, &returnY);
		if (foundInX)
		{
			printf("found in X\n");
			putNumberHere( board, returnNum, returnX, returnY);
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
				else{
					printf("None Found\n");
				}
				for (int num=0; num<sudokuSize; num++)			
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
				}

			}
		}
		getchar();
	}

	return 0;
}