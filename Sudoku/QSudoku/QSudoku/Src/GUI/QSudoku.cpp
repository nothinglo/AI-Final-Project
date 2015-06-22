#include "QSudoku.h"

QSudoku *QSudoku::Instance = NULL;
QSudoku::QSudoku(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.aExit, SIGNAL(triggered()), this, SLOT(ExitApp()));
	connect(ui.aNewGame, SIGNAL(triggered()), this, SLOT(OpenNewGameDialog()));
	connect(ui.aBigBoard, SIGNAL(triggered()), this, SLOT(ChangeToBigBoard()));
	connect(ui.aSmallBoard, SIGNAL(triggered()), this, SLOT(ChangeToSmallBoard()));
	connect(ui.aHintOneStep, SIGNAL(triggered()), this, SLOT(HintOneStep()));

	m_game	= QSudokuGame::getInstance();
	m_scene = QSudokuScene::getInstance();
	m_view	= new QSudokuView(m_scene);
	
	m_scene->setSudokuGame();
	m_game->setSudokuScene();
	setCentralWidget(m_view);

	m_newGame = QNewGameDialog::getInstance();
	m_newGame->hide();
}

QSudoku::~QSudoku()
{

}

QSudoku* QSudoku::getInstance()
{
	if (Instance == NULL)
	{
		Instance = new QSudoku;
	}

	return Instance;
}

void QSudoku::ExitApp()
{
	QApplication::quit();
}

void QSudoku::OpenNewGameDialog()
{
	m_newGame->init();
	m_newGame->show();
}

void QSudoku::newGame(bool manual)
{
	if (manual)
	{
		m_game->newGameManual();
		ui.statusBar->showMessage("[Space] : Draw, [C] : Clear, [Enter] : Confirm");
	}
	else
		m_game->newGameAuto();
}

void QSudoku::ChangeToBigBoard()
{
	ui.aSmallBoard->setChecked(false);
	setFixedWidth(BOARD_SIZE_PIXEL_BIG);
	setFixedHeight(BOARD_SIZE_PIXEL_BIG
		+ ui.menuBar->geometry().height()
		+ ui.mainToolBar->geometry().height()
		+ ui.statusBar->geometry().height());
	m_scene->changeBoardSize(1);
}

void QSudoku::ChangeToSmallBoard()
{
	ui.aBigBoard->setChecked(false);
	setFixedWidth(BOARD_SIZE_PIXEL_SMALL);
	setFixedHeight(BOARD_SIZE_PIXEL_SMALL
		+ ui.menuBar->geometry().height()
		+ ui.mainToolBar->geometry().height()
		+ ui.statusBar->geometry().height());
	m_scene->changeBoardSize(0);
}

void QSudoku::HintOneStep()
{
	m_game->showOneStepHint();
}
