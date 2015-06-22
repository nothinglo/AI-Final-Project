#ifndef QSUDOKUVIEW_H
#define QSUDOKUVIEW_H

#include <QGraphicsView>
#include "QSudokuScene.h"

class QSudokuView : public QGraphicsView
{
	Q_OBJECT

public:
	QSudokuView(QSudokuScene * scene, QWidget * parent = 0);
	~QSudokuView();

private:
	virtual void resizeEvent(QResizeEvent * event);

	QSudokuScene * m_scene;
};

#endif