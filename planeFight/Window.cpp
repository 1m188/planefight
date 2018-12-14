#include "Window.h"
#include "Director.h"
#include "GameScene.h"
#include "QApplication"
#include "QDeskTopWidget"
#include "QStyle"

Window::Window()
	: QWidget()
{
	//基本设置
	setAttribute(Qt::WA_DeleteOnClose, true);
	setAttribute(Qt::WA_QuitOnClose, true);

	//获取除任务栏之外的屏幕区域
	QRect screenWithoutTaskBar = QApplication::desktop()->availableGeometry();

	//窗口标题和大小
	setWindowTitle(tr(u8"飞机大战"));
	setFixedSize(900, screenWithoutTaskBar.height() - style()->pixelMetric(QStyle::PM_TitleBarHeight));

	//移动到屏幕中央
	move(screenWithoutTaskBar.width() / 2 - width() / 2, 0);
}

Window::~Window()
{

}

void Window::keyPressEvent(QKeyEvent * event)
{
	Director::getInstance()->getNowScene()->keyPressEvent(event);
}

void Window::keyReleaseEvent(QKeyEvent * event)
{
	Director::getInstance()->getNowScene()->keyReleaseEvent(event);
}

void Window::show()
{
	GameScene *gameScene = new GameScene(this);
	Director::getInstance()->setNowScene(gameScene);
	gameScene->init();
	gameScene->show();
	QWidget::show();
}