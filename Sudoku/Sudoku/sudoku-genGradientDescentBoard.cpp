//
//  sudoku-genGradientDescentBoard.cpp
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2015/5/23.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#include <algorithm>
#include "sudoku-operateBoard.h"
#include "sudoku-genRandomWalkBoard.h"

#include "consoleUI.h"

/***************************************************/
/******************* not used now ******************/
/***************************************************/

void getBoardCells(int board[][sudokuSize], vector<boardCell> & boardCells, int & Threshold, int nowS) {
    for(int i = 0; i < sudokuSize; ++i) {
        for(int j = 0; j < sudokuSize; ++j) {
            if(board[i][j] == 0) {
                const vector<int> & numbers = maybeNumbers(board, i, j);
                boardCell c(Threshold);
                for(int k = 0; k < numbers.size(); ++k) {
                    board[i][j] = numbers[k];
                    int count = solveSudoku(board, false, true, true, c.solutions);
                    //printf("i = %d, j = %d, k = %d, c = %d, cs = %d\n", i, j, k, count, c.solutions);
                    if(count != 0 && (count < c.solutions || boardCells.empty())) {
                        c = boardCell(i, j, numbers[k], count);
                        if(count == 1 /* || (nowS > 2000 && count < nowS / 10) */ ) {
                            Threshold = count;
                            boardCells.push_back(c);
                            return;
                        }
                    }
                }
                if(c.null == false) {
                    boardCells.push_back(c);
                    Threshold = c.solutions;
                }
                board[i][j] = 0;
            }
        }
    }
}
const boardCell descentBoardCell(int board[][sudokuSize], int & Threshold) {
    vector<boardCell> boardCells;
    boardCell bc(0);
    getBoardCells(board, boardCells, Threshold, Threshold);
    if(boardCells.size() == 0) {
        return bc;
    }
    sort(boardCells.begin(), boardCells.end());
    return boardCells[0];
}
const boardCell descentBoardCell(int board[][sudokuSize]) {
    int Threshold = min(UpperBoundOfFindSolution, solveSudoku(board, false, true, true, UpperBoundOfFindSolution));
    return descentBoardCell(board, Threshold);
}
bool gradientDescentToBoard(int board[][sudokuSize]) {
    //printUIBoard(board);
    //printf("answerCount = %d, spaceCount = %d\n", sudoku_answer_count(board), countSpace(board));
    int Threshold = min(UpperBoundOfFindSolution, solveSudoku(board, false, true, true, UpperBoundOfFindSolution));
    cout << Threshold << endl;
    while(isSudokuUniqueSolution(board) == false) {
        vector<boardCell> boardCells;
        const boardCell & c = descentBoardCell(board, Threshold);
        if(c.null) {
            cout << "fff" << endl;
            return false;
        }
        board[c.x][c.y] = c.num;
        cout << "done : " << c.solutions << endl;
        //printUIBoard(board);
        //printf("answerCount = %d, spaceCount = %d\n", sudoku_answer_count(board), countSpace(board));
    }
    return true;
}
/***************************************************/
/***************************************************/
/***************************************************/

const boardCell getOneSolutionBoardCell(int board[][sudokuSize], int i, int j) {
    const vector<int> & numbers = maybeNumbers(board, i, j);
    boardCell c(0);
    for(int k = 0; k < numbers.size(); ++k) {
        board[i][j] = numbers[k];
		if (isSudokuUniqueSolution(board)) {
            return boardCell(i, j, numbers[k], 1);
        }
    }
    board[i][j] = 0;
    return c;
}
const boardCell getOneSolutionBoardCellForAll(int board[][sudokuSize]) {
    boardCell c(0);
    const vector<pair<int, int> > & blanks = getHasBlank(board);
    for(int i = 0; i < blanks.size(); ++i) {
        const boardCell & ok = getOneSolutionBoardCell(board, blanks[i].first, blanks[i].second);
        if(ok.null == false) {
            return ok;
        }
    }
    return c;
}
bool getOneSolutionBoardCell_2(int board[][sudokuSize], int i, int j, int i2, int j2) {
    const vector<int> & numbers = maybeNumbers(board, i, j);
    for(int k = 0; k < numbers.size(); ++k) {
        board[i][j] = numbers[k];
        const vector<int> & numbers2 = maybeNumbers(board, i2, j2);
        for(int k2 = 0; k2 < numbers2.size(); ++k2) {
            board[i2][j2] = numbers2[k2];
            if (isSudokuUniqueSolution(board)) {
                return true;
            }
        }
    }
    board[i][j] = 0;
    board[i2][j2] = 0;
    return false;
}
bool getOneSolutionBoardCellForAll_2(int board[][sudokuSize]) {
    const vector<pair<int, int> > & blanks = getHasBlank(board);
    for(int i = 0; i < blanks.size(); ++i) {
        for(int j = i + 1; j < blanks.size(); ++j) {
            if(getOneSolutionBoardCell_2(board, blanks[i].first, blanks[i].second,
                                                blanks[j].first, blanks[j].second)) {
                return true;
                
            }
        }
    }
    return false;
}

bool descentOneCellToOneSolution(int board[][sudokuSize], vector<pair<int, int> > & hasNumber) {
    const unsigned long size = hasNumber.size();
//    const float all =  100.f / ((size * (size - 1)) / 2);
//    int progress = 0;
    for(int i = 0; i < size; ++i) {
        const int & x1 = hasNumber[i].first, y1 = hasNumber[i].second;
        int tmp1 = board[x1][y1];
        board[x1][y1] = 0;
        for(int j = i + 1; j < size; ++j) {
            //printf("descentOneCellToOneSolution = %.2f%%\n", ++progress * all);
            const int & x2 = hasNumber[j].first, y2 = hasNumber[j].second;
            int tmp2 = board[x2][y2];
            board[x2][y2] = 0;
//            const boardCell & cell = getOneSolutionBoardCell(board, x2, y2);
//            boardCell c = cell;
//            if(c.null == true) {
//                c = getOneSolutionBoardCell(board, x1, y1);
//            }
            const boardCell & c = getOneSolutionBoardCellForAll(board);
            if(c.null == false) {
                hasNumber.push_back(make_pair(c.x, c.y));
                hasNumber.erase(hasNumber.begin() + j);
                hasNumber.erase(hasNumber.begin() + i);
                return true;
            }
            board[x2][y2] = tmp2;
        }
        board[x1][y1] = tmp1;
    }
    return false;
}
bool descentOneCellToOneSolution_3(int board[][sudokuSize]) {
    vector<pair<int, int> > hasNumber = getHasNumber(board);
    std::random_shuffle(hasNumber.begin(), hasNumber.end());
    const unsigned long size = hasNumber.size();
    
    const float all =  100.f / ((size * (size - 1) * (size - 2)) / 6);
    int progress = 0;
    
    for(int i = 0; i < size; ++i) {
        const int & x1 = hasNumber[i].first, y1 = hasNumber[i].second;
        int tmp1 = board[x1][y1];
        board[x1][y1] = 0;
        for(int j = i + 1; j < size; ++j) {
            const int & x2 = hasNumber[j].first, y2 = hasNumber[j].second;
            int tmp2 = board[x2][y2];
            board[x2][y2] = 0;
            for(int k = j + 1; k < size; ++k) {
                printf("descentOneCellToOneSolution = %.2f%%\n", ++progress * all);
                const int & x3 = hasNumber[k].first, y3 = hasNumber[k].second;
                int tmp3 = board[x3][y3];
                board[x3][y3] = 0;
                if(getOneSolutionBoardCellForAll_2(board)) {
                    return true;
                }
                board[x3][y3] = tmp3;
            }
            board[x2][y2] = tmp2;
        }
        board[x1][y1] = tmp1;
    }
    return false;
}
void generateGradientDescentBoard(int board[][sudokuSize], const int spaceCount) {
//    bool isDone;
//    do {
//        cout << "generateSpaceBoard() ing" << endl;
//        while(generateSpaceBoard_NonUniqueSolution_ByData(board, spaceCount) == false || isSudokuNoSolution(board));
//        cout << "gradientDescentToBoard() ing" << endl;
//        isDone = gradientDescentToBoard(board);
//    } while( isDone == false );
    
    const int Threshold = 60, firstT = 62;
    if(spaceCount <= Threshold) {
        generateRandomWalkBoard_noBackTrack(board, spaceCount, Threshold);
        return;
    }
    int nowSpace;
    do {
        vector<pair<int, int> > hasNumber = generateRandomWalkBoard_noBackTrack(board, spaceCount, Threshold);
        std::random_shuffle(hasNumber.begin(), hasNumber.end());
        
        nowSpace = Threshold;
        printf("Start, NOW BLANKS : %d\n", nowSpace);
        
        while(nowSpace != spaceCount) {
            if(nowSpace >= firstT) {
                if(descentOneCellToOneSolution_3(board) == false) {
                    break;
                }
            } else {
                if(descentOneCellToOneSolution(board, hasNumber) == false) {
                    break;
                }
            }
            ++nowSpace;
            printf("NOW BLANKS : %d\n", nowSpace);
        }
    } while(nowSpace != spaceCount);
}

void generateGradientDescentBoard_Back(int board[][sudokuSize], const int spaceCount) {
    generateGradientDescentBoard(board, spaceCount);
    vector<pair<int, int> > hasNumber = getHasNumber(board);
    const int step = 6;
    std::random_shuffle(hasNumber.begin(), hasNumber.end());
    for(int i = 0; i < step; ++i) {
        int index = rand() % hasNumber.size();
        const int & x1 = hasNumber[index].first, y1 = hasNumber[index].second;
        board[x1][y1] = 0;
        hasNumber.erase(hasNumber.begin() + index);
    }
    gradientDescentToBoard(board);
}