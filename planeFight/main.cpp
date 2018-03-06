#include "planefight.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	planeFight w;
	w.show();
	return a.exec();
}
