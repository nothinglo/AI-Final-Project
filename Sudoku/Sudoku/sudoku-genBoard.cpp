//
//  sudoku-genBoard.cpp
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2015/5/23.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#include <random>
#include <limits.h>
#include <algorithm>
#include <time.h>
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
bool gradientDescentToBoard(int board[][sudokuSize]) {
    //printUIBoard(board);
    //printf("answerCount = %d, spaceCount = %d\n", sudoku_answer_count(board), countSpace(board));
    int Threshold = sudoku_answer_count(board);
    while(sudoku_answer_count(board, 2) > 1) {
        vector<boardCell> boardCells;
        int nowS = Threshold;
        getBoardCells(board, boardCells, Threshold, nowS);
        if(boardCells.size() == 0) {
            return false;
        }
        sort(boardCells.begin(), boardCells.end());
        const boardCell & c = boardCells[0];
        board[c.x][c.y] = c.num;
        //printUIBoard(board);
        //printf("answerCount = %d, spaceCount = %d\n", sudoku_answer_count(board), countSpace(board));
    }
    return true;
}
void generateRandomSpaceBoard(int board[][sudokuSize], const int spaceCount) {
    srand((unsigned int)time(NULL));
    bool isDone;
    do {
        cout << "generateSpaceBoard() ing" << endl;
        while(generateSpaceBoard_NonUniqueSolution_ByData(board, spaceCount) == false || sudoku_answer_count(board, 1) == 0);
        cout << "gradientDescentToBoard() ing" << endl;
        isDone = gradientDescentToBoard(board);
    } while( isDone == false );
}

