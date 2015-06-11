//
//  inputChecker.h
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2015/5/24.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#ifndef __Sudoku__inputChecker__
#define __Sudoku__inputChecker__

#include "globalVar.h"

using namespace std;

enum GENERATON_METHOD { GAUSSIAN_DESCENT, RANDOMWALK };
enum GENERATON_MODE { NORMAL, DIGGING };
enum CONSOLE_OUTPUT_MODE { OUT_NORMAL, PHP };

class Param {

public:
	Param();
	bool checkParameter(int argc, const char * argv[]);

	int level;
	GENERATON_METHOD method;
	GENERATON_MODE mode;
	CONSOLE_OUTPUT_MODE out_mode;
};
bool checkParameter(int argc, const char * argv[]);

#endif /* defined(__Sudoku__inputChecker__) */
