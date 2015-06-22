#include "QSudokuView.h"

QSudokuView::QSudokuView(QSudokuScene * scene, QWidget * parent) : QGraphicsView(scene, parent), m_scene(scene)
{
	setRenderHints(
		QPainter::Antialiasing
		| QPainter::TextAntialiasing
		| QPainter::SmoothPixmapTransform
		| QPainter::HighQualityAntialiasing
		);
	setOptimizationFlags(
		QGraphicsView::DontClipPainter
		| QGraphicsView::DontAdjustForAntialiasing
		| QGraphicsView::DontSavePainterState
		);
	setCacheMode(QGraphicsView::CacheBackground);
	setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);

	// Appearance
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFrameStyle(QFrame::NoFrame);

	// Background
	setBackgroundBrush(QColor(170, 218, 238));
}

void QSudokuView::resizeEvent(QResizeEvent * event) 
{
	m_scene->resizeScene(event->size().width(), event->size().height());
}

QSudokuView::~QSudokuView()
{

}
