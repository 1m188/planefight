#include "Window.h"
#include "QApplication"
#include "QDeskTopWidget"

Window::Window()
	: QWidget()
{
	//基本设置
	setAttribute(Qt::WA_DeleteOnClose, true);
	setAttribute(Qt::WA_QuitOnClose, true);

	//窗口标题和大小
	setWindowTitle(tr(u8"飞机大战"));
	setFixedSize(700, 940);

	//移动到屏幕中央
	QRect rect = frameGeometry();
	rect.moveCenter(QApplication::desktop()->availableGeometry().center());
	move(rect.topLeft());
}

Window::~Window()
{

}

void Window::keyPressEvent(QKeyEvent * event)
{
}

void Window::keyReleaseEvent(QKeyEvent * event)
{
}

void Window::show()
{
	QWidget::show();
}