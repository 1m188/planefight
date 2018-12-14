#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"

//游戏场景
class GameScene : public Scene
{
	Q_OBJECT

private:
	//图片
	QPixmap backgroundImage;
	QPixmap againImage;
	QPixmap gameoverImage;

public:
	GameScene(Window *parent);
	~GameScene();

	void init() override; //初始化游戏场景

	//重写按键事件
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // GAMESCENE_H
