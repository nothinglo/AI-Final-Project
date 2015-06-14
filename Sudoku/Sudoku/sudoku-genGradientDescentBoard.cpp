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
    for(int i = 0; i < sudokuSize; ++i) {
        for(int j = 0; j < sudokuSize; ++j) {
            if(board[i][j] == 0) {
                const boardCell & ok = getOneSolutionBoardCell(board, i, j);
                if(ok.null == false) {
                    return ok;
                }
            }
        }
    }
    return c;
}
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
                    if(count != 0 && count < c.solutions) {
                        c = boardCell(i, j, numbers[k], count);
                        if(count == 1 || (nowS > 2000 && count < nowS / 10)) {
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
	int Threshold = solveSudoku(board, false, true);
    while(isSudokuUniqueSolution(board) == false) {
        vector<boardCell> boardCells;
        const boardCell & c = descentBoardCell(board, Threshold);
        if(c.null) {
            return false;
        }
        board[c.x][c.y] = c.num;
        //printUIBoard(board);
        //printf("answerCount = %d, spaceCount = %d\n", sudoku_answer_count(board), countSpace(board));
    }
    return true;
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
                board[c.x][c.y] = c.num;
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
void generateGradientDescentBoard(int board[][sudokuSize], const int spaceCount) {
//    bool isDone;
//    do {
//        cout << "generateSpaceBoard() ing" << endl;
//        while(generateSpaceBoard_NonUniqueSolution_ByData(board, spaceCount) == false || isSudokuNoSolution(board));
//        cout << "gradientDescentToBoard() ing" << endl;
//        isDone = gradientDescentToBoard(board);
//    } while( isDone == false );
    
    const int Threshold = 60;
    if(spaceCount <= Threshold) {
        generateRandomWalkBoard_noBackTrack(board, spaceCount, Threshold);
        return;
    }
    int descentStep;
    do {
        vector<pair<int, int> > hasNumber = generateRandomWalkBoard_noBackTrack(board, spaceCount, Threshold);
        std::random_shuffle(hasNumber.begin(), hasNumber.end());
        descentStep = spaceCount - Threshold;
        int nowSpace = Threshold;
        printf("NOW BLANKS : %d\n", nowSpace);
        while(descentOneCellToOneSolution(board, hasNumber) && --descentStep) {
            printf("NOW BLANKS : %d\n", ++nowSpace);
        }
    } while(descentStep != 0);
}

