#include "GameScene.h"
#include "QPainter"
#include "QKeyEvent"
#include "QTime"

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
	playerBulletImage.load(":/Resources/image/bullet1.png");
	enemyBulletImage.load(":/Resources/image/bullet2.png");

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
	player.rimageChangeFpsInterval() = 1000 / 60 * 13 / (1000 / fps);
	//设置每隔多少帧产生一次子弹
	player.rproductBulletFpsInterval() = 1000 / 60 * 13 / (1000 / fps);
	//设置玩家飞机一开始的图片
	player.rimage() = player.normalImageVector()[0];
	//设置玩家飞机宽高
	player.rwidth() = player.image().width();
	player.rheight() = player.image().height();
	//设置玩家飞机初始坐标
	player.rx() = width() / 2 - player.width() / 2;
	player.ry() = height() - player.height();
	//设置玩家飞机每帧在两个方向上行进距离
	player.rdx() = 10 * 60 / fps;
	player.rdy() = 10 * 60 / fps;

	//初始化敌机产生
	productEnemyFpsCounter = 0;
	productEnemyFpsInterval = 1000 / 60 * 100 / (1000 / fps);
	srand(QTime::currentTime().msec()); //初始化随机种子

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
		//玩家飞机移动
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
		//开火
		else if (event->key() == Qt::Key::Key_J)
		{
			player.risFiring() = true;
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
		else if (event->key() == Qt::Key::Key_J)
		{
			player.risFiring() = false;
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

	//绘制敌机
	for (Enemy &enemy : enemyVector)
	{
		painter->drawPixmap(enemy.x(), enemy.y(), enemy.width(), enemy.height(), enemy.image());
	}

	//绘制玩家子弹
	for (Bullet &playerBullet : playerBulletVector)
	{
		painter->drawPixmap(playerBullet.x(), playerBullet.y(), playerBullet.width(), playerBullet.height(), playerBullet.image());
	}

	//绘制敌机子弹
	for (Bullet &enemyBullet : enemyBulletVector)
	{
		painter->drawPixmap(enemyBullet.x(), enemyBullet.y(), enemyBullet.width(), enemyBullet.height(), enemyBullet.image());
	}

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

		//开火
		player.rproductBulletFpsCounter()++;
		if (player.productBulletFpsCounter() == player.productBulletFpsInterval())
		{
			player.rproductBulletFpsCounter() = 0;
			if (player.isFiring())
			{
				//初始化玩家子弹
				Bullet bullet;
				//设置玩家子弹图片
				bullet.rimage() = playerBulletImage;
				//设置玩家子弹宽高
				bullet.rwidth() = bullet.image().width();
				bullet.rheight() = bullet.image().height();
				//设置玩家子弹坐标
				bullet.rx() = player.x() + player.width() / 2 - bullet.width() / 2;
				bullet.ry() = player.y() - bullet.y();
				//设置玩家子弹每帧行进距离
				bullet.rdy() = 10 * 60 / fps;
				//将玩家子弹压入玩家子弹数组便于管理计算
				playerBulletVector.append(bullet);
			}
		}

		//切换常态图片
		player.rnormalImageChangeFpsCounter()++;
		if (player.normalImageChangeFpsCounter() == player.imageChangeFpsInterval())
		{
			player.rnormalImageChangeFpsCounter() = 0;
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
		player.rdestroyImageChangeFpsCounter()++;
		if (player.destroyImageChangeFpsCounter() == player.imageChangeFpsInterval())
		{
			player.rdestroyImageChangeFpsCounter() = 0;
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


	//计算敌机状态
	//敌机产生
	productEnemyFpsCounter++;
	if (productEnemyFpsCounter == productEnemyFpsInterval)
	{
		productEnemyFpsCounter = 0;

		//初始化敌机
		Enemy enemy1;
		//设置敌机的常态图片
		enemy1.rnormalImageVector().append(QPixmap(":/Resources/image/enemy1.png"));
		//设置敌机的损毁图片
		enemy1.rdestroyImageVector().append(QPixmap(":/Resources/image/enemy1_down1.png"));
		enemy1.rdestroyImageVector().append(QPixmap(":/Resources/image/enemy1_down2.png"));
		enemy1.rdestroyImageVector().append(QPixmap(":/Resources/image/enemy1_down3.png"));
		enemy1.rdestroyImageVector().append(QPixmap(":/Resources/image/enemy1_down4.png"));
		//设置敌机每隔多少帧切换一张图片
		enemy1.rimageChangeFpsInterval() = 1000 / 60 * 13 / (1000 / fps);
		//设置敌机每隔多少帧产生一次子弹
		enemy1.rproductBulletFpsInterval() = 1000 / 60 * 50 / (1000 / fps);
		//设置敌机一开始的图片
		enemy1.rimage() = enemy1.normalImageVector()[0];
		//设置敌机一开始的宽高
		enemy1.rwidth() = enemy1.image().width();
		enemy1.rheight() = enemy1.image().height();
		//设置敌机一开始的随机坐标
		enemy1.rx() = qrand() % (width() - enemy1.width() + 1);
		enemy1.ry() = -enemy1.height();
		//设置敌机每帧在y方向上的行进距离
		enemy1.rdy() = 3 * 60 / fps;

		//敌机加入数组
		enemyVector.append(enemy1);
	}

	//计算状态
	for (int i = 0; i < enemyVector.size(); i++)
	{
		Enemy &enemy = enemyVector[i];

		//如果敌机活着
		if (enemy.life() > 0)
		{
			//移动
			enemy.ry() += enemy.dy();
			//超出地图边界则从内存中删除
			if (enemy.y() >= height())
			{
				enemyVector.removeAt(i);
				i--;
				continue;
			}

			//开火
			enemy.rproductBulletFpsCounter()++;
			if (enemy.productBulletFpsCounter() == enemy.productBulletFpsInterval())
			{
				enemy.rproductBulletFpsCounter() = 0;

				//初始化敌机子弹
				Bullet bullet;
				//设置敌机子弹图片
				bullet.rimage() = enemyBulletImage;
				//设置敌机子弹宽高
				bullet.rwidth() = bullet.image().width();
				bullet.rheight() = bullet.image().height();
				//设置敌机子弹坐标
				bullet.rx() = enemy.x() + enemy.width() / 2 - bullet.width() / 2;
				bullet.ry() = enemy.y() + enemy.height();
				//设置敌机子弹每帧的行进距离
				bullet.rdy() = 5 * 60 / fps;
				//压入敌机子弹数组
				enemyBulletVector.append(bullet);
			}

			//切换常态图片
			enemy.rnormalImageChangeFpsCounter()++;
			if (enemy.normalImageChangeFpsCounter() == enemy.imageChangeFpsInterval())
			{
				enemy.rnormalImageChangeFpsCounter() = 0;
				enemy.rimage() = enemy.normalImageVector()[enemy.nowNormalImageIndex()];
				enemy.rnowNormalImageIndex()++;
				if (enemy.nowNormalImageIndex() >= enemy.normalImageVector().size())
				{
					enemy.rnowNormalImageIndex() = 0;
				}
			}
		}
		//否则展示损毁图片，展示完了之后从数组中推出去
		else
		{
			enemy.rdestroyImageChangeFpsCounter()++;
			if (enemy.destroyImageChangeFpsCounter() == enemy.imageChangeFpsInterval())
			{
				enemy.rdestroyImageChangeFpsCounter() = 0;
				enemy.rimage() = enemy.destroyImageVector()[enemy.nowDestroyImageIndex()];
				enemy.rnowDestroyImageIndex()++;
				if (enemy.nowDestroyImageIndex() >= enemy.destroyImageVector().size())
				{
					enemyVector.removeAt(i);
					i--;
					continue;
				}
			}
		}
	}


	//计算子弹状态
	//玩家子弹
	//子弹移动
	for (int i = 0; i < playerBulletVector.size(); i++)
	{
		Bullet &bullet = playerBulletVector[i];
		bullet.ry() -= bullet.dy();
		//超出地图边界则从内存中删除
		if (bullet.y() + bullet.height() <= 0)
		{
			playerBulletVector.removeAt(i);
			i--;
		}
	}

	//敌机子弹
	//子弹移动
	for (int i = 0; i < enemyBulletVector.size(); i++)
	{
		Bullet &bullet = enemyBulletVector[i];
		bullet.ry() += bullet.dy();
		if (bullet.y() + bullet.height() <= 0)
		{
			enemyBulletVector.removeAt(i);
			i--;
		}
	}


	//绘制游戏画面
	update();
}