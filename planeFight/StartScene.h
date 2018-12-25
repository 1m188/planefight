#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "Scene.h"

//开始场景
class StartScene :public Scene
{
public:
	StartScene(Window *parent);
	~StartScene();

	//初始化场景
	void init() override;

private slots:
	void newGameButtonClicked(); //单击开始新游戏
	void highestScoreButtonClicked(); //单击最高分按钮
	void settingButtonClicked(); //单击设置按钮
};

#endif // !STARTSCENE_H
