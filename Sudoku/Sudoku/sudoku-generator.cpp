//
//  sudoku-generator.cpp
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2015/5/23.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <chrono>
#include "globalVar.h"
#include "consoleUI.h"
#include "sudoku-board.h"
#include "sudoku-digging.h"
#include "sudoku-answer-count.h"
#include "sudoku-another-way.h"
#include "inputChecker.h"

using namespace std;
//arguments:
//[level] [method]
int main(int argc, const char * argv[]) {
	Param param;
    if(!param.checkParameter(argc, argv)) {
        return -1;
    }
    int level = param.level;
    int board[sudokuSize][sudokuSize];
    
	if (param.method == GENERATON_METHOD::RANDOMWALK) {
		auto start = std::chrono::system_clock::now();
		genSudokuAnotherWay(board, level * levelSpaceStep);
		auto end = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << elapsed.count() << endl;
	}
	else if (param.mode == GENERATON_MODE::DIGGING) {
		generateDiggingBoard(board);
	}
	else {
		generateRandomSpaceBoard(board, level * levelSpaceStep);
	}

	if (param.out_mode == CONSOLE_OUTPUT_MODE::PHP)
		printUIBoardforPHP(board);
	else
	{
		printUIBoard(board);
		printf("ansCount = %d, countSpace = %d\n", sudoku_answer_count(board), countSpace(board));
	}
		
    return 0;
}
