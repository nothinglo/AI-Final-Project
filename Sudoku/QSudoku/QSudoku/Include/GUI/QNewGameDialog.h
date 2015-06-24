#ifndef QNEWGAMEDIALOG_H
#define QNEWGAMEDIALOG_H

#include <QWidget>
#include "ui_QNewGameDialog.h"

const enum Difficulty {EASY, NORMAL, ADVANCED, EVIL};
const enum Method {GRADIENT_DESCENT, RANDOM_WALK};
const enum GenerateMode {DIFFICULTIES, CLUES, SUDOKU_PATTERN};

class QNewGameDialog : public QWidget
{
	Q_OBJECT

public:
	QNewGameDialog(QWidget *parent = 0);
	~QNewGameDialog();
	
	void init();
	static QNewGameDialog* getInstance();
	static QNewGameDialog *Instance;

	Difficulty difficulty;
	unsigned int clueCount;
	Method method;
	GenerateMode gMode;
	bool mode; // true = auto, false = manual

private:
	Ui::QNewGameDialog ui;

private slots:
	void modeAuto(bool b);
	void modeManual(bool b);
	void modeClues(bool b);
	void confirm();
};

#endif // QNEWGAMEDIALOG_H
