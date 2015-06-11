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
		if (sudoku_answer_count(clone_board) == 1)
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

    const int disturbCount = 100;
	int answered_board[sudokuSize][sudokuSize] = {
		{ 5, 3, 4, 6, 7, 8, 9, 1, 2 },
		{ 6, 7, 2, 1, 9, 5, 3, 4, 8 },
		{ 1, 9, 8, 3, 4, 2, 5, 6, 7 },
		{ 8, 5, 9, 7, 6, 1, 4, 2, 3 },
		{ 4, 2, 6, 8, 5, 3, 7, 9, 1 },
		{ 7, 1, 3, 9, 2, 4, 8, 5, 6 },
		{ 9, 6, 1, 5, 3, 7, 2, 8, 4 },
		{ 2, 8, 7, 4, 1, 9, 6, 3, 5 },
		{ 3, 4, 5, 2, 8, 6, 1, 7, 9 },
	};

	// disturb the board
	for (int i = 0; i < disturbCount; i++) {
		randomChange2Units(answered_board);
	}

	// copy data from answered_board to board
    copyBoard(answered_board, board);

	// prepare one dimension index
	vector<int> candidates;
	for (int i = 0; i < sudokuSize*sudokuSize - 1; i++)
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
}