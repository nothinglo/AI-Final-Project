#ifndef QSUDOKUGAME_H
#define QSUDOKUGAME_H

#include <vector>
#include <QtWidgets>
#include <QObject>
#include <QTime>
#include "QSudokuScene.h"
#include "Generator.h"
using namespace std;

class QSudokuScene;

class QSudokuGame : public QObject
{
	Q_OBJECT

public:
	QSudokuGame();
	~QSudokuGame();

	// get current board
	vector<vector<int> > getBoard(){ return m_board; }

	// get original board
	vector<vector<int> > getOriginalBoard(){ return m_originalBoard; }

	// get current choices in cell (x, y)
	vector<bool> getChoices(int x, int y) const { return m_choices[x][y]; }

	// set choices in cell (x, y) with given configuration
	void setChoices(int x, int y, vector<bool> choices);
	
	// solve the current board
	bool solve(void);

	// get value in cell (x, y)
	int getBoardValue(int x, int y) const { return m_board[x][y]; }

	// get QSudokuScene instance
	void setSudokuScene();

	// generate board by some algorithms
	void newGameAuto();

	// generate a blank board that user can draw something on it
	void newGameManual();

	// generate board by user-specified pattern
	void generateBoardWithConstraint(bool pattern[][_N]);

	// check if the current board is valid or not
	bool isBoardValid(void);

	// give user a hint
	void showOneStepHint();

	static QSudokuGame* getInstance();
	static QSudokuGame *Instance;

public slots:
	
	void reset();

	// set a number to be in the "chosen" state in cell (x, y)
	void enableChoice(int x, int y, int number){ m_choices[x][y][number - 1] = true; }

	// set a number to be in the "unchosen" state in cell (x, y)
	void disableChoice(int x, int y, int number){ m_choices[x][y][number - 1] = false; }

	// set final choice in cell (x, y), move the state of a cell from "chosen/unchosen" state to "final"
	void setFinalChoice(int x, int y, int number);

	// unset final choice in cell (x, y), move the state of a cell from "final" state to "chosen/unchosen"
	void unsetFinalChoice(int x, int y){ m_board[x][y] = 0; }

private slots:
	void updateDuration(void);

signals:
	void durationUpdated(unsigned int);

private:
	// reset choices in all cells
	void initialize();

	// generate board according to specified difficulty and method
	// the variables can be found at QNewGameDialog
	void generateBoard(void);

	// after generating the board, store it as original one 
	void storeOriginalBoard(void);

	vector<vector<int> > m_originalBoard;
	vector<vector<int> > m_board;
	vector<vector<vector<bool> > > m_choices;

	unsigned int m_duration;

	bool m_valid;

	// Timers.
	QTimer *m_durationTimer;
	QSudokuScene *m_scene;
};

#endif