#include <stdio.h>
#include <stdlib.h>
#include "logicalSolver.h"


// ZorinLogicSolver(board) 
// fill in all the certain number, and get stuck when none found.


void updateAvalibilityData(bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], int num, int posX, int posY)
{

	for (int numI=0; numI<sudokuSize; numI++) // this cell is occupied
	{
		canNumBeHere[posX][posY][numI]=false;
	}

	for (int i=0; i<sudokuSize; i++)	// won't see same number again in same col or row
	{
		canNumBeHere[i][posY][num]=false;
		canNumBeHere[posX][i][num]=false;
	}

	int blockMinX=(posX/3)*3;
	int blockMinY=(posY/3)*3;

	for (int count3X=0; count3X<3; count3X++)	// neither in the same block
	{
		for (int count3Y=0; count3Y<3; count3Y++)
		{
			canNumBeHere[blockMinX+count3X][blockMinY+count3Y][num]=false;
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
void cellNumToOffset(int cellNum, int *x, int *y)
{
	*y=(cellNum%3);
	*x=(cellNum/3);
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

bool findNumSelf(bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], 
				 int *returnNum, int *returnX, int *returnY)
{
	for (int x=0; x<sudokuSize; x++)
	{
		for (int y=0; y<sudokuSize; y++)
		{
			int candiCount=0;
			for (int num=0; num<sudokuSize; num++)
			{
				if(canNumBeHere[x][y][num])
				{
					candiCount++;
					*returnNum=num;
				}
			}
			if (candiCount==1)
			{
				*returnX=x;
				*returnY=y;
				return true;
			}
		}
	}

	return false;
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
					if(canNumBeHere[x][y][num])
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
					if(canNumBeHere[x][y][num])
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

						if(canNumBeHere[baseX+count3X][baseY+count3Y][num])
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
							bool waitingNumInThisY[sudokuSize][sudokuSize], bool waitingNumInThisBlock[sudokuSize][sudokuSize], struct actionCount *actionsDone)	
{

	bool stuck=false;
	while(!stuck)
	{
		// X dir
		int returnNum, returnX, returnY;
		bool foundInSelf= findNumSelf(canNumBeHere, &returnNum, &returnX, &returnY);
		if(foundInSelf)
		{
			actionsDone->theOnlyCandidate++;
			printf("found in Self (this block can only be this number!)\n");
			putNumberHere( board, returnNum, returnX, returnY);

			// after putting this number down, other cell will be effected, update these
			updateAvalibilityData(canNumBeHere, returnNum, returnX, returnY);	
			updateWatingNumData(waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, returnNum, returnX, returnY);
		}
		else
		{
			bool foundInX=findNumXDir(waitingNumInThisX, canNumBeHere, &returnNum, &returnX, &returnY);
			if (foundInX)
			{
				actionsDone->loneRanger++;
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
				actionsDone->loneRanger++;
					printf("found in Y\n");
					putNumberHere( board, returnNum, returnX, returnY);
					updateAvalibilityData(canNumBeHere, returnNum, returnX, returnY);
					updateWatingNumData(waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, returnNum, returnX, returnY);
				}
				else
				{
					bool foundInBlock=findNumBlock( waitingNumInThisBlock, canNumBeHere, &returnNum, &returnX, &returnY);
					if (foundInBlock)
					{
				actionsDone->loneRanger++;
						printf("found in Block\n");	
						putNumberHere( board, returnNum, returnX, returnY);
						updateAvalibilityData(canNumBeHere, returnNum, returnX, returnY);
						updateWatingNumData(waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, returnNum, returnX, returnY);
					}
					else
					{

						printf("Can't find a certain step\n");

						stuck=true;



						// for debugging
						/*					for (int num=0; num<sudokuSize; num++)			
						{
						printf("Num %d: \n", num+1);
						for (int x=0; x<sudokuSize; x++)
						{
						for (int y=0; y<sudokuSize; y++)
						{
						printf("%d ", canNumBeHere[x][y][num]);
						}
						printf("\n");
						}
						}*/
						// for debugging

					}

				}
			}
		}
		//		getchar();
	}
	return;
}

bool twinElimination( bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize])
{
	printf("Trying twinsEliminationInX\n");
	bool twinX=twinsEliminationInX(canNumBeHere);

	if (twinX)
	{
		printf("Twin Elimination in X helped us eliminated some possibilities, now recheck if we can find some certain number to fill in.\n");
	}
	else
	{
		printf("Trying twinsEliminationInY\n");

		bool twinY=twinsEliminationInY(canNumBeHere);
		if (twinY)
		{

			printf("Twin Elimination in Y helped us eliminated some possibilities, now recheck if we can find some certain number to fill in.\n");
		}
		else
		{
			printf("Trying twinsEliminationInBlock\n");
			bool twinCell=twinsEliminationInBlock(canNumBeHere);
			if (twinCell)
			{
				printf("Twin Elimination in Block helped us eliminated some possibilities, now recheck if we can find some certain number to fill in.\n");
			}
			else
			{
				printf("All failed, I'm really stucked\n");
				return false;
			}
		}
	}

	return true;
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
					if(canNumBeHere[x][y][num])
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
					printf("Can't decide number.\n");
					//					printf("Branching, 2 candidates\n");
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
		printf("Can't decide number.\n");
		//		printf("Branching, %d candidates\n", minCandidateCount);
		return 0;
	}



}

bool inSearchOfAnswer(int board[][sudokuSize], bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize], bool waitingNumInThisX[sudokuSize][sudokuSize], 
					  bool waitingNumInThisY[sudokuSize][sudokuSize], bool waitingNumInThisBlock[sudokuSize][sudokuSize], struct actionCount *actionsDone)
{
	int guessX, guessY;
	bool candidate[sudokuSize];
	int boardStatus;
	while (true)
	{
		fillInNumbersTillStuck(board, canNumBeHere, waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, actionsDone);
		boardStatus=decideNextStep(board, canNumBeHere, &guessX, &guessY, candidate);
		getchar();
		if (boardStatus==1)
		{
			return true;	// FOUND ANSWER!!
		}
		if (boardStatus==-1)	// something is wrong in upper layer
		{
			printf("Got myself in a dead end. Poping out\n");
			getchar();
			return false;
		}

		printf("Trying twinElimination.\n");
		bool twinsHelped = twinElimination(canNumBeHere);
		getchar();
		if (!twinsHelped)	// if twins Helped, 重新繼續填數字看看, if not, 真的得猜了
		{
			printf("Twin Elimination didn't help. We have to guess.\n");
			break;
		}
		else
		{
			actionsDone->twinEliminate++; // if twin helped.
		}
	}


	if (boardStatus==0)	// need to guess a number
	{

		// back up the data in case we need to roll back
		int backUp_board[sudokuSize][sudokuSize];
		bool backUp_canNumBeHere[sudokuSize][sudokuSize][sudokuSize];
		bool backUp_waitingNumInThisX[sudokuSize][sudokuSize];
		bool backUp_waitingNumInThisY[sudokuSize][sudokuSize];
		bool backUp_waitingNumInThisBlock[sudokuSize][sudokuSize];
		struct actionCount backUp_actionsDone;

		memcpy(backUp_board, board, sizeof(int)*sudokuSize*sudokuSize);
		memcpy(backUp_canNumBeHere, canNumBeHere, sizeof(bool)*sudokuSize*sudokuSize*sudokuSize);
		memcpy(backUp_waitingNumInThisX, waitingNumInThisX, sizeof(bool)*sudokuSize*sudokuSize);
		memcpy(backUp_waitingNumInThisY, waitingNumInThisY, sizeof(bool)*sudokuSize*sudokuSize);
		memcpy(backUp_waitingNumInThisBlock, waitingNumInThisBlock, sizeof(bool)*sudokuSize*sudokuSize);

		backUp_actionsDone.theOnlyCandidate=actionsDone->theOnlyCandidate;
		backUp_actionsDone.loneRanger=actionsDone->loneRanger;
		backUp_actionsDone.twinEliminate=actionsDone->twinEliminate;
		backUp_actionsDone.wildGuess=actionsDone->wildGuess;
		backUp_actionsDone.possibleBranchNum=actionsDone->possibleBranchNum;

		int candidateCount=0;
		for (int num=0; num<sudokuSize; num++)	// count our candidate (for evaluating how hard is the sudoku)
		{
			if (candidate[num])
			{
				candidateCount++;
			}
		}

		for (int num=0; num<sudokuSize; num++)	// try every candidate, if one doesn't work, undo it and try another
		{
			if (candidate[num])	// if this num is a possible candidate
			{	
				
				actionsDone->wildGuess++;
				actionsDone->possibleBranchNum+=candidateCount;
				printf("Guessing: ");
				putNumberHere( board, num, guessX, guessY);
				updateAvalibilityData(canNumBeHere, num, guessX, guessY);
				updateWatingNumData(waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, num, guessX, guessY);

				getchar();

				bool guessSuccess = inSearchOfAnswer(board, canNumBeHere, waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, actionsDone);
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

					actionsDone->theOnlyCandidate=backUp_actionsDone.theOnlyCandidate;
					actionsDone->loneRanger=backUp_actionsDone.loneRanger;
					actionsDone->twinEliminate=backUp_actionsDone.twinEliminate;
					actionsDone->wildGuess=backUp_actionsDone.wildGuess;
					actionsDone->possibleBranchNum=backUp_actionsDone.possibleBranchNum;
				}
			}
		}
		//	if tried all the candidate and haven't found the right one, something is wrong in earlier steps
		printf("Tried all Candidates but still can't find the right one. Poping out\n");
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
				canNumBeHere[x][y][num]=checkIfCanWriteThisHere(board, x, y, num);
			}
		}

	}

}

int numOfCandi(bool canNumBeHereXY[sudokuSize])	// canNumBeHere[x][y][num]	把最後一維傳進來
{
	int count=0;	
	for (int num=0; num<sudokuSize; num++)
	{
		if (canNumBeHereXY[num])
			count++;
	}

	return count;
}

bool candiIsSame(bool canNumBeHereX1Y1[sudokuSize], bool canNumBeHereX2Y2[sudokuSize])
{
	for (int num=0; num<sudokuSize; num++)
	{
		if (canNumBeHereX1Y1[num]!=canNumBeHereX2Y2[num])
			return false;
	}

	return true;
}



bool twinsEliminationInX(bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize])
{			
	bool changed=false;
	for (int x=0; x<sudokuSize; x++)
	{
		bool candiNumIsTwo[sudokuSize];
		for (int y=0; y<sudokuSize; y++)	// 把候選有兩個的先找好
		{
			candiNumIsTwo[y]=(numOfCandi(canNumBeHere[x][y])==2);	
		}

		for (int y1=0; y1<sudokuSize; y1++)
		{
			if (candiNumIsTwo[y1])	// 候選有兩個才有可能有twins
			{
				for (int y2=y1+1; y2<sudokuSize; y2++)
				{
					if (candiNumIsTwo[y2])	//找到另一個候選數=2的
					{
						if (candiIsSame(canNumBeHere[x][y1], canNumBeHere[x][y2]))	// 至此找到了twins!!
						{
							printf("found twins in X direction : (%d, %d), (%d, %d) num: ", x, y1, x, y2);
							for (int twinNum=0; twinNum<sudokuSize; twinNum++)
							{
								if (canNumBeHere[x][y1][twinNum])	//	twins的兩個數字會過這判斷式
								{
									printf("%d ", twinNum+1);
								}
							}
							printf("\n");
							for (int twinNum=0; twinNum<sudokuSize; twinNum++)
							{
								if (canNumBeHere[x][y1][twinNum])	//	twins的兩個數字會過這判斷式
								{
									//printf("twin: num %d ", twinNum+1);
									for (int clearingY=0; clearingY<sudokuSize; clearingY++)	
									{
										if (clearingY==y1||clearingY==y2)	// twins本身不動
											continue;
										if (canNumBeHere[x][clearingY][twinNum])//	twins中的數字若出現在其他的地方, 刪掉它們 // 如果不是要知道我有沒有changed, 不需要此判斷式, 通通設false就是了
										{
											canNumBeHere[x][clearingY][twinNum]=false;
											changed=true;
											printf("(%d, %d), kick out %d\n", x, clearingY, twinNum+1);
										}

									}
								}
							}
							printf("\n");
						}
					}
				}
			}
		}


	}

	return changed;

}
bool twinsEliminationInY(bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize])
{			
	bool changed=false;
	for (int y=0; y<sudokuSize; y++)
	{
		bool candiNumIsTwo[sudokuSize];
		for (int x=0; x<sudokuSize; x++)	// 把候選有兩個的先找好
		{
			candiNumIsTwo[x]=(numOfCandi(canNumBeHere[x][y])==2);	
		}

		for (int x1=0; x1<sudokuSize; x1++)
		{
			if (candiNumIsTwo[x1])	// 候選有兩個才有可能有twins
			{
				for (int x2=x1+1; x2<sudokuSize; x2++)
				{
					if (candiNumIsTwo[x2])	//找到另一個候選數=2的
					{
						if (candiIsSame(canNumBeHere[x1][y], canNumBeHere[x2][y]))	// 至此找到了twins!!
						{
							printf("found twins in Y direction : (%d, %d), (%d, %d), num: ", x1, y, x2, y);
							for (int twinNum=0; twinNum<sudokuSize; twinNum++)
							{
								if (canNumBeHere[x1][y][twinNum])	//	twins的兩個數字會過這判斷式
								{
									printf("%d ", twinNum+1);
								}
							}
							printf("\n");
							for (int twinNum=0; twinNum<sudokuSize; twinNum++)
							{
								if (canNumBeHere[x1][y][twinNum])	//	twins的兩個數字會過這判斷式
								{
									for (int clearingX=0; clearingX<sudokuSize; clearingX++)	
									{
										if (clearingX==x1||clearingX==x2)	// twins本身不動
											continue;
										if (canNumBeHere[clearingX][y][twinNum])//	twins中的數字若出現在其他的地方, 刪掉它們 // 如果不是要知道我有沒有changed, 不需要此判斷式, 通通設false就是了
										{
											canNumBeHere[clearingX][y][twinNum]=false;
											changed=true;
											printf("(%d, %d), kick out %d\n", clearingX, y, twinNum+1);
										}

									}
								}
							}
							printf("\n");
						}
					}
				}
			}
		}


	}

	return changed;

}


bool twinsEliminationInBlock(bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize])
{			
	bool changed=false;
	for (int blockID=0; blockID<sudokuSize; blockID++)
	{
		int baseX, baseY;
		blockNumToBasePos(blockID, &baseX, &baseY);

		bool candiNumIsTwo[sudokuSize];
		for (int cellID=0; cellID<sudokuSize; cellID++)	// 把候選有兩個的先找好
		{
			int offsetX, offsetY;
			cellNumToOffset(cellID, &offsetX, &offsetY);
			candiNumIsTwo[cellID]=(numOfCandi(canNumBeHere[baseX+offsetX][baseY+offsetY])==2);	
		}

		for (int cellID1=0; cellID1<sudokuSize; cellID1++)
		{
			if (candiNumIsTwo[cellID1])	// 候選有兩個才有可能有twins
			{
				int offsetX1, offsetY1;
				cellNumToOffset(cellID1, &offsetX1, &offsetY1);
				for (int cellID2=cellID1+1; cellID2<sudokuSize; cellID2++)
				{
					if (candiNumIsTwo[cellID2])	//找到另一個候選數=2的
					{
						int offsetX2, offsetY2;
						cellNumToOffset(cellID2, &offsetX2, &offsetY2);
						int x1=baseX+offsetX1;
						int y1=baseY+offsetY1;
						int x2=baseX+offsetX2;
						int y2=baseY+offsetY2;

						if (candiIsSame(canNumBeHere[x1][y1], canNumBeHere[x2][y2]))	// 至此找到了twins!!
						{
							printf("found twins in Block : (%d, %d), (%d, %d), num: ", x1, y1, x2, y2);
							for (int twinNum=0; twinNum<sudokuSize; twinNum++)
							{
								if (canNumBeHere[x1][y1][twinNum])	//	twins的兩個數字會過這判斷式
								{
									printf("%d ", twinNum+1);
								}
							}
							printf("\n");
							for (int twinNum=0; twinNum<sudokuSize; twinNum++)
							{
								if (canNumBeHere[x1][y1][twinNum])	//	twins的兩個數字會過這判斷式
								{
									for (int clearingCell=0; clearingCell<sudokuSize; clearingCell++)	
									{
										int clearingX, clearingY;
										cellNumToOffset(clearingCell, &clearingX, &clearingY);
										clearingX=clearingX+baseX;
										clearingY=clearingY+baseY;

										if ((clearingX==x1&&clearingY==y1)||(clearingX==x2&&clearingY==y2))	// twins本身不動
											continue;
										if (canNumBeHere[clearingX][clearingY][twinNum])//	twins中的數字若出現在其他的地方, 刪掉它們 // 如果不是要知道我有沒有changed, 不需要此判斷式, 通通設false就是了
										{
											canNumBeHere[clearingX][clearingY][twinNum]=false;
											changed=true;
											printf("(%d, %d), kick out %d\n", clearingX, clearingY, twinNum+1);
										}

									}
								}
							}
							printf("\n");
						}
					}
				}
			}
		}


	}

	return changed;

}



bool hintOneStep(int board[][sudokuSize], int*returnNum, int*returnX, int*returnY, int*gotHintFrom)
{
	bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize]; //[num][x][y]
	initCanNumBeHere(board, canNumBeHere);

	bool waitingNumInThisX[sudokuSize][sudokuSize];	// [pos][num], true means this position still doesn't have that number
	bool waitingNumInThisY[sudokuSize][sudokuSize];
	bool waitingNumInThisBlock[sudokuSize][sudokuSize];

	initWaitingNum( board,  waitingNumInThisX,  waitingNumInThisY,  waitingNumInThisBlock);

	bool foundInSelf= findNumSelf(canNumBeHere, returnNum, returnX, returnY);
	if(foundInSelf)
	{
		*gotHintFrom=3;
		printf("found in Self\n");
		return true;
	}
	else
	{
		bool foundInX=findNumXDir(waitingNumInThisX, canNumBeHere, returnNum, returnX, returnY);
		if (foundInX)
		{
			*gotHintFrom=0;
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
				*gotHintFrom=1;
				printf("found in Y\n");
				return true;

				//updateAvalibilityData(canNumBeHere, returnNum, returnX, returnY);
				//updateWatingNumData(waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, returnNum, returnX, returnY);
			}
			else{
				bool foundInBlock=findNumBlock( waitingNumInThisBlock, canNumBeHere, returnNum, returnX, returnY);
				if (foundInBlock)
				{
					*gotHintFrom=2;
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


}

int howHard(struct actionCount actionsDone)
{
	int w1=1;	// theOnlyCandidate
	int w2=2;	// loneRanger
	int w3=10;	// twinEliminate
	int w4=20;	// wildGuess
	int score=actionsDone.theOnlyCandidate*w1+actionsDone.loneRanger*w2+actionsDone.twinEliminate*w3+actionsDone.wildGuess*w4;
	return score;
}

int logicalSolver(int board[][sudokuSize])
{
	bool canNumBeHere[sudokuSize][sudokuSize][sudokuSize]; //[x][y][num]
	initCanNumBeHere(board, canNumBeHere);

	bool waitingNumInThisX[sudokuSize][sudokuSize];	// [pos][num], true means this position still doesn't have that number
	bool waitingNumInThisY[sudokuSize][sudokuSize];
	bool waitingNumInThisBlock[sudokuSize][sudokuSize];

	initWaitingNum( board,  waitingNumInThisX,  waitingNumInThisY,  waitingNumInThisBlock);

	struct actionCount actionsDone;
	actionsDone.theOnlyCandidate=0;
	actionsDone.loneRanger=0;
	actionsDone.twinEliminate=0;
	actionsDone.wildGuess=0;
	actionsDone.possibleBranchNum=0;

	printf("Finished initializing data\n");

	bool guessSuccess = inSearchOfAnswer(board, canNumBeHere, waitingNumInThisX, waitingNumInThisY, waitingNumInThisBlock, &actionsDone);
	if (guessSuccess)
	{
		printf("FOUND ANSWER!!!\n");
		printUIBoard(board);

		printf("Actions done:\ntheOnlyCandidate: %d\nloneRanger: %d\ntwinEliminate: %d\nwildGuess: %d\npossibleBranchNum: %d\n", actionsDone.theOnlyCandidate, actionsDone.loneRanger, actionsDone.twinEliminate, actionsDone.wildGuess, actionsDone.possibleBranchNum);
		printf("\nSudoku Score: %d\n==================\n", howHard(actionsDone));
	}
	else
	{
		printf("WTF??\n");	
		printUIBoard(board);
	}


	return 0;
}
