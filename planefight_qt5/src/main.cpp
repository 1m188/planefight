#include <QtWidgets/QApplication>
#include "Director.h"
#include "Window.h"
#include "Image.h"
#include "Config.h"

int main(int argc, char *argv[])
{
    //发布版本
#ifdef RELEASE
    QApplication::addLibraryPath("./plugins");
#endif // RELEASE

    QApplication a(argc, argv);
    Image::getInstance()->init();  //初始化图片
    Config::getInstance()->init(); //初始化游戏数据
    Director::getInstance()->setWindow(new Window());
    Director::getInstance()->getWindow()->show();
    a.exec();
    Config::getInstance()->uninit(); //保存游戏数据
    return 0;
}
