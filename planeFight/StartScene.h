#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "Scene.h"

//��ʼ����
class StartScene : public Scene
{
	Q_OBJECT

public:
	StartScene(Window *parent);
	~StartScene();

	//��ʼ������
	void init() override;
};

#endif // STARTSCENE_H