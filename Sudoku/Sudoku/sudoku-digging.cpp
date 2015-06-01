//
//  sudoku-board.cpp
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2015/5/23.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#include <random>
#include <limits.h>
#include <algorithm>
#include <time.h>
#include "sudoku-digging.h"
#include "sudoku-answer-count.h"
#include "consoleUI.h"

bool generateDigSpaceBoard(int board[][sudokuSize], const int spaceCount) {
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
    int space = sudokuLength, cutRange = 42;
    for(int i = 0; i < sudokuSize; ++i) {
        for(int j = 0; j < sudokuSize; ++j) {
            if(board[i][j] == 0) {
                --space;
                const vector<int> & numbers = maybeNumbers(board, i, j);
                if(numbers.size() == 0) {
                    return false;
                }
                if(space < cutRange) {
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
bool gradientDescentDigToBoard(int board[][sudokuSize]) {
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
}
void generateDiggingBoard(int board[][sudokuSize]) {
    srand((unsigned int)time(NULL));
    bool isDone;
	cout<<"generate a space board : "<<endl;
    do {
		while(generateDigSpaceBoard(board, 0) == false || sudoku_answer_count(board) == 0);
        isDone = gradientDescentDigToBoard(board);
    } while( isDone == false );
	printUIBoard(board);
	printf("ansCount = %d, countSpace = %d\n", sudoku_answer_count(board), countSpace(board));
	char again[10];
	while(1){
		cout<<"Do you want to dig (no to leave)?";
		cin>>again;
		if(strcmp(again,"no") == 0)
			break;
		while(1){
			cout<<"Where do you want to dig(1 1 ~ 9 9) ?";
			int x,y;
			cin>>x>>y;
			if(!(1 <= x && x <= sudokuSize && 1 <= y && y <= sudokuSize)){
				cout<<"This place is infeasible !"<<endl;
				continue;
			}
			board[x-1][y-1] = 0;
			if(sudoku_answer_count(board) != 1){
				cout<<"This place is infeasible !"<<endl;
			}
			else{
				printUIBoard(board);
				printf("ansCount = %d, countSpace = %d\n", sudoku_answer_count(board), countSpace(board));
			}
			cout<<"---------------"<<"Continue (no to leave)?"<<"---------------"<<endl;
			cin>>again;
			if(strcmp(again,"no") == 0)
				goto LEAVE;
		}
	}
LEAVE:;
}
