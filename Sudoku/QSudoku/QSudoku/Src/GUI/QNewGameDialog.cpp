#include "QNewGameDialog.h"
#include "QSudoku.h"

QNewGameDialog * QNewGameDialog::Instance = NULL;

QNewGameDialog::QNewGameDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.rAuto, SIGNAL(clicked(bool)), this, SLOT(modeAuto(bool)));
	connect(ui.rClues, SIGNAL(clicked(bool)), this, SLOT(modeClues(bool)));
	connect(ui.rManual, SIGNAL(clicked(bool)), this, SLOT(modeManual(bool)));
	connect(ui.bGenerate, SIGNAL(clicked()), this, SLOT(confirm()));
}

QNewGameDialog::~QNewGameDialog()
{

}

QNewGameDialog* QNewGameDialog::getInstance()
{
	if (Instance == NULL)
	{
		Instance = new QNewGameDialog;
	}

	return Instance;
}

void QNewGameDialog::modeAuto(bool b)
{
	ui.cDifficulty->setEnabled(true);
	ui.cClueCount->setEnabled(false);
}

void QNewGameDialog::modeManual(bool b)
{
	ui.cDifficulty->setEnabled(false);
	ui.cClueCount->setEnabled(false);
}

void QNewGameDialog::modeClues(bool b)
{
	ui.cDifficulty->setEnabled(false);
	ui.cClueCount->setEnabled(true);
}

void QNewGameDialog::init()
{
	ui.rAuto->setChecked(true);
	ui.cDifficulty->setEnabled(true);
	ui.cDifficulty->setCurrentIndex(0);
	ui.cClueCount->setEnabled(false);
	//ui.cMethod->setCurrentIndex(0);
}

void QNewGameDialog::confirm()
{
	if (ui.rAuto->isChecked())
	{
		gMode = GenerateMode::DIFFICULTIES;
		switch (ui.cDifficulty->currentIndex())
		{
		case 0:
			difficulty = EASY;
			break;
		case 1:
			difficulty = NORMAL;
			break;
		case 2:
			difficulty = ADVANCED;
			break;
		case 3:
			difficulty = EVIL;
			break;
		default:
			break;
		}
	}
	else if (ui.rClues->isChecked())
	{
		gMode = GenerateMode::CLUES;
		clueCount = ui.cClueCount->value();
	}
	else if (ui.rManual->isChecked())
	{
		gMode = GenerateMode::SUDOKU_PATTERN;
		clueCount = ui.cClueCount->value();
	}

	QSudoku::getInstance()->newGame(gMode);
	hide();
}
