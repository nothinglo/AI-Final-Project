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
    int time = 0;
    while(space > 0) {
        int nowSpace = space;
        for(int i = 0; i < hasNumber.size(); ++i) {
            const int & x = hasNumber[i].first, y = hasNumber[i].second;
            board[x][y] = 0;
            if(isSudokuUniqueSolution(board)) {
                hasNumber.erase(hasNumber.begin() + i);
                --space;
                break;
            }
            board[x][y] = answer[x][y];
        }
        if(nowSpace == space) {
            printf("Generate %d space board fail time = %d\n", initSpace, ++time);
            space = initSpace;
            generateRandomFullFilledBoard(board);
            hasNumber = fullPos;
        }
        std::random_shuffle(hasNumber.begin(), hasNumber.end());
    }
    return hasNumber;
}

void generatePerfectRandomWalkBoard(int board[][sudokuSize], const int spaceCount) {
    generateRandomFullFilledBoard(board);
    int answer[sudokuSize][sudokuSize];
    copyBoard(board, answer);
    
    vector<pair<int, int> > numbers, blanks;
    for(int i = 0; i < sudokuSize; ++i) {
        for(int j = 0; j < sudokuSize; ++j) {
            numbers.push_back(make_pair(i, j));
        }
    }
    std::random_shuffle(numbers.begin(), numbers.end());
    int space = spaceCount;
//    int r = 1;
//    int n = (int)numbers.size();
//    while(space) {
//        int nowSpace = space;
//        printf("space = %d\n", space);
//        std::vector<bool> v(n);
//        std::fill(v.begin() + r, v.end(), true);
//        int loop1 = 0;
//        do {
//            printf("loop1 = %d\n", ++loop1);
//            vector<int> removeNumbers;
//            vector<pair<int, int> > newBlanks;
//            for(int i = n - 1; i >= 0; --i) {
//                if(!v[i]) {
//                    const int & x = numbers[i].first, y = numbers[i].second;
//                    board[x][y] = 0;
//                    newBlanks.push_back(numbers[i]);
//                    removeNumbers.push_back(i);
//                }
//            }
//            int m = r - 1;
//            if(m > 0) {
//                int s = sudokuLength - n;
//                printf("s = %d\n", s);
//                std::vector<bool> v2(s);
//                std::fill(v2.begin() + m, v2.end(), true);
//                int loop2 = 0;
//                do {
//                    printf("loop2 = %d, r = %d\n", ++loop2, r);
//                    vector<int> removeBlanks;
//                    vector<pair<int, int> > newNumbers;
//                    for(int i = s - 1; i >= 0; --i) {
//                        if(!v2[i]) {
//                            const int & x = blanks[i].first, y = blanks[i].second;
//                            board[x][y] = answer[x][y];
//                            newNumbers.push_back(blanks[i]);
//                            removeBlanks.push_back(i);
//                        }
//                    }
//                    printf("answerCount = %d\n", sudoku_answer_count(board, 2));
//                    if(isSudokuUniqueSolution(board)) {
//                        for(int i = 0; i < removeNumbers.size(); ++i) {
//                            numbers.erase(numbers.begin() + removeNumbers[i]);
//                        }
//                        for(int i = 0; i < removeBlanks.size(); ++i) {
//                            blanks.erase(blanks.begin() + removeBlanks[i]);
//                        }
//                        for(int i = 0; i < newNumbers.size(); ++i) {
//                            numbers.push_back(newNumbers[i]);
//                        }
//                        for(int i = 0; i < newBlanks.size(); ++i) {
//                            blanks.push_back(newBlanks[i]);
//                        }
//                        --space;
//                        break;
//                    } else {
//                        for(int i = 0; i < newNumbers.size(); ++i) {
//                            const int & x = newNumbers[i].first, y = newNumbers[i].second;
//                            board[x][y] = 0;
//                        }
//                    }
//                } while(std::next_permutation(v2.begin(), v2.end()));
//            } else {
//                if(isSudokuUniqueSolution(board)) {
//                    for(int i = 0; i < newBlanks.size(); ++i) {
//                        blanks.push_back(newBlanks[i]);
//                    }
//                    for(int i = 0; i < removeNumbers.size(); ++i) {
//                        numbers.erase(numbers.begin() + removeNumbers[i]);
//                    }
//                    --space;
//                } else {
//                    for(int i = 0; i < newBlanks.size(); ++i) {
//                        const int & x = newBlanks[i].first, y = newBlanks[i].second;
//                        board[x][y] = answer[x][y];
//                    }
//                }
//            }
//            if(nowSpace != space) {
//                --n;
//                break;
//            }
//        } while(std::next_permutation(v.begin(), v.end()));
//        if(nowSpace == space) {
//            ++r;
//        } else {
//            r = 1;
//        }
//    }
    
    while(space) {
        int nowSpace = space;
        for(int i = 0; i < numbers.size(); ++i) {
            const int & x = numbers[i].first, y = numbers[i].second;
            board[x][y] = 0;
            if(isSudokuUniqueSolution(board)) {
                blanks.push_back(numbers[i]);
                numbers.erase(numbers.begin() + i);
                --space;
                break;
            }
            board[x][y] = answer[x][y];
        }
        if(nowSpace == space) {
            break;
        }
    }
    printUIBoard(board);
    printf("ansCount = %d, countSpace = %d\n", sudoku_answer_count(board), countSpace(board));
    printf("space = %d\n", space);
    std::random_shuffle(blanks.begin(), blanks.end());
    while(space) {
        int nowSpace = space;
        for(int i = 0; i < numbers.size(); ++i) {
            printf("i = %d\n", i);
            const int & x = numbers[i].first, y = numbers[i].second;
            board[x][y] = 0;
            for(int j = i + 1; j < numbers.size(); ++j) {
                printf("j = %d\n", j);
                const int & x2 = numbers[j].first, y2 = numbers[j].second;
                board[x2][y2] = 0;
                for(int k = 0; k < blanks.size(); ++k) {
                    printf("k = %d\n", k);
                    const int & x3 = blanks[k].first, y3 = blanks[k].second;
                    board[x3][y3] = answer[x3][y3];
                    if(isSudokuUniqueSolution(board)) {
                        blanks.push_back(numbers[i]);
                        blanks.push_back(numbers[j]);
                        numbers.push_back(blanks[k]);
                        numbers.erase(numbers.begin() + j);
                        numbers.erase(numbers.begin() + i);
                        blanks.erase(blanks.begin() + k);
                        --space;
                        break;
                    }
                    if(nowSpace != space) {
                        break;
                    }
                    board[x3][y3] = 0;
                }
                if(nowSpace != space) {
                    break;
                }
                board[x2][y2] = answer[x2][y2];
            }
            if(nowSpace != space) {
                break;
            }
            board[x][y] = answer[x][y];
        }
        if(nowSpace == space) {
            break;
        }
        printf("space = %d, nowS = %d\n", space, nowSpace);
    }
}