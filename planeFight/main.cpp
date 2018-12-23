#include <QtWidgets/QApplication>
#include "Director.h"
#include "Window.h"
#include "Image.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Image::getInstance()->init(); //初始化图片
	Director::getInstance()->setWindow(new Window());
	Director::getInstance()->getWindow()->show();
	return a.exec();
}
