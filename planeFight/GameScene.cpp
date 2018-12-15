#include "GameScene.h"
#include "QPainter"
#include "QKeyEvent"

GameScene::GameScene(Window *parent)
	: Scene(parent)
{

}

GameScene::~GameScene()
{

}

void GameScene::init()
{
	//初始化游戏元素
	backgroundImage.load(":/Resources/image/background.png");
	backgroundImage = backgroundImage.scaled(size()); //将背景图片缩放至和窗口一样大，便于绘制
	againImage.load(":/Resources/image/again.png");
	gameoverImage.load(":/Resources/image/gameover.png");

	//初始化帧数
	fps = 60;

	//初始化玩家飞机
	//设置玩家飞机常态图片
	player.rnormalImageVector().append(QPixmap(":/Resources/image/me1.png"));
	player.rnormalImageVector().append(QPixmap(":/Resources/image/me2.png"));
	//设置玩家飞机损毁图片
	player.rdestroyImageVector().append(QPixmap(":/Resources/image/me_destroy_1.png"));
	player.rdestroyImageVector().append(QPixmap(":/Resources/image/me_destroy_2.png"));
	player.rdestroyImageVector().append(QPixmap(":/Resources/image/me_destroy_3.png"));
	player.rdestroyImageVector().append(QPixmap(":/Resources/image/me_destroy_4.png"));
	//设置每隔多少帧切换一张玩家飞机图片
	player.rimageChangeFps() = 1000 / 60 * 13 / (1000 / fps);
	//设置玩家飞机一开始的图片
	player.rimage() = player.normalImageVector()[0];
	//设置玩家飞机宽高
	player.rwidth() = player.image().width();
	player.rheight() = player.image().height();
	//设置玩家飞机初始坐标
	player.rx() = width() / 2 - player.width() / 2;
	player.ry() = height() - player.height();
	//设置玩家飞机每帧在两个方向上行进距离
	player.rdx() = 20 * 30 / fps;
	player.rdy() = 20 * 30 / fps;

	//启动游戏循环
	gameCycleTimer = new QTimer(this);
	connect(gameCycleTimer, &QTimer::timeout, this, &GameScene::gameCycleSlot);
	gameCycleTimer->setInterval(1000 / fps);
	gameCycleTimer->start();
}

void GameScene::keyPressEvent(QKeyEvent * event)
{
	if (!event->isAutoRepeat())
	{
		if (event->key() == Qt::Key::Key_W)
		{
			player.risUping() = true;
		}
		else if (event->key() == Qt::Key::Key_S)
		{
			player.risDowning() = true;
		}
		else if (event->key() == Qt::Key::Key_A)
		{
			player.risLefting() = true;
		}
		else if (event->key() == Qt::Key::Key_D)
		{
			player.risRighting() = true;
		}
	}
	QWidget::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent * event)
{
	if (!event->isAutoRepeat())
	{
		if (event->key() == Qt::Key::Key_W)
		{
			player.risUping() = false;
		}
		else if (event->key() == Qt::Key::Key_S)
		{
			player.risDowning() = false;
		}
		else if (event->key() == Qt::Key::Key_A)
		{
			player.risLefting() = false;
		}
		else if (event->key() == Qt::Key::Key_D)
		{
			player.risRighting() = false;
		}
	}
	QWidget::keyReleaseEvent(event);
}

void GameScene::paintEvent(QPaintEvent * event)
{
	QPainter *painter = new QPainter(this);

	//绘制背景
	painter->drawPixmap(frameGeometry(), backgroundImage);

	//绘制玩家
	painter->drawPixmap(player.x(), player.y(), player.width(), player.height(), player.image());

	painter->end();
	QWidget::paintEvent(event);
}

void GameScene::gameCycleSlot()
{
	//计算状态
	//计算玩家状态
	//如果玩家存活
	if (player.life() > 0)
	{
		//移动
		player.move(0, height(), 0, width());

		//切换常态图片
		player.rfpsCounter()++;
		if (player.fpsCounter() == player.imageChangeFps())
		{
			player.rfpsCounter() = 0;
			player.rimage() = player.normalImageVector()[player.nowNormalImageIndex()];
			player.rnowNormalImageIndex()++;
			//倘若一轮图片显示完了之后，继续显示下一轮图片
			if (player.nowNormalImageIndex() >= player.normalImageVector().size())
			{
				player.rnowNormalImageIndex() = 0;
			}
		}
	}
	//否则显示损毁过程
	else
	{
		//切换损毁图片
		player.rfpsCounter()++;
		if (player.fpsCounter() == player.imageChangeFps())
		{
			player.rfpsCounter() = 0;
			player.rimage() = player.destroyImageVector()[player.nowDestroyImageIndex()];
			player.rnowDestroyImageIndex()++;
			//倘若一轮图片显示完了之后，停止游戏画面更新，进入游戏结束阶段
			if (player.nowDestroyImageIndex() >= player.destroyImageVector().size())
			{
				gameCycleTimer->stop();

				//游戏结束
			}
		}
	}

	//绘制游戏画面
	update();
}