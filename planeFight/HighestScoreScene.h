#ifndef HIGHESTSCORESCENE_H
#define HIGHESTSCORESCENE_H

#include "Scene.h"

class HighestScoreScene : public Scene
{
public:
	HighestScoreScene(Window *parent);
	~HighestScoreScene();

	//初始化场景
	void init() override;

private slots:
	void returnToStartSceneButtonClicked(); //单击返回开始场景按钮
};

#endif // !HIGHESTSCORESCENE_H
