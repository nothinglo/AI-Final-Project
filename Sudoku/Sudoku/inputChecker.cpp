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
#include <string.h>

bool checkParameter(int argc, const char * argv[]) {
    if(argc != 2 && argc != 3) {
        fprintf(stderr, "./exe [level: easy %d, difficult %d] ([-a])\n", minLevel, maxLevel);
        return false;
    }
    if(argc == 3 && strcmp(argv[2], "-f") == 0) {
        return true;
    }
    int level = atoi(argv[1]);
    if( (level >= minLevel && level <= maxLevel) == false ) {
        fprintf(stderr, "level range is : easy %d ~ difficult %d\n", minLevel, maxLevel);
        return false;
    }
    return true;
}