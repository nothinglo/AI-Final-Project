//
//  consoleUI.cpp
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2015/5/23.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#include "consoleUI.h"
#include <iostream>

using namespace std;

void printSimpleBoard(int board[][sudokuSize]) {
    for(int i = 0; i < sudokuSize; ++i) {
        for(int j = 0; j < sudokuSize; ++j) {
            cout << " " << board[i][j];
        }
        cout << endl;
    }
}

void printUIBoard(int board[][sudokuSize]) {
    for(int i = 0; i < sudokuSize; ++i) {
        if(i % 3 == 0) {
            cout << " - - - - - - - - -" << endl;
        }
        for(int j = 0; j < sudokuSize; ++j) {
            if(j == sudokuSize - 1) {
                cout << " " << board[i][j] << "|";
            } else if(j % 3 == 0) {
                cout << "|" << board[i][j];
            } else {
                cout << " " << board[i][j];
            }
        }
        cout << endl;
    }
    cout << " - - - - - - - - -" << endl;
}

void printUIBoardforPHP(int board[][sudokuSize]) {
    for(int i = 0; i < sudokuSize; ++i) {
        for(int j = 0; j < sudokuSize; ++j) {
                cout << board[i][j] << ";";
        }
    }
}