#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "QLabel"
#include "QPushButton"
#include "enemysolider.h"
#include "enemyleader.h"
#include "enemygeneral.h"

//游戏场景
class GameScene : public Scene
{
	Q_OBJECT

private:
	//图片
	QPixmap backgroundImg;
	QPixmap againImg;
	QPixmap gameoverImg;

	//游戏结束的信息标签和功能button
	QLabel *gameOverLabel;
	QPushButton *againButton;
	QPushButton *gameoverButton;

	//敌机选择数组
	QVector<Enemy *(GameScene::*)(QWidget *)> enemyChoose;

	//制造敌机的timer
	QTimer *productEnemyTimer;

	//游戏是否结束
	bool isGameOver;

	//三个敌机选择函数
	EnemySolider *productSolider(QWidget *parent) { return new EnemySolider(parent); }
	EnemyLeader *productLeader(QWidget *parent) { return new EnemyLeader(parent); }
	EnemyGeneral *productGeneral(QWidget *parent) { return new EnemyGeneral(parent); }

public:
	GameScene(Window *parent);
	~GameScene();

	void init() override; //初始化游戏场景
	void keyPressEvent(QKeyEvent *event) override; //重写按键事件

	private slots:
	//制造敌机
	void productEnemy();
	//游戏结束
	void gameOver();
	//单击重新开始按钮
	void againButtonClicked();
};

#endif // GAMESCENE_H
