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
		if (isSudokuUniqueSolution(clone_board))
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
}

vector<pair<int, int> >
generateRandomWalkBoard_noBackTrack(int board[][sudokuSize], const int spaceCount, const int Threshold) {
    generateRandomFullFilledBoard(board);
    int space, initSpace = min(Threshold, spaceCount);
    
    vector<pair<int, int> > hasNumber, fullPos;
    for(int i = 0; i < sudokuSize; ++i) {
        for(int j = 0; j < sudokuSize; ++j) {
            fullPos.push_back(make_pair(i, j));
        }
    }
    hasNumber = fullPos;
    space = initSpace;
    int time = 0;
    while(space > 0) {
        vector<tuple<int, int, int> > candidates;
        for(int i = 0; i < hasNumber.size(); ++i) {
            const int & x = hasNumber[i].first, y = hasNumber[i].second;
            int tmp = board[x][y];
            board[x][y] = 0;
            if(isSudokuUniqueSolution(board)) {
                candidates.push_back(make_tuple(x, y, i));
            }
            board[x][y] = tmp;
        }
        if(candidates.size() == 0) {
            printf("Generate %d space board fail time = %d\n", initSpace, ++time);
            space = initSpace;
            generateRandomFullFilledBoard(board);
            hasNumber = fullPos;
        } else {
            int randNum = rand() % candidates.size();
            vector<tuple<int, int, int> >::iterator it = candidates.begin() + randNum;
            const int & x = std::get<0>(*it), y = std::get<1>(*it), i = std::get<2>(*it);
            board[x][y] = 0;
            candidates.erase(it);
            hasNumber.erase(hasNumber.begin() + i);
            --space;
        }
    }
    return hasNumber;
}