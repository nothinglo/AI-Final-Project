#include "QNewGameDialog.h"
#include "QSudoku.h"

QNewGameDialog * QNewGameDialog::Instance = NULL;

QNewGameDialog::QNewGameDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.rAuto, SIGNAL(clicked(bool)), this, SLOT(modeAuto(bool)));
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
	ui.gAuto->setEnabled(true);
	b ? printf("true\n") : printf("false\n");
}

void QNewGameDialog::modeManual(bool b)
{
	ui.gAuto->setEnabled(false);
	b ? printf("true\n") : printf("false\n");
}

void QNewGameDialog::init()
{
	ui.rAuto->setChecked(true);
	ui.gAuto->setEnabled(true);
	ui.cDifficulty->setCurrentIndex(0);
	//ui.cMethod->setCurrentIndex(0);
}

void QNewGameDialog::confirm()
{
	if (ui.rAuto->isChecked())
	{
		mode = true;
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

		/*switch (ui.cMethod->currentIndex())
		{
		case 0:
			method = GRADIENT_DESCENT;
			break;
		case 1:
			method = RANDOM_WALK;
			break;
		default:
			break;
		}*/
	}
	else
	{
		mode = false;
	}

	QSudoku::getInstance()->newGame(!mode);
	hide();
}
