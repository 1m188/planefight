#include "scene.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Scene w(nullptr);
	w.show();
	return a.exec();
}
