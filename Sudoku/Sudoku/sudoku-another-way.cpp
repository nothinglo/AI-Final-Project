#include "sudoku-board.h"
#include "sudoku-answer-count.h"
#include "sudoku-another-way.h"

int block_size;

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

void genSudokuAnotherWay(int board[][sudokuSize], const int spaceCount) {
	srand((unsigned int)time(NULL));

	block_size = sqrt(sudokuSize);

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
	for (int i = 0; i < sudokuSize; i++) {
		for (int j = 0; j < sudokuSize; j++) {
			board[i][j] = answered_board[i][j];
		}
	}

	int blank_count = spaceCount;

	for (int i = 0; i < sudokuSize; i++) {
		for (int j = 0; j < sudokuSize; j++) {
			while (blank_count > 0) {
				int x, y;
				x = rand() % sudokuSize;
				y = rand() % sudokuSize;
				int temp = board[x][y];

				if (temp != 0) {
					board[x][y] = 0;
					if (sudoku_answer_count(board) == 1) {
						blank_count--;
					}
					else {
						board[x][y] = temp;
					}
				}
			}
		}
	}
}