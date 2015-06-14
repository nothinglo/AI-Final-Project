//
//  sudoku-operateBoard.cpp
//  Sudoku
//
//  Created by uglyman.nothinglo on 2015/6/8.
//  Copyright (c) 2015年 nothinglo. All rights reserved.
//

#include "sudoku-operateBoard.h"
#include "solver.h"
#include <fstream>

#include <algorithm>// std::random_shuffle
#include <string>// stoi

#include "consoleUI.h"

void copyBoard(const int board[][sudokuSize], int nBoard[][sudokuSize]) {
    for (int i = 0; i < sudokuSize; ++i) {
        for (int j = 0; j < sudokuSize; ++j) {
            nBoard[i][j] = board[i][j];
        }
    }
}
bool generateByFileInputBoard(int board[][sudokuSize], const char *fileName) {
    string str;
    fstream file(fileName);
    int index = 0;
    char c = '\0';
    while(file.get(c)) {
        if(isdigit(c)) {
            str += c;
        } else if(str.length() > 0) {
            int i = index / sudokuSize;
            int j = index % sudokuSize;
            board[i][j] = stoi(str);
            if(++index == sudokuLength) {
                return true;
            }
            str.clear();
        }
    }
    if(str.length() > 0 && index == sudokuLength - 1) {
        int i = index / sudokuSize;
        int j = index % sudokuSize;
        board[i][j] = stoi(str);
        return true;
    }
    return false;
}
void findPlace(int board[][sudokuSize], int* sum, const int threshold, int x, int y){
    if(x == sudokuSize) {
        ++y, x = 0;
    }
    if(y == sudokuSize) {
        ++(*sum);
        return;
    }
    if(board[x][y] >= 1 && board[x][y] <= sudokuSize) {
        findPlace(board, sum, threshold, x+1, y);
    } else {
        for(int num = 1; num <= sudokuSize; ++num) { //try 1~9
            if(boardCheck(board, x, y, num)) {
                board[x][y] = num;
                findPlace(board, sum, threshold, x+1, y);
                if(*sum == threshold) {
                    return;
                }
                board[x][y] = 0;
            }
        }
    }
}
bool isSudokuUniqueSolution(const int board[][sudokuSize]) {
//    return sudoku_answer_count(board, 2) == 1;
    return solveSudoku(board, false, true, true, 1) == 1;
}
bool isSudokuNoSolution(const int board[][sudokuSize]) {
//    return sudoku_answer_count(board, 1) == 0;
    return solveSudoku(board, false, true, true, 1) == 0;
}
int sudoku_answer_count(const int board[][sudokuSize], const int threshold) {
    int sum = 0, tmpBoard[sudokuSize][sudokuSize];
    copyBoard(board, tmpBoard);
    findPlace(tmpBoard, &sum, threshold, 0, 0);
    return sum;
}

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
    /*diagnosis
     if(x == y){
     for(i = 0; i < sudokuSize; ++i) {
     if(board[i][i] == num) {
     return false;
     }
     }
     }
     else if(x == 8-y){
     for(i = 0; i < sudokuSize; ++i) {
     if(board[i][8-i] == num) {
     return false;
     }
     }
     }
     */
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
            if(board[i][j] <= 0) {
                ++count;
            }
        }
    }
    return count;
}

bool generateSpaceBoard_NonUniqueSolution(int board[][sudokuSize], const int spaceCount) {
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
//    int non_space = 0, randRange = 20;
//    for(int i = 0; i < sudokuSize; ++i) {
//        for(int j = 0; j < sudokuSize; ++j) {
//            if(board[i][j] == 0) {
//                ++non_space;
//                vector<int> numbers = maybeNumbers(board, i, j);
//                if(numbers.size() == 0) {
//                    return false;
//                }
//                if(non_space > randRange) {
//                    boardCell c(100);
//                    printf("nonSpace = %d\n", non_space);
//                    for(int k = 0; k < numbers.size(); ++k) {
//                        board[i][j] = numbers[k];
//                        printUIBoard(board);
//                        int count = sudoku_answer_count(board, c.solutions);
//                        printf("i = %d, j = %d, k = %d, count = %d, cs = %d\n", i, j, k, count, c.solutions);
//                        if(count != 0 && (count < c.solutions || c.null)) {
//                            c = boardCell(i, j, numbers[k], count);
//                        }
//                    }
//                    if(c.null) {
//                        return false;
//                    }
//                    board[i][j] = c.num;
//                } else {
//                    board[i][j] = numbers[rand() % numbers.size()];
////                    do {
////                        int index = rand() % numbers.size();
////                        board[i][j] = numbers[index];
////                        numbers.erase(numbers.begin() + index);
////                    } while(sudoku_answer_count(board, 1) == 0);
//                }
//            } else {
//                board[i][j] = 0;
//            }
//        }
//    }
    
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
bool generateSpaceBoard_NonUniqueSolution_ByRandomWalk(int board[][sudokuSize], const int spaceCount) {
    return true;
}
void randomChange2Cols(int board[sudokuSize][sudokuSize], int col1, int col2) {
    for (int i = 0; i < sudokuSize; i++) {
        int temp = board[i][col2];
        board[i][col2] = board[i][col1];
        board[i][col1] = temp;
    }
}
void randomChange2Rows(int board[sudokuSize][sudokuSize], int row1, int row2) {
    for (int i = 0; i < sudokuSize; i++) {
        int temp = board[row2][i];
        board[row2][i] = board[row1][i];
        board[row1][i] = temp;
    }
}

void randomChange2BlockCols(int board[sudokuSize][sudokuSize], int col1, int col2) {
    for (int n = 0; n < block_size; n++) {
        for (int i = 0; i < sudokuSize; i++) {
            int temp = board[i][col2 + n];
            board[i][col2 + n] = board[i][col1 + n];
            board[i][col1 + n] = temp;
        }
    }
}

void randomChange2BlockRows(int board[sudokuSize][sudokuSize], int row1, int row2) {
    for (int n = 0; n < block_size; n++) {
        for (int i = 0; i < sudokuSize; i++) {
            int temp = board[row2 + n][i];
            board[row2 + n][i] = board[row1 + n][i];
            board[row1 + n][i] = temp;
        }
    }
}

void randomChange2Units(int board[sudokuSize][sudokuSize])
{
    int choice = rand() % 2;
    switch (choice) {
        case 0: // change 2 cols or 2 rows in same block
        {
            int entry1 = rand() % sudokuSize;
            int entry2 = (entry1 + (rand() % (block_size - 1) + 1));
            
            // if entry1 & entry2 are not in the same block, revise entry2
            if (entry2 / block_size != entry1 / block_size)
                entry2 -= block_size;
            
            rand() % 2 == 0 ? randomChange2Cols(board, entry1, entry2) :
            randomChange2Rows(board, entry1, entry2);
        }
            break;
        case 1: // change 2 block-cols or 2 block-rows
        {
            vector<int> random2Entry;
            for (int i = 0; i < sudokuSize; i++) {
                // 4 * 4 sudoku will push {0, 2}
                // 9 * 9 sudoku will push {0, 3, 6}
                // ...
                if (i % block_size == 0) {
                    random2Entry.push_back(i);
                }
            }
            std::random_shuffle(random2Entry.begin(), random2Entry.end());
            
            rand() % 2 == 0 ? randomChange2BlockCols(board, random2Entry[0], random2Entry[1]) :
            randomChange2BlockRows(board, random2Entry[0], random2Entry[1]);
        }
            break;
    }
}

void generateRandomFullFilledBoard(int board[][sudokuSize], const int disturbCount) {
    /*int answered_board[sudokuSize][sudokuSize] = {
        { 5, 3, 4, 6, 7, 8, 9, 1, 2 },
        { 6, 7, 2, 1, 9, 5, 3, 4, 8 },
        { 1, 9, 8, 3, 4, 2, 5, 6, 7 },
        { 8, 5, 9, 7, 6, 1, 4, 2, 3 },
        { 4, 2, 6, 8, 5, 3, 7, 9, 1 },
        { 7, 1, 3, 9, 2, 4, 8, 5, 6 },
        { 9, 6, 1, 5, 3, 7, 2, 8, 4 },
        { 2, 8, 7, 4, 1, 9, 6, 3, 5 },
        { 3, 4, 5, 2, 8, 6, 1, 7, 9 },
    };*/
    
	int answered_board[sudokuSize][sudokuSize] = {
		{ 6, 3, 9, 2, 4, 1, 7, 8, 5 },
		{ 2, 8, 4, 7, 6, 5, 1, 9, 3 },
		{ 5, 1, 7, 9, 8, 3, 6, 2, 4 },
		{ 1, 2, 3, 8, 5, 7, 9, 4, 6 },
		{ 7, 9, 6, 4, 3, 2, 8, 5, 1 },
		{ 4, 5, 8, 6, 1, 9, 2, 3, 7 },
		{ 3, 4, 2, 1, 7, 8, 5, 6, 9 },
		{ 8, 6, 1, 5, 9, 4, 3, 7, 2 },
		{ 9, 7, 5, 3, 2, 6, 4, 1, 8 },
	};

    // disturb the board
    for (int i = 0; i < disturbCount; i++) {
        randomChange2Units(answered_board);
    }
    
    // copy data from answered_board to board
    copyBoard(answered_board, board);
}