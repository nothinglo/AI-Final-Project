//
//  sudoku-generator.cpp
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2015/5/23.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#include <iostream>
#include "globalVar.h"
#include "consoleUI.h"
#include "sudoku-board.h"
#include "sudoku-digging.h"
#include "sudoku-answer-count.h"
#include "sudoku-another-way.h"
#include "inputChecker.h"

using namespace std;

int main(int argc, const char * argv[]) {
    if(checkParameter(argc, argv) == false) {
        return -1;
    }
    int level = atoi(argv[1]);
    int board[sudokuSize][sudokuSize];
    
	if (argc == 3 && (strcmp(argv[2], "-a")==0)) {
		genSudokuAnotherWay(board, level * levelSpaceStep);
	} else if(argc == 3 && string(argv[2]) == "-dig"){
		generateDiggingBoard(board);
	}
	else {
		generateRandomSpaceBoard(board, level * levelSpaceStep);
	}
    printUIBoard(board);
    printf("ansCount = %d, countSpace = %d\n", sudoku_answer_count(board), countSpace(board));

    return 0;
}
