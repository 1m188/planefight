#ifndef SCENE_H
#define SCENE_H

#include "Window.h"

//场景类
class Scene : public QWidget
{
	Q_OBJECT

public:
	Scene(Window *parent);
	virtual ~Scene();

	//将按键事件重写到public下，便于游戏窗口调用传递按键事件
	virtual void keyPressEvent(QKeyEvent *event) override;
	virtual void keyReleaseEvent(QKeyEvent *event) override;

	//初始化场景
	virtual void init();
};

#endif // SCENE_H
