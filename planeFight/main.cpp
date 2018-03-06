#include "scene.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Scene w(nullptr);
	return a.exec();
}
