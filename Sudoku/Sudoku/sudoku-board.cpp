//
//  sudoku-board.cpp
//  Sudoku
//
//  Created by uglyman.nothinglo on 2015/5/23.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#include <random>
#include <limits.h>
#include "sudoku-board.h"
#include "sudoku-answer-count.h"


#include "consoleUI.h"
#include <iostream>
using namespace std;

bool boardCheck(const int board[][sudokuSize], int x, int y, int num) {
    int i, j, time_1, time_2;
    
    for(i = 0; i < sudokuSize; ++i) {
        if(board[x][i] == num || board[i][y] == num) {
            return false;
        }
    }
    for(i=(x/3)*3, time_1=0; time_1 < 3; ++i, ++time_1) {
        for(j=(y/3)*3, time_2=0; time_2 < 3; ++j, ++time_2) {
            if(board[i][j] == num) {
                return false;
            }
        }
    }
    return true;
}

vector<int> maybeNumbers(int board[][sudokuSize], int x, int y) {
    vector<int> numbers;
    for(int num = 1; num <= sudokuSize; ++num) {
        if(boardCheck(board, x, y, num)) {
            numbers.push_back(num);
        }
    }
    return numbers;
}

int countSpace(const int board[][sudokuSize]) {
    int count = 0;
    for(int i = 0; i < sudokuSize; ++i) {
        for(int j = 0; j < sudokuSize; ++j) {
            if(board[i][j] == 0) {
                ++count;
            }
        }
    }
    return count;
}
bool generateSpaceBoard(int board[][sudokuSize], const int spaceCount) {
    for(int i = 0; i < sudokuSize; ++i) {
        for(int j = 0; j < sudokuSize; ++j) {
            board[i][j] = 0;
        }
    }
    for(int i = 0; i < spaceCount; ++i) {
        int index = rand() % sudokuLength;
        int x = index / sudokuSize;
        int y = index % sudokuSize;
        if(board[x][y] == -1) {
            --i;
        } else {
            board[x][y] = -1;
        }
    }
    
    for(int i = 0; i < sudokuSize; ++i) {
        for(int j = 0; j < sudokuSize; ++j) {
            if(board[i][j] == 0) {
                const vector<int> & numbers = maybeNumbers(board, i, j);
                if(numbers.size() == 0) {
                    return false;
                }
                if(countSpace(board) < 25) {
                    boardCell c(0);
                    for(int k = 0; k < numbers.size(); ++k) {
                        board[i][j] = numbers[k];
                        int count = sudoku_answer_count(board);
                        if(count > c.solutions) {
                            c = boardCell(i, j, numbers[k], count);
                        }
                    }
                    if(c.solutions == 0) {
                        return false;
                    }
                    board[i][j] = c.num;
                } else {
                    board[i][j] = numbers[rand() % numbers.size()];
                }
            } else {
                board[i][j] = 0;
            }
        }
    }
    return true;
}
bool gradientDescentToBoard(int board[][sudokuSize]) {
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
    }
    return true;
}
void generateRandomSpaceBoard(int board[][sudokuSize], const int spaceCount) {
    srand((unsigned int)time(NULL));
    bool isDone;
    do {
        while(generateSpaceBoard(board, spaceCount) == false || sudoku_answer_count(board) == 0);
        isDone = gradientDescentToBoard(board);
    } while( isDone == false );
}

