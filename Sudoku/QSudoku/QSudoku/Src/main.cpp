#include "QSudoku.h"
#include <QtWidgets/QApplication>
#include <ctime>
int main(int argc, char *argv[])
{
	srand(time(NULL));
	QApplication a(argc, argv);
	QSudoku *w = QSudoku::getInstance();
	w->show();
	return a.exec();
}
