#ifndef QSUDOKUELEMENT_H
#define QSUDOKUELEMENT_H

#include <vector>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QKeyEvent>

using namespace std;

const QVector<qreal> DASHLINE_PATTERN = QVector<qreal>() << 1 << 8 << 1 << 8 << 1 << 8 << 1 << 8;
const QColor COLOR_NORMAL			= QColor(170, 218, 238);
const QColor COLOR_FOCUSED			= QColor(223, 243, 252);
const QColor COLOR_TOBEGENERATED	= QColor(45, 145, 219);
const QColor COLOR_REASON			= QColor(255, 184, 104);

class QSudokuElement : public QObject, public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)

public:
	QSudokuElement();
	~QSudokuElement(){}

	QRectF boundingRect() const;
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

	void setChoices(vector<bool> choices);
	bool getFocused(void) const { return m_focus; }
	void setFocused(bool focused) { m_focus = focused; }
	bool getGenerated(void) const { return m_generated; }
	void setGenerated(bool generated) { m_generated = generated; }
	bool getToBeGenerated(void) const { return m_toBeGenerated; }
	void setToBeGenerated(bool tobegenerated) { m_toBeGenerated = tobegenerated; }
	void flipToBeGenerated();
	bool getManual(void) const { return m_manual; }
	void setManual(bool m) { m_manual = m; }
	bool getHint(void) const { return m_hint; }
	void setHint(bool hint) { m_hint = hint; }
	bool getReason(void) const { return m_reason; }
	void setReason(bool reason) { m_reason = reason; }
	int getX(void) const { return m_x; }
	int getY(void) const { return m_y; }
	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }

	void setFinalChoice(int number);
	void unsetFinalChoice(void);

	int cellSize;
	int choiceSize;

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent * event);

	void focusInEvent(QFocusEvent * event);
	void focusOutEvent(QFocusEvent * event);

	void keyPressEvent(QKeyEvent * event);

private:
	void enableChoice(int x, int y, int number);
	void disableChoice(int x, int y, int number);
	void setFinalChoice(int x, int y, int number);
	void unsetFinalChoice(int x, int y);
	void loadHints(int x, int y);
	void selectOtherSudokuElement(int fromX, int fromY, int toX, int toY);

	void enableChoice(int number);
	void disableChoice(int number);

	int getChoiceByMousePos(const QPointF & pos) const;
	QRect getBoundingRectForChoiceByCoords(int x, int y) const;
	QRect getBoundingRectForChoice(int number) const;
	QRect getBoundingRectForFinalChoice(void) const;

	// Values.
	int m_x, m_y;
	vector<bool> *m_choices;
	int m_finalChoice;

	// States.
	bool m_hint;
	bool m_reason;

	bool m_focus;
	bool m_generated;
	bool m_manual;
	bool m_toBeGenerated;
};

#endif