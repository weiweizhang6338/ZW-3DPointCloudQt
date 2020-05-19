#include "QvtkTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QvtkTest w;
	w.show();
	return a.exec();
}
