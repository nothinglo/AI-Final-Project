#include "generator.h"
#include "sudoku-operateBoard.h"
#include "logicalSolver.h"

bool generateWithSpecifiedPattern(int board[_N][_N], bool pattern[_N][_N])
{
	while (!generateRealRandomCompleteBoard(board));

	vector<pair<int, int> > hintIndex;

	/*
	// Leave the number in the pattern area, and
	// remove the number outside the pattern area
	// 將使用者指定地方的數字留下，其他填0
	// 紀錄使用者指定地方的 index
	*/
	for (int i = 0; i < _N; i++)
		for (int j = 0; j < _N; j++)
		{
			if (!pattern[i][j])
				board[i][j] = 0;
			else
				hintIndex.push_back(make_pair(i, j));
		}
	
	// Temporary storage
	int leaveOneOut[_N][_N];
	bool leaveOneOutCandidates[_N][_N][_N];
	int tryCandidate[_N][_N];
	bool tryCandidateCandidates[_N][_N][_N];

	// If we are lucky enough, we can return right now...
	if (isSudokuUniqueSolution(board))
		return true;

	int blankCount;
	copyBoard(board, leaveOneOut);
	eliminateTillStuck(leaveOneOut, blankCount);

	if (blankCount == 0)
		return false;

	// Segments the pattern into some groups
	vector<int> nextList(hintIndex.size());
	int groupNum = sqrt(hintIndex.size());
	int remain = hintIndex.size() % groupNum;
	int n = hintIndex.size() / groupNum;
	int c = 0;
	int next = 0;
	for (int i = 0; i < groupNum; i++)
	{
		int elements = n;
		if (i < remain) elements++;
		next += elements;

		for (int j = 0; j < elements; j++)
		{
			nextList[c++] = next - 1;
		}
	}

	bool stillHasSomethingToDo = true;
	while (stillHasSomethingToDo)
	{
		stillHasSomethingToDo = false;

		/*
		// For each hint(where user wants to show the number),
		// remove it and try all the candidates in that cell,
		// find the candidate that can reduce #blank more
		*/
		for (int i = 0; i < hintIndex.size(); i++)
		{
			int id_x = hintIndex[i].first;
			int id_y = hintIndex[i].second;
			int pre = board[id_x][id_y];

			board[id_x][id_y] = 0;

			copyBoard(board, leaveOneOut);

			initCanNumBeHere(leaveOneOut, leaveOneOutCandidates);

			vector<int> candiList = getCandidateList(id_x, id_y, leaveOneOutCandidates);
			if (candiList.empty())
			{
				board[id_x][id_y] = pre;
				continue;
			}

			// If candidate list contains "pre", remove it
			vector<int>::iterator it = find(candiList.begin(), candiList.end(), pre);
			if (it != candiList.end())
			{
				vector<int> temp(it + 1, candiList.end());
				temp.insert(temp.end(), candiList.begin(), it);
				candiList.erase(it);
				candiList = temp;
			}

			board[id_x][id_y] = pre;

			// Try all the candidates in the i-th hint
			for (int o = 0; o < candiList.size(); o++)
			{
				if (candiList[o] == pre) continue;
				copyBoard(leaveOneOut, tryCandidate);

				tryCandidate[id_x][id_y] = candiList[o];

				if (!isSudokuNoSolution(tryCandidate))
				{
					int space;
					eliminateTillStuck(tryCandidate, space);
					// If use this number can leads the remaining #blanks smaller
					if (blankCount > space)
					{
						blankCount = space;
						board[id_x][id_y] = candiList[o];
						if (blankCount == 0)
						{
							for (int i = 0; i < _N; i++)
								for (int j = 0; j < _N; j++)
									if (!pattern[i][j])
										board[i][j] = 0;
							return true;
						}
						stillHasSomethingToDo = true;
						break;
					}
				}
			}
			if (stillHasSomethingToDo)
			{
				/*
				// If we find a number that can leads the remaining 
				// #blanks smaller,go to next group instead of trying
				// next number in this group
				*/
				i = nextList[i];
			}
		}
	}

	if (blankCount != 0) return false;
	return true;
}