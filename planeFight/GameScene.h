#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "QTimer.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

//游戏场景
class GameScene : public Scene
{
	Q_OBJECT

private:
	//图片
	QPixmap backgroundImage; //背景图片
	QPixmap againImage;
	QPixmap gameoverImage;

	QVector<QPixmap> playerNormalImageVector; //玩家常态图片
	QVector<QPixmap> playerDestroyImageVector; //玩家损毁图片

	QVector<QPixmap> enemy1NormalImageVector; //敌机1常态图片
	QVector<QPixmap> enemy1DestroyImageVector; //敌机1损毁图片

	QVector<QPixmap> enemy2NormalImageVector; //敌机2常态图片
	QVector<QPixmap> enemy2DestroyImageVector; //敌机2损毁图片

	QVector<QPixmap> enemy3NormalImageVector; //敌机3常态图片
	QVector<QPixmap> enemy3DestroyImageVector; //敌机3损毁图片

	QPixmap playerBulletImage; //玩家子弹图片
	QPixmap enemyBulletImage; //敌机子弹图片

	//玩家
	Player player;
	//玩家子弹数组
	QVector<Bullet> playerBulletVector;
	//敌机数组
	QVector<Enemy> enemyVector;
	//敌机子弹数组
	QVector<Bullet> enemyBulletVector;

	//敌机产生计帧器
	int productEnemyFpsCounter;
	//每隔多少帧产生一架敌机
	int productEnemyFpsInterval;

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
