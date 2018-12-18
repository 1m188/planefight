#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "Scene.h"

//开始场景
class StartScene : public Scene
{
	Q_OBJECT

public:
	StartScene(Window *parent);
	~StartScene();

	//初始化场景
	void init() override;

	private slots:
	void newGameButtonClicked(); //单击开始新游戏按钮
};

#endif // STARTSCENE_H
