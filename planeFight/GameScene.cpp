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

	//初始化玩家
	player.rimage().load(":/Resources/image/me1.png");
	player.rwidth() = player.image().width();
	player.rheight() = player.image().height();
	player.rx() = width() / 2 - player.width() / 2;
	player.ry() = height() - player.height();
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
	//玩家移动
	player.move(0, height(), 0, width());

	//绘制游戏画面
	update();
}