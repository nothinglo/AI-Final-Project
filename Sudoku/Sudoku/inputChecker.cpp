//
//  inputChecker.cpp
//  AI-Final-Project
//
//  Created by uglyman.nothinglo on 2015/5/24.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#include "inputChecker.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>

using namespace std;

Param::Param()
{
	method   = GAUSSIAN_DESCENT;
	mode	 = NORMAL;
	out_mode = OUT_NORMAL;
}

bool Param::checkParameter(int argc, const char * argv[]) {

	for (int i = 1; i < argc; i++)
	{
		char * pEnd;
		int l = strtol(argv[i], &pEnd, 10);

		if (l > 0)
		{
			if (l >= minLevel && l <= maxLevel)
			{
				level = l;
			}
			else
			{
				cout << "level you query : " << level << endl;
				cout << "level range is : easy " << minLevel << "~ difficult " << maxLevel << endl;
				return false;
			}
		}
		else if (strcmp(argv[i], "-a") == 0)
		{
			method = RANDOMWALK;
		}
		else if (strcmp(argv[i], "-dig") == 0)
		{
			mode = DIGGING;
		}
		else if (strcmp(argv[i], "-php") == 0)
		{
			out_mode = PHP;
		}
	}

    return true;
}