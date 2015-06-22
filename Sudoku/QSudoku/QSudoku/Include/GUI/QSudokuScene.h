#ifndef QSUDOKUSCENE_H
#define QSUDOKUSCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "QSudokuGame.h"
#include "QSudokuElement.h"

class QSudokuGame;

const int BOARD_SIZE_PIXEL_BIG		= 720;
const int BOARD_SIZE_PIXEL_SMALL	= 540;
const int CELL_SIZE_PIXEL_BIG		= 80;
const int CELL_SIZE_PIXEL_SMALL		= 60;
const int CHOICE_SIZE_PIXEL_BIG		= 20;
const int CHOICE_SIZE_PIXEL_SMALL	= 15;

class QSudokuScene : public QGraphicsScene
{
	Q_OBJECT

public:
	QSudokuScene(QObject *parent = 0);
	~QSudokuScene();

	void renderBoard(QPainter * painter, const QRectF & target = QRectF());
	void updateSudoku(void);
	void updateSudokuElement(int x, int y);

	// Qt-related methods.
	void resizeScene(int width, int height);
	void setSudokuGame();
	void setAllElements();
	void setManualMode();
	void setOneStepHint(int x, int y, int num, int type);

	void changeBoardSize(int size);
	void putItemsIntoScene();

	static QSudokuScene* getInstance();
	static QSudokuScene *Instance;

	bool isMouseHold;
	bool isPressed;

	bool oneStepHintNow;

	int m_boardSize;
	int m_cellSize;
	int m_choiceSize;

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

private:
	void moveFocus(int fromX, int fromY, int toX, int toY);

signals:
	void moveFinished(void);
	void gameIsActive(bool active);

private:
	double m_currentScale;
	QSudokuGame *m_game;
	QGraphicsRectItem *m_boxes;
	QSudokuElement ** m_elements;
};

#endif