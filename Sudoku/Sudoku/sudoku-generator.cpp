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
#include "sudoku-operateBoard.h"
#include "sudoku-genBoard.h"
#include "sudoku-digging.h"
#include "sudoku-another-way.h"
#include "inputChecker.h"

#include "logicalSolver.h"

using namespace std;
//arguments:
//[level] [method]
int main(int argc, const char * argv[]) {
    if(checkParameter(argc, argv) == false) {
        return -1;
    }
    int level = atoi(argv[1]);
    int board[sudokuSize][sudokuSize];
    
	if (argc == 3 && (strcmp(argv[2], "-a")==0)) {
		genSudokuAnotherWay(board, level * levelSpaceStep);
	} else if(argc == 3 && (strcmp(argv[2], "-dig")==0)){
		generateDiggingBoard(board);
    } else if(argc == 3 && (strcmp(argv[2], "-f") == 0)) {
        generateByFileInputBoard(board, argv[1]);
    } else {
		generateRandomSpaceBoard(board, level * levelSpaceStep + 1);
	}
    printUIBoard(board);
    printf("ansCount = %d, countSpace = %d\n", sudoku_answer_count(board), countSpace(board));
    
    return 0;
}
