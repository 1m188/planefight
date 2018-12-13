#include "GameScene.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GameScene w(nullptr);
	w.show();
	return a.exec();
}
