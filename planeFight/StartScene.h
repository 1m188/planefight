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
};

#endif // STARTSCENE_H
