#pragma once

#include <QWidget>

//游戏主窗口
class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    ~Window();

    void show(); //重写原来的show函数，使得show的时候能够出现初始场景

protected:
    //重写按键事件，将发送到窗口的按键事件发送到响应场景中
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};
