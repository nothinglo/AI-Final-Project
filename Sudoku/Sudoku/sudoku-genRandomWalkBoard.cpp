#include "logicalSolver.h"
#include "sudoku-operateBoard.h"
#include "sudoku-genRandomWalkBoard.h"
#include "consoleUI.h"

bool randomWalk(int board[sudokuSize][sudokuSize], vector<int> candidates, int blankNum)
{
	if (blankNum == 0) return true;

	// copy a new board
	int clone_board[sudokuSize][sudokuSize];
	copyBoard(board, clone_board);

	// go through all candidates
	while (!candidates.empty())
	{
		// random select a cell to eliminate
		int randNum = rand() % candidates.size();
		vector<int>::iterator it = candidates.begin() + randNum;
		int OneDimIndex = *it;
		int x = OneDimIndex / sudokuSize;
		int y = OneDimIndex % sudokuSize;

		int temp = clone_board[x][y];

		clone_board[x][y] = 0;

		vector<int> explored;

		// if removing selected cell can still get only one solution
		if (isSudokuUniqueSolution(board))
		//if (isSudokuUniqueSolution(clone_board))
		{
			vector<int> nextLevelCandidates = candidates;
			nextLevelCandidates.erase(nextLevelCandidates.begin() + randNum);
			nextLevelCandidates.insert(nextLevelCandidates.end(), explored.begin(), explored.end());

			if (randomWalk(clone_board, nextLevelCandidates, blankNum - 1))
			{
				copyBoard(clone_board, board);
				return true;
			}
			else
			{
				explored.push_back(*it);
				candidates.erase(it);	
				clone_board[x][y] = temp;
			}
		}
		else
		{		
			explored.push_back(*it);
			candidates.erase(it);
			clone_board[x][y] = temp;
		}
	}
	return false;
}

void generateRandomWalkBoard(int board[][sudokuSize], const int spaceCount) {
    
	/*vector<pair<int, int> > fullPos;
	for (int i = 0; i < sudokuSize; ++i) 
	{
		for (int j = 0; j < sudokuSize; ++j) 
		{
			fullPos.push_back(make_pair(i, j));
		}
	}

	std::random_shuffle(fullPos.begin(), fullPos.end());

	do
	{
		generateRandomFullFilledBoard(board);

		for (int i = 0; i < spaceCount; i++)
		{
			board[fullPos[i].first][fullPos[i].second] = 0;
		}
	} while (solveSudoku(board, false, true) != 1);*/
	
	generateRandomFullFilledBoard(board);

	// prepare one dimension index
	vector<int> candidates;
	for (int i = 0; i < sudokuLength - 1; i++)
	{
		candidates.push_back(i);
	}

	if (!randomWalk(board, candidates, spaceCount))
	{
		for (int i = 0; i < sudokuSize; i++)
		{
			for (int j = 0; j < sudokuSize; j++)
			{
				board[i][j] = 0;
			}
		}
	}

	/*int answered_board[sudokuSize][sudokuSize] = {
		{ 0, 0, 0, 8, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 4, 3 },
		{ 5, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 7, 0, 8, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 0 },
		{ 0, 2, 0, 0, 3, 0, 0, 0, 0 },
		{ 6, 0, 0, 0, 0, 0, 0, 7, 5 },
		{ 0, 0, 3, 4, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 2, 0, 0, 6, 0, 0 },
	};

	int answered_board[sudokuSize][sudokuSize] = {
		{ 0, 0, 0, 7, 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 4, 3, 0, 2, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 6 },
		{ 0, 0, 0, 5, 0, 9, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 4, 1, 8 },
		{ 0, 0, 0, 0, 8, 1, 0, 0, 0 },
		{ 0, 0, 2, 0, 0, 0, 0, 5, 0 },
		{ 0, 4, 0, 0, 0, 0, 3, 0, 0 },
	};

	for (int i = 0; i < 100; i++) {
		randomChange2Units(answered_board);
	}

	copyBoard(answered_board, board);*/
}

vector<pair<int, int> >
generateRandomWalkBoard_noBackTrack(int board[][sudokuSize], const int spaceCount, const int Threshold, const int level) {
    generateRandomFullFilledBoard(board);
    int answer[sudokuSize][sudokuSize];
    copyBoard(board, answer);
    int space, initSpace = min(Threshold, spaceCount);
    
    vector<pair<int, int> > hasNumber, fullPos;
    for(int i = 0; i < sudokuSize; ++i) {
        for(int j = 0; j < sudokuSize; ++j) {
            fullPos.push_back(make_pair(i, j));
        }
    }
    hasNumber = fullPos;
    space = initSpace;
    //int time = 0;
    while(space > 0) {
        int nowSpace = space;
        for(int i = 0; i < hasNumber.size(); ++i) {
            const int & x = hasNumber[i].first, y = hasNumber[i].second;
            board[x][y] = 0;
			if (isSudokuUniqueSolution(board)) {
                hasNumber.erase(hasNumber.begin() + i);
                --space;
                break;
            }
            board[x][y] = answer[x][y];
        }
        if(nowSpace == space) {
            //printf("Generate %d space board fail time = %d\n", initSpace, ++time);
            space = initSpace;
            generateRandomFullFilledBoard(board);
            hasNumber = fullPos;
        }
        std::random_shuffle(hasNumber.begin(), hasNumber.end());
        
        if((level == 0 || level == 1) && space == 0) {
            int tmpBoard[sudokuSize][sudokuSize];
            copyBoard(board, tmpBoard);
            if(logicalSolver(tmpBoard) == level) {
                return hasNumber;
            } else {
                space = initSpace;
                generateRandomFullFilledBoard(board);
                hasNumber = fullPos;
            }
        } else if(level >= 2) {
            int tmpBoard[sudokuSize][sudokuSize];
            copyBoard(board, tmpBoard);
            if(logicalSolver(tmpBoard) == level) {
                return hasNumber;
            }
        }
    }
    return hasNumber;
}

void generateLevelBoard(int board[][sudokuSize], const int level) {
    int spaceCount = 0;
    switch (level) {
        case 0:
            spaceCount = (firstLevelBlanksBound - 1) - rand() % 5;
            break;
        case 1:
            spaceCount = firstLevelBlanksBound + rand() % (58 - firstLevelBlanksBound + 1);
            break;
        case 2:
            spaceCount = 62;
            break;
        case 3:
            spaceCount = 62;
            break;
    }
    generateRandomWalkBoard_noBackTrack(board, spaceCount, 100, level);
}

void generateRandomWalkBoardWithConstraint(int board[][sudokuSize], vector<vector<bool> > pattern)
{
	const int disturbCount = 100;
	int answered_board[sudokuSize][sudokuSize] = {
		{ 6, 3, 9, 2, 4, 1, 7, 8, 5 },
		{ 2, 8, 4, 7, 6, 5, 1, 9, 3 },
		{ 5, 1, 7, 9, 8, 3, 6, 2, 4 },
		{ 1, 2, 3, 8, 5, 7, 9, 4, 6 },
		{ 7, 9, 6, 4, 3, 2, 8, 5, 1 },
		{ 4, 5, 8, 6, 1, 9, 2, 3, 7 },
		{ 3, 4, 2, 1, 7, 8, 5, 6, 9 },
		{ 8, 6, 1, 5, 9, 4, 3, 7, 2 },
		{ 9, 7, 5, 3, 2, 6, 4, 1, 8 },
	};

	do {
		// disturb the board
		for (int i = 0; i < disturbCount; i++)
		{
			randomChange2Units(answered_board);
		}

		for (int i = 0; i < sudokuSize; i++)
		{
			for (int j = 0; j < sudokuSize; j++)
			{
				board[i][j] = (pattern[i][j]) ? answered_board[i][j] : 0;
			}
		}
	} while (!isSudokuUniqueSolution(board));

	printf("answer count = %d\n", sudoku_answer_count(board));

}