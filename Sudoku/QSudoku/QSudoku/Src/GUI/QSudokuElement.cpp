#include "QSudokuElement.h"
#include "QSudokuGame.h"
#include "QSudokuScene.h"
#include "globalVar.h"

QSudokuElement::QSudokuElement() :
m_x(-1),
m_y(-1),
m_finalChoice(-1),
m_focus(false),
m_generated(false),
m_manual(false),
m_toBeGenerated(false),
m_hint(false),
m_reason(false),
cellSize(CELL_SIZE_PIXEL_BIG),
choiceSize(CHOICE_SIZE_PIXEL_BIG)
{
	m_choices = new vector<bool>(sudokuSize, false);

	setAcceptHoverEvents(true);
	setFlag(QGraphicsItem::ItemIsFocusable);
}

QRectF QSudokuElement::boundingRect() const
{
	return QRectF(0, 0, cellSize, cellSize);
}

void QSudokuElement::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	Q_UNUSED(widget);

	// Set the background color
	QColor finalColor;
	finalColor = (m_toBeGenerated) ? COLOR_TOBEGENERATED : COLOR_NORMAL;
	if (m_reason) finalColor = COLOR_REASON;
	if (m_focus)  finalColor = COLOR_FOCUSED;
	painter->setBrush(finalColor);

	// Draw the box.
	QPen pen(QColor(207,245,245));
	pen.setWidth(2);
	pen.setDashPattern(DASHLINE_PATTERN);
	pen.setStyle(Qt::CustomDashLine);
	painter->setPen(pen);
	painter->drawRect(0, 0, cellSize, cellSize);

	// If we are now in "drawing" mode, the choices don't need to be shown
	if (m_manual) return;

	// If no final choice is made, then draw the 9 choices inside the box.
	// Otherwise, we draw the final choice at an item-filling size.
	if (m_finalChoice == -1) 
	{
		for (int number = 1; number <= sudokuSize; number++) 
		{
			bool chosen = (*m_choices)[number - 1];

			// We draw the number if it's either chosen or if the user is hovering over this item.
			if (!m_reason && (chosen || m_focus)) 
			{ 
				painter->setPen(QPen((chosen) ? QColor(3, 73, 104) : QColor(87, 106, 114), 0));

				// When chosen: bold font.
				QFont font = QFont("Consolas", 0.1875 * cellSize, QFont::Normal, true);
				font.setBold(chosen);
				painter->setFont(font);

				// Draw!
				painter->drawText(
					getBoundingRectForChoice(number),
					Qt::AlignCenter | Qt::AlignVCenter,
					QString::number(number)
					);
			}
		}
	}
	else 
	{
		// Font.
		QFont font = QFont("Consolas", 0.5 * cellSize, QFont::Normal, false);
		font.setBold(true);
		painter->setFont(font);

		// Pen.
		QColor finalColor = (m_generated) ? Qt::black : QColor(56, 165, 211);
		if (m_hint) finalColor = QColor(255, 0, 0);
		painter->setPen(QPen(finalColor, 1));

		painter->drawText(
			getBoundingRectForFinalChoice(),
			Qt::AlignCenter | Qt::AlignVCenter,
			QString::number(m_finalChoice)
			);
	}
}

void QSudokuElement::setChoices(vector<bool> choices)
{
	for (int i = 0; i < sudokuSize; i++)
		(*m_choices)[i] = choices[i];

	update();
}

void QSudokuElement::enableChoice(int number) 
{
	(*m_choices)[number - 1] = true;
}

void QSudokuElement::disableChoice(int number) 
{
	(*m_choices)[number - 1] = false;
}

void QSudokuElement::setFinalChoice(int number) 
{
	m_finalChoice = number;
	QSudokuGame::getInstance()->setFinalChoice(m_x, m_y, number);
}

void QSudokuElement::unsetFinalChoice(void) 
{
	m_finalChoice = -1;
	QSudokuGame::getInstance()->unsetFinalChoice(m_x, m_y);
}

void QSudokuElement::hoverEnterEvent(QGraphicsSceneHoverEvent * event) 
{
	Q_UNUSED(event);
	setFocus(Qt::OtherFocusReason);
}

void QSudokuElement::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) 
{
	Q_UNUSED(event);
	clearFocus();
}

void QSudokuElement::mousePressEvent(QGraphicsSceneMouseEvent * event) 
{
	if (m_generated || m_reason) // This is a generated element, so ignore this event.
		return;

	if (m_finalChoice != -1)
		return;
	
	int number = getChoiceByMousePos(event->lastScenePos());
	if (number > 0) {
		// Send out signals to allow for responding events.
		if (!(*m_choices)[number - 1])
			enableChoice(number);
		else
			disableChoice(number);

		update();
	}
}

void QSudokuElement::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) 
{
	if (m_generated || m_reason) // This is a generated element, so ignore this event.
		return;

	// If there's no final choice set yet, allow this double click to set it.
	if (m_finalChoice == -1) {
		int number = getChoiceByMousePos(event->lastScenePos());
		if (number > 0)
		{
			setFinalChoice(number);
			update();
		}
	}
	// Otherwise, if a final choice is set, allow this double click to unset
	// it.
	else if (QRectF(getBoundingRectForFinalChoice()).contains(mapFromScene(event->lastScenePos())))
	{
		unsetFinalChoice();
		update();
	}
}

void QSudokuElement::contextMenuEvent(QGraphicsSceneContextMenuEvent * event) 
{
	Q_UNUSED(event);
}

void QSudokuElement::focusInEvent(QFocusEvent * event) {
	Q_UNUSED(event);

	m_focus = true;
	if (m_manual && QSudokuScene::getInstance()->isMouseHold)
	{
		m_toBeGenerated = !m_toBeGenerated;
	}
	update();
}

/**
* Override of focusOutEvent().
*/
void QSudokuElement::focusOutEvent(QFocusEvent * event) {
	Q_UNUSED(event);

	m_focus = false;
	update();
}

/**
* Override of keyPressEvent().
*/
void QSudokuElement::keyPressEvent(QKeyEvent * event) {
	/* Selection movement.
	switch (event->key()) {
	case Qt::Key_Left: // Left arrow.
		selectOtherSudokuElement(m_x, m_y, m_x - 1, m_y);
		break;
	case Qt::Key_Up: // Top arrow.
		selectOtherSudokuElement(m_x, m_y, m_x, m_y - 1);
		break;
	case Qt::Key_Right: // Right arrow.
		selectOtherSudokuElement(m_x, m_y, m_x + 1, m_y);
		break;
	case Qt::Key_Down: // Bottom arrow.
		selectOtherSudokuElement(m_x, m_y, m_x, m_y + 1);
		break;
	}

	// This is a generated element, so only allow keyboard navigation.
	if (m_generated)
		return;

	// Final choices and choices.
	if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_9) 
	{
		int number = event->key() - Qt::Key_0;

		if (event->modifiers() != Qt::ControlModifier) // Final choice.
		if (number != m_finalChoice)
			setFinalChoice(m_x, m_y, number);
		else
			unsetFinalChoice(m_x, m_y);
		else // Choice.
		if (!(*m_choices)[number - 1])
			enableChoice(m_x, m_y, number);
		else
			disableChoice(m_x, m_y, number);
	}

	// Unset a final choice.
	if (event->key() == Qt::Key_Backspace)
		unsetFinalChoice(m_x, m_y);

	if (event->key() == Qt::Key_H)
		loadHints(m_x, m_y);*/
}

int QSudokuElement::getChoiceByMousePos(const QPointF & scenePos) const 
{
	QPointF itemPos = mapFromScene(scenePos);

	for (int number = 1; number <= 9; number++)
		// NOTE: if it turns out to be hard for the user to click the number,
		// we can always upscale the bounding rectangle for the number,
		// allowing him to click just beside it.
	if (QRectF(getBoundingRectForChoice(number)).contains(itemPos))
		return number;

	return 0;
}

QRect QSudokuElement::getBoundingRectForChoiceByCoords(int x, int y) const 
{
	if (x < 0 || x > block_size - 1 || y < 0 || y > block_size - 1)
		qFatal("SudokuElement::getBoundingRectForChoiceByCoords(): x or y was not in the valid range (0-2). x: %d, y: %d.", x, y);

	int offset = (cellSize - (block_size * choiceSize)) / 4;
	int nextNumberOffset = offset + choiceSize;

	return QRect(
		offset + x * nextNumberOffset,
		offset + y * nextNumberOffset,
		choiceSize,
		choiceSize
		);
}

QRect QSudokuElement::getBoundingRectForChoice(int number) const 
{
	if (number < 1 || number > 9)
		qFatal("SudokuElement::getboundingRectForChoice(): number was not in the valid range (1-9). number: %d.", number);

	for (int y = 0; y < block_size; y++)
	for (int x = 0; x < block_size; x++)
	if (--number == 0)
		return getBoundingRectForChoiceByCoords(x, y);

	// This should never be reached!
	qFatal("The number %d could not be found!", number);
	return QRect();
}

QRect QSudokuElement::getBoundingRectForFinalChoice(void) const 
{
	return QRect(ceil(0.1 * cellSize), ceil(0.1 * cellSize), ceil(0.8 * cellSize), ceil(0.8 * cellSize));
}

void QSudokuElement::flipToBeGenerated()
{
	if (m_manual)
	{
		m_toBeGenerated = !m_toBeGenerated;
	}
}
