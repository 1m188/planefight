#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "QTimer.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Props.h"
#include "Image.h"

//游戏场景
class GameScene : public Scene
{
	Q_OBJECT

private:
	//图片
	Image *image;

	//玩家
	Player player;
	//玩家子弹数组
	QVector<Bullet> playerBulletVector;
	//敌机数组
	QVector<Enemy> enemyVector;
	//敌机子弹数组
	QVector<Bullet> enemyBulletVector;
	//道具数组
	QVector<Props> propsVector;

	//敌机产生计帧器
	int productEnemyFpsCounter;
	//每隔多少帧产生一架敌机
	int productEnemyFpsInterval;

	//道具产生计帧器
	int productPropsFpsCounter;
	//每隔多少帧产生一个随机道具
	int productPropsFpsInterval;

	//弹药补给计帧器
	int bulletPropsLastFpsCounter;
	//弹药补给道具持续帧数
	int bulletPropsLastFps;

	//当前分数
	int score;

	//帧数
	int fps;

	//是否暂停
	bool isPause;
	//暂停/继续按钮是否被按下
	bool isPauseResumeClicked;
	//暂停/继续按钮的位置
	QRect pauseResumeRect;

	//鼠标一开始按下的时候的坐标
	QPoint originalPoint;

	//游戏是否结束
	bool isGameOver;
	//游戏结束相关的信息按钮的摆放的位置
	QRect gameEndTextRect;
	QRect againRect;
	QRect gameOverRect;

	//游戏循环定时器
	QTimer gameCycleTimer;

	//获取分数
	int getScore(Enemy enemy);

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
	//重写鼠标按下事件
	void mousePressEvent(QMouseEvent *event) override;
	//重写鼠标释放事件
	void mouseReleaseEvent(QMouseEvent *event) override;
	//重写鼠标按住后的移动事件
	void mouseMoveEvent(QMouseEvent *event) override;

private slots:
	//游戏循环
	void gameCycleSlot();
};

#endif // GAMESCENE_H
