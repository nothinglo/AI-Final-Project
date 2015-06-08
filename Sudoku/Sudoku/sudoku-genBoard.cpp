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
bool gradientDescentToBoard(int board[][sudokuSize]) {
    printUIBoard(board);
    printf("answerCount = %d\n", sudoku_answer_count(board));
    while(sudoku_answer_count(board) > 1) {
        vector<boardCell> boardCells;
        for(int i = 0; i < sudokuSize; ++i) {
            for(int j = 0; j < sudokuSize; ++j) {
                if(board[i][j] == 0) {
                    const vector<int> & numbers = maybeNumbers(board, i, j);
                    boardCell c(std::numeric_limits<int>::max());
                    for(int k = 0; k < numbers.size(); ++k) {
                        board[i][j] = numbers[k];
                        int count = sudoku_answer_count(board);
                        if(count != 0 && count < c.solutions) {
                            c = boardCell(i, j, numbers[k], count);
                        }
                    }
                    boardCells.push_back(c);
                    board[i][j] = 0;
                }
            }
        }
        if(boardCells.size() == 0) {
            return false;
        }
        sort(boardCells.begin(), boardCells.end());
        boardCell & c = boardCells[0];
        board[c.x][c.y] = c.num;
        
        printUIBoard(board);
        printf("answerCount = %d\n", sudoku_answer_count(board));
    }
    return true;
}
void generateRandomSpaceBoard(int board[][sudokuSize], const int spaceCount) {
    srand((unsigned int)time(NULL));
    bool isDone;
    do {
        cout << "generateSpaceBoard() ing" << endl;
        while(generateSpaceBoard_NonUniqueSolution_ByData(board, spaceCount) == false || sudoku_answer_count(board) == 0);
        cout << "gradientDescentToBoard() ing" << endl;
        isDone = gradientDescentToBoard(board);
    } while( isDone == false );
}

