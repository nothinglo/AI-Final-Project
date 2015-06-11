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
#include "sudoku-genGradientDescentBoard.h"
#include "sudoku-genRandomWalkBoard.h"
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
    
    srand((unsigned int)time(NULL));
    
	if (argc == 3 && (strcmp(argv[2], "-RW")==0)) {
		generateRandomWalkBoard(board, level * levelSpaceStep);
	} else if(argc == 3 && (strcmp(argv[2], "-f") == 0)) {
        if(generateByFileInputBoard(board, argv[1]) == false) {
            fprintf(stderr, "input file [%s] board format error.\n", argv[1]);
            return - 1;
        }
    } else if(argc == 3 && (strcmp(argv[2], "-s") == 0)) {
        generateGradientDescentBoard(board, atoi(argv[1]));
    } else {
		generateGradientDescentBoard(board, level * levelSpaceStep);
	}
    printUIBoard(board);
    printf("ansCount = %d, countSpace = %d\n", sudoku_answer_count(board), countSpace(board));
    
    return 0;
}
