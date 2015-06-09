#include "sudoku-operateBoard.h"
#include "sudoku-another-way.h"


#include "consoleUI.h"
void genSudokuAnotherWay(int board[][sudokuSize], const int spaceCount) {
	srand((unsigned int)time(NULL));

	int answered_board[9][9] = {
		{ 5, 3, 4, 6, 7, 8, 9, 1, 2 },
		{ 6, 7, 2, 1, 9, 5, 3, 4, 8 },
		{ 1, 9, 8, 3, 4, 2, 5, 6, 7 },
		{ 8, 5, 9, 7, 6, 1, 4, 2, 3 },
		{ 4, 2, 6, 8, 5, 3, 7, 9, 1 },
		{ 7, 1, 3, 9, 2, 4, 8, 5, 6 },
		{ 9, 6, 1, 5, 3, 7, 2, 8, 4 },
		{ 2, 8, 7, 4, 1, 9, 6, 3, 5 },
		{ 3, 4, 5, 2, 8, 6, 1, 7, 9 },
	};

	// disturb the board
	for (int i = 0; i < 100; i++) {
		randomChange2Units(answered_board);
	}

	// copy data from answered_board to board
    copyBoard(answered_board, board);

	int blank_count = spaceCount;

    while (blank_count > 0) {
        int x, y;
        x = rand() % sudokuSize;
        y = rand() % sudokuSize;
        int temp = board[x][y];
        
        if (temp != 0) {
            board[x][y] = 0;
            if (sudoku_answer_count(board, 2) == 1) {
                --blank_count;
            }
            else {
                board[x][y] = temp;
            }
        }
    }
}