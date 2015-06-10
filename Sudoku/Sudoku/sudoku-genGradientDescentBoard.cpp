//
//  sudoku-genGradientDescentBoard.cpp
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2015/5/23.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#include <algorithm>
#include "sudoku-operateBoard.h"

#include "consoleUI.h"

void getBoardCells(int board[][sudokuSize], vector<boardCell> & boardCells, int & Threshold, int nowS) {
    for(int i = 0; i < sudokuSize; ++i) {
        for(int j = 0; j < sudokuSize; ++j) {
            if(board[i][j] == 0) {
                const vector<int> & numbers = maybeNumbers(board, i, j);
                boardCell c(Threshold);
                for(int k = 0; k < numbers.size(); ++k) {
                    board[i][j] = numbers[k];
                    int count = sudoku_answer_count(board, c.solutions);
                    //printf("i = %d, j = %d, k = %d, c = %d, cs = %d\n", i, j, k, count, c.solutions);
                    if(count != 0 && (count < c.solutions || boardCells.size() == 0)) {
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
    int Threshold = 7000;
    return descentBoardCell(board, Threshold);
}
bool gradientDescentToBoard(int board[][sudokuSize]) {
    //printUIBoard(board);
    //printf("answerCount = %d, spaceCount = %d\n", sudoku_answer_count(board), countSpace(board));
    int Threshold = sudoku_answer_count(board);
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
void generateGradientDescentBoard(int board[][sudokuSize], const int spaceCount) {
    bool isDone;
    do {
        cout << "generateSpaceBoard() ing" << endl;
        while(generateSpaceBoard_NonUniqueSolution_ByData(board, spaceCount) == false || isSudokuNoSolution(board));
        cout << "gradientDescentToBoard() ing" << endl;
        isDone = gradientDescentToBoard(board);
    } while( isDone == false );
}

