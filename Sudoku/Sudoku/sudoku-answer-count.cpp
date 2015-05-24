//
//  sudoku-answer-count.cpp
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2012/4/03.
//  Copyright (c) 2012年 nothinglo. All rights reserved.
//

#include "sudoku-answer-count.h"
#include "sudoku-board.h"

void findPlace(int board[][sudokuSize], int* sum, int x, int y){
    int num;
    
    if(x==9) {
        ++y, x = 0;
    }
    if(y==9) {
        ++(*sum);
        return;
    }
    if(board[x][y] != 0) {
        findPlace(board, sum, x+1, y);
    } else {
        for(num = 1; num <= sudokuSize; ++num) {
            if(boardCheck(board, x, y, num)) {
                board[x][y] = num;
                findPlace(board, sum, x+1, y);
                board[x][y] = 0;
            }
        }
    }
}
int sudoku_answer_count(int board[][sudokuSize]) {
    int sum = 0;
    findPlace(board, &sum, 0, 0);
    return sum;
}