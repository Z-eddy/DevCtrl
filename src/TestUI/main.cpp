#include "TestUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TestUI w;
	w.show();
	return a.exec();
}
