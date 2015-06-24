#include "QSudokuGame.h"
#include "QNewGameDialog.h"
#include "sudoku-genGradientDescentBoard.h"
#include "sudoku-genRandomWalkBoard.h"
#include "logicalSolver.h"
#include "consoleUI.h"
#include <chrono>
QSudokuGame* QSudokuGame::Instance = NULL;
QSudokuGame::QSudokuGame()
{
	// initialize all boards
	m_board			= vector<vector<int> >(sudokuSize, vector<int>(sudokuSize, 0));
	m_originalBoard = vector<vector<int> >(sudokuSize, vector<int>(sudokuSize, 0));
	m_choices		= vector<vector<vector<bool> > >(sudokuSize, vector<vector<bool> >(sudokuSize, vector<bool>(sudokuSize, false)));

	// initialize timer
	m_duration = 0;
	m_durationTimer = NULL;
}

QSudokuGame::~QSudokuGame()
{

}

QSudokuGame* QSudokuGame::getInstance()
{
	if (Instance == NULL)
	{
		Instance = new QSudokuGame;
	}

	return Instance;
}

void QSudokuGame::initialize()
{
	m_valid = true;

	// each cell has [sudikuSize] choices
	for (int x = 0; x < sudokuSize; x++)
	for (int y = 0; y < sudokuSize; y++)
	for (int z = 0; z < sudokuSize; z++)
		m_choices[x][y][z] = false;
}

void QSudokuGame::setChoices(int x, int y, vector<bool> choices) 
{
	for (int i = 0; i < sudokuSize; i++)
		m_choices[x][y][i] = choices[i];
}

bool QSudokuGame::solve(void) 
{
	bool status = false;

	// status = Sudoku::SolveBoard(m_board);

	// Stop the timer and reset the duration to 0, to indicate that the user
	// didn't solve the Sudoku.
	m_durationTimer->stop();
	m_duration = 0;
	durationUpdated(m_duration);

	return status;
}

void QSudokuGame::reset(void) 
{
	m_duration = 0;

	for (int x = 0; x < sudokuSize; x++)
	for (int y = 0; y < sudokuSize; y++)
	{
		m_board[x][y] = m_originalBoard[x][y];

		for (int i = 0; i < sudokuSize; i++)
			m_choices[x][y][i] = false;
	}	
}

void QSudokuGame::setFinalChoice(int x, int y, int number) 
{
	m_board[x][y] = number;

	/*
	if (m_board->IsFull() && m_board->IsValid()) 
	{
		m_finished = true;
		m_durationTimer->stop();
	}*/
}

void QSudokuGame::updateDuration(void) 
{
	m_duration++;
	durationUpdated(m_duration);
}

void QSudokuGame::generateBoard(bool m) 
{
	int board[sudokuSize][sudokuSize];

	if (m)
	{
		generateLevelBoard(board, QNewGameDialog::getInstance()->difficulty);
	}
	else
	{
		generateGradientDescentBoard(board, sudokuLength - QNewGameDialog::getInstance()->clueCount);
	}
	

	int test[sudokuSize][sudokuSize];
	copyBoard(board, test);
	//cout << logicalSolver(test) << endl;

	for (int i = 0; i < sudokuSize; i++)
	for (int j = 0; j < sudokuSize; j++)
		m_board[i][j] = m_originalBoard[i][j] = board[j][i];

	m_scene->setAllElements();
}

void QSudokuGame::storeOriginalBoard(void) 
{
	for (int x = 0; x < sudokuSize; x++)
	for (int y = 0; y < sudokuSize; y++)
		m_originalBoard[x][y] = m_board[x][y];
}

void QSudokuGame::newGameAuto(void) 
{
	initialize();

	if (QNewGameDialog::getInstance()->gMode == GenerateMode::DIFFICULTIES)
	{
		generateBoard(true);
	}
	else if (QNewGameDialog::getInstance()->gMode == GenerateMode::CLUES)
	{
		generateBoard(false);
	}
	

	m_duration = 0;
	m_durationTimer = new QTimer(this);
	connect(m_durationTimer, SIGNAL(timeout()), this, SLOT(updateDuration()));
	m_durationTimer->start(1000);
}

void QSudokuGame::newGameManual()
{
	initialize();

	// go to the "drawing" mode for user to draw something
	m_scene->setManualMode();
}

void QSudokuGame::newGameClues()
{

}

bool QSudokuGame::isBoardValid() 
{
	return true;
}

void QSudokuGame::setSudokuScene()
{
	m_scene = QSudokuScene::getInstance();
}

void QSudokuGame::generateBoardWithConstraint(bool pattern[][_N])
{	
	int board[sudokuSize][sudokuSize];

	int c = 0;
	while (true)
	{
		c++;

		bool done = generateWithSpecifiedPattern(board, pattern);

		if (done) break;
	}
	cout << "Times : " << c << endl;

	//printUIBoard(board);

	for (int i = 0; i < sudokuSize; i++)
	for (int j = 0; j < sudokuSize; j++)
		m_board[i][j] = m_originalBoard[i][j] = board[j][i];	

	cout << "Answer Count : " << solveSudoku(board, false, true) << endl;
	m_scene->setAllElements();
}

void QSudokuGame::showOneStepHint()
{
	int x, y, num, type;

	int board[sudokuSize][sudokuSize];
	for (int i = 0; i < sudokuSize; i++)
	for (int j = 0; j < sudokuSize; j++)
		board[i][j] = m_board[j][i];

	//printUIBoard(board);
	if (hintOneStep(board, &num, &x, &y, &type))
	{
		m_scene->setOneStepHint(x, y, num + 1, type);
	}
}

