#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "QTimer.h"
#include "Player.h"

//游戏场景
class GameScene : public Scene
{
	Q_OBJECT

private:
	//图片
	QPixmap backgroundImage;
	QPixmap againImage;
	QPixmap gameoverImage;

	//玩家
	Player player;

	//帧数
	int fps;

	//游戏循环定时器
	QTimer *gameCycleTimer;

public:
	GameScene(Window *parent);
	~GameScene();

	//初始化游戏场景
	void init() override;

	//重写按键事件
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;

protected:
	//重写绘制事件
	void paintEvent(QPaintEvent *event) override;

	private slots:
	//游戏循环
	void gameCycleSlot();
};

#endif // GAMESCENE_H
