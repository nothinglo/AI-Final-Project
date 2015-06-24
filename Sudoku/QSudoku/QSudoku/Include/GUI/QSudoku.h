#ifndef QSUDOKU_H
#define QSUDOKU_H

#include <QtWidgets/QMainWindow>
#include <QTime>
#include "ui_QSudoku.h"

#include "QSudokuGame.h"
#include "QSudokuScene.h"
#include "QSudokuView.h"
#include "QNewGameDialog.h"

class QSudoku : public QMainWindow
{
	Q_OBJECT

public:
	QSudoku(QWidget *parent = 0);
	~QSudoku();
	void newGame(GenerateMode mode);

	static QSudoku* getInstance();

private:
	Ui::QSudokuClass ui;
	static QSudoku *Instance;

	QSudokuGame		*m_game;
	QSudokuScene	*m_scene;
	QSudokuView		*m_view;
	QNewGameDialog	*m_newGame;

private slots:
	void ExitApp();
	void OpenNewGameDialog();
	void ChangeToBigBoard();
	void ChangeToSmallBoard();
	void HintOneStep();
};

#endif // QSUDOKU_H
