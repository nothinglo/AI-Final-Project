#include "QSudokuScene.h"
#include "consoleUI.h"

QSudokuScene * QSudokuScene::Instance = NULL;
QSudokuScene::QSudokuScene(QObject *parent)
{
	m_boardSize = BOARD_SIZE_PIXEL_BIG;
	m_cellSize = CELL_SIZE_PIXEL_BIG;
	m_choiceSize = CHOICE_SIZE_PIXEL_BIG;

	setSceneRect(0, 0, m_boardSize, m_boardSize);

	m_elements = new QSudokuElement *[sudokuSize];
	m_boxes = new QGraphicsRectItem[sudokuSize];
	for (int i = 0; i < sudokuSize; i++)
		m_elements[i] = new QSudokuElement[sudokuSize];

	for (int i = 0; i < sudokuSize; i++)
	{
		for (int j = 0; j < sudokuSize; j++)
		{
			QSudokuElement * e = (&m_elements[i][j]);
			e->setPos(m_cellSize * i, m_cellSize * j);
			e->cellSize = m_cellSize;
			e->choiceSize = m_choiceSize;
			e->setX(i);
			e->setY(j);
			addItem(e);

			if ((i + 1) % block_size == 0 && (j + 1) % block_size == 0)
			{
				// Accentuate the boxes with thicker lines.
				static int box_id = -1;
				box_id++;
				m_boxes[box_id].setRect(QRectF(m_cellSize * (i - block_size + 1), m_cellSize * (j - block_size + 1), m_cellSize * block_size, m_cellSize * block_size));
				m_boxes[box_id].setPen(QPen(QColor(36, 156, 206), 2));
				addItem(&m_boxes[box_id]);
			}
		}
	}

	update();
	oneStepHintNow = false;
	isMouseHold = false;
	isPressed = false;
}

QSudokuScene::~QSudokuScene()
{
}

void QSudokuScene::putItemsIntoScene()
{
	int box_id = 0;
	for (int i = 0; i < sudokuSize; i++)
	{
		for (int j = 0; j < sudokuSize; j++)
		{
			QSudokuElement *e = (&m_elements[i][j]);
			e->setPos(m_cellSize * i, m_cellSize * j);
			e->cellSize = m_cellSize;
			e->choiceSize = m_choiceSize;

			if ((i + 1) % block_size == 0 && (j + 1) % block_size == 0)
			{
				// Accentuate the boxes with thicker lines.
				QGraphicsRectItem *r = (&m_boxes[box_id]);
				m_boxes[box_id].setRect(QRectF(m_cellSize * (i - block_size + 1), m_cellSize * (j - block_size + 1), m_cellSize * block_size, m_cellSize * block_size));
				box_id++;
			}
		}
	}

	update();
}

QSudokuScene* QSudokuScene::getInstance()
{
	if (Instance == NULL)
	{
		Instance = new QSudokuScene;
	}

	return Instance;
}

void QSudokuScene::renderBoard(QPainter * painter, const QRectF & target /*= QRectF()*/)
{
	
	render(painter, target, QRect(0, 0, m_boardSize, m_boardSize));
}

void QSudokuScene::resizeScene(int width, int height)
{
	/*double scale;
	if ((double)width / height > 1)
		scale = (double)height / 810;
	else
		scale = (double)width / 810;

	// Store in CPU registry because this will be used to scale *every* item
	// in the scene!    
	register double scaledScale = scale / m_currentScale;

	QGraphicsItem * item;
	foreach(item, this->items()) 
	{
		item->setPos(item->pos() * scaledScale);
		item->setScale(scaledScale);
	}

	m_currentScale = scale;*/
}

void QSudokuScene::updateSudoku(void) 
{
	update(QRect(0, 0, m_boardSize, m_boardSize));
}

void QSudokuScene::updateSudokuElement(int x, int y) 
{
	update(QRect(0, 0, m_boardSize, m_boardSize));
}

void QSudokuScene::moveFocus(int fromX, int fromY, int toX, int toY) 
{
	Q_UNUSED(fromX);
	Q_UNUSED(fromY);

	// TODO: animation?

	toX = (toX < 0) ? sudokuSize - 1 : toX % sudokuSize;
	toY = (toY < 0) ? sudokuSize - 1 : toY % sudokuSize;
	setFocusItem(&m_elements[toX][toY], Qt::PopupFocusReason);
}

void QSudokuScene::setSudokuGame()
{
	m_game = QSudokuGame::getInstance();
}

void QSudokuScene::setAllElements()
{
	for (int x = 0; x < sudokuSize; x++)
	for (int y = 0; y < sudokuSize; y++)
	{
		if (m_game->getBoardValue(x, y) != 0)
		{
			m_elements[x][y].setFinalChoice(m_game->getBoardValue(x, y));
			m_elements[x][y].setGenerated(true);
			m_elements[x][y].setManual(false);
			m_elements[x][y].setToBeGenerated(false);
		}
		else
		{
			m_elements[x][y].unsetFinalChoice();
			m_elements[x][y].setGenerated(false);
			m_elements[x][y].setManual(false);
			m_elements[x][y].setToBeGenerated(false);
		}
			
		m_elements[x][y].setChoices(m_game->getChoices(x, y));

		m_elements[x][y].update();
	}

	isMouseHold = false;

	update();
}

void QSudokuScene::setManualMode()
{
	for (int x = 0; x < sudokuSize; x++)
	for (int y = 0; y < sudokuSize; y++)
	{
		m_elements[x][y].unsetFinalChoice();
		m_elements[x][y].setGenerated(false);
		m_elements[x][y].setManual(true);
		m_elements[x][y].setToBeGenerated(false);
		m_elements[x][y].update();
	}

	isMouseHold = false;

	update();
}

void QSudokuScene::keyPressEvent(QKeyEvent *event)
{
	if (m_elements[0][0].getManual())
	{
		if (event->key() == Qt::Key_Space && !event->isAutoRepeat())
		{
			for (int x = 0; x < sudokuSize; x++)
			for (int y = 0; y < sudokuSize; y++)
			{
				if (m_elements[x][y].getFocused())
					m_elements[x][y].flipToBeGenerated();
			}

			isMouseHold = true;
			isPressed = true;
		}
		if (event->key() == Qt::Key_C && !event->isAutoRepeat())
		{
			for (int x = 0; x < sudokuSize; x++)
			for (int y = 0; y < sudokuSize; y++)
			{
				m_elements[x][y].setToBeGenerated(false);
				m_elements[x][y].update();
			}
		}
		if (event->key() == Qt::Key_Return && !event->isAutoRepeat())
		{
			bool pattern[sudokuSize][sudokuSize];
			for (int x = 0; x < sudokuSize; x++)
			for (int y = 0; y < sudokuSize; y++)
				pattern[y][x] = m_elements[x][y].getToBeGenerated();

			m_game->generateBoardWithConstraint(pattern);
		}
	}
	else if (oneStepHintNow)
	{
		if (event->key() == Qt::Key_Return && !event->isAutoRepeat())
		{
			oneStepHintNow = false;

			for (int x = 0; x < sudokuSize; x++)
			for (int y = 0; y < sudokuSize; y++)
			{
				m_elements[x][y].setHint(false);
				m_elements[x][y].setReason(false);
				m_elements[x][y].update();
			}
		}
	}
}

void QSudokuScene::keyReleaseEvent(QKeyEvent *event)
{
	if (m_elements[0][0].getManual())
	{
		if (event->key() == Qt::Key_Space && !event->isAutoRepeat())
		{
			isMouseHold = false;
			isPressed = false;
		}
	}
}

void QSudokuScene::changeBoardSize(int size)
{
	if (size == 1)
	{
		m_boardSize = BOARD_SIZE_PIXEL_BIG;
		m_cellSize = CELL_SIZE_PIXEL_BIG;
		m_choiceSize = CHOICE_SIZE_PIXEL_BIG;
	}
	else if (size == 0)
	{
		m_boardSize = BOARD_SIZE_PIXEL_SMALL;
		m_cellSize = CELL_SIZE_PIXEL_SMALL;
		m_choiceSize = CHOICE_SIZE_PIXEL_SMALL;
	}
	putItemsIntoScene();
}

void QSudokuScene::setOneStepHint(int x, int y, int num, int type)
{
	if (oneStepHintNow) return;

	oneStepHintNow = true;

	m_elements[y][x].setHint(true);
	m_elements[y][x].setFinalChoice(num);

	if (type == 0)
	{
		for (int i = 0; i < sudokuSize; i++)
		{
			m_elements[i][x].setReason(true);
			m_elements[i][x].update();
		}
	}
	else if (type == 1)
	{
		for (int i = 0; i < sudokuSize; i++)
		{
			m_elements[y][i].setReason(true);
			m_elements[y][i].update();
		}	
	}
	else if (type == 2)
	{
		int blockX = y / block_size;
		int blockY = x / block_size;

		for (int i = 0; i < block_size; i++)
		for (int j = 0; j < block_size; j++)
		{
			m_elements[blockX*block_size + i][blockY*block_size + j].setReason(true);
			m_elements[blockX*block_size + i][blockY*block_size + j].update();
		}
	}
	else if (type == 3)
	{
		m_elements[y][x].update();
	}
}
