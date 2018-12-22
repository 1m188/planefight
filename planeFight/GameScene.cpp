#include "GameScene.h"
#include "Director.h"
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
	//这里把所需的图片提前加载到内存之中，以提高调用的效率
	backgroundImage.load(":/Resources/image/background.png");
	backgroundImage = backgroundImage.scaled(size()); //将背景图片缩放至和窗口一样大，便于绘制

	againImage.load(":/Resources/image/again.png");
	gameOverImage.load(":/Resources/image/gameover.png");

	pauseNorImage.load(":/Resources/image/pause_nor.png");
	pausePressedImage.load(":/Resources/image/pause_pressed.png");
	resumeNorImage.load(":/Resources/image/resume_nor.png");
	resumePressedImage.load(":/Resources/image/resume_pressed.png");
	pauseResumeImage = pauseNorImage;

	playerNormalImageVector.append(QPixmap(":/Resources/image/me1.png"));
	playerNormalImageVector.append(QPixmap(":/Resources/image/me2.png"));
	playerDestroyImageVector.append(QPixmap(":/Resources/image/me_destroy_1.png"));
	playerDestroyImageVector.append(QPixmap(":/Resources/image/me_destroy_2.png"));
	playerDestroyImageVector.append(QPixmap(":/Resources/image/me_destroy_3.png"));
	playerDestroyImageVector.append(QPixmap(":/Resources/image/me_destroy_4.png"));

	enemy1NormalImageVector.append(QPixmap(":/Resources/image/enemy1.png"));
	enemy1DestroyImageVector.append(QPixmap(":/Resources/image/enemy1_down1.png"));
	enemy1DestroyImageVector.append(QPixmap(":/Resources/image/enemy1_down2.png"));
	enemy1DestroyImageVector.append(QPixmap(":/Resources/image/enemy1_down3.png"));
	enemy1DestroyImageVector.append(QPixmap(":/Resources/image/enemy1_down4.png"));

	enemy2NormalImageVector.append(QPixmap(":/Resources/image/enemy2.png"));
	enemy2DestroyImageVector.append(QPixmap(":/Resources/image/enemy2_down1.png"));
	enemy2DestroyImageVector.append(QPixmap(":/Resources/image/enemy2_down2.png"));
	enemy2DestroyImageVector.append(QPixmap(":/Resources/image/enemy2_down3.png"));
	enemy2DestroyImageVector.append(QPixmap(":/Resources/image/enemy2_down4.png"));
	enemy2HitImageVector.append(QPixmap(":/Resources/image/enemy2_hit.png"));

	enemy3NormalImageVector.append(QPixmap(":/Resources/image/enemy3_n1.png"));
	enemy3NormalImageVector.append(QPixmap(":/Resources/image/enemy3_n2.png"));
	enemy3DestroyImageVector.append(QPixmap(":/Resources/image/enemy3_down1.png"));
	enemy3DestroyImageVector.append(QPixmap(":/Resources/image/enemy3_down2.png"));
	enemy3DestroyImageVector.append(QPixmap(":/Resources/image/enemy3_down3.png"));
	enemy3DestroyImageVector.append(QPixmap(":/Resources/image/enemy3_down4.png"));
	enemy3DestroyImageVector.append(QPixmap(":/Resources/image/enemy3_down5.png"));
	enemy3DestroyImageVector.append(QPixmap(":/Resources/image/enemy3_down6.png"));
	enemy3HitImageVector.append(QPixmap(":/Resources/image/enemy3_hit.png"));

	playerBulletImage.load(":/Resources/image/bullet1.png");
	enemyBulletImage.load(":/Resources/image/bullet2.png");

	lifeImage.load(":/Resources/image/life.png");

	bombImage.load(":/Resources/image/bomb.png");
	bombPropsImage.load(":/Resources/image/bomb_supply.png");
	bulletPropsImage.load(":/Resources/image/bullet_supply.png");

	//初始化帧数
	fps = 60;

	//初始化分数
	score = 0;

	//初始化是否暂停标志
	isPause = false;
	//没有被按下
	isPauseResumeClicked = false;
	//暂停/继续按钮位置
	pauseResumeRect.setX(width() - pauseResumeImage.width());
	pauseResumeRect.setY(0);
	pauseResumeRect.setWidth(pauseResumeImage.width());
	pauseResumeRect.setHeight(pauseResumeImage.height());

	//游戏没有结束
	isGameOver = false;
	//初始化游戏结束的信息按钮摆放位置
	gameEndTextRect.setX(0);
	gameEndTextRect.setY(height() / 3);
	gameEndTextRect.setWidth(width());
	gameEndTextRect.setHeight(200);
	againRect.setX(width() / 2 - againImage.width() / 2);
	againRect.setY(gameEndTextRect.y() + gameEndTextRect.height() + 50);
	againRect.setWidth(againImage.width());
	againRect.setHeight(againImage.height());
	gameOverRect.setX(width() / 2 - gameOverImage.width() / 2);
	gameOverRect.setY(againRect.y() + againRect.height() + 50);
	gameOverRect.setWidth(gameOverImage.width());
	gameOverRect.setHeight(gameOverImage.height());

	//初始化玩家飞机
	//设置玩家飞机常态图片
	player.rnormalImageVector() = playerNormalImageVector;
	//设置玩家飞机损毁图片
	player.rdestroyImageVector() = playerDestroyImageVector;
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

	//初始化道具产生
	productPropsFpsCounter = 0;
	productPropsFpsInterval = 1000 / 60 * 1000 / (1000 / fps);

	//初始化弹药补给的持续
	bulletPropsLastFpsCounter = 0;
	bulletPropsLastFps = 1000 / 60 * 700 / (1000 / fps);

	//启动游戏循环
	connect(&gameCycleTimer, &QTimer::timeout, this, &GameScene::gameCycleSlot);
	gameCycleTimer.setInterval(1000 / fps);
	gameCycleTimer.start();
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
		//使用炸弹，全图轰炸
		else if (event->key() == Qt::Key::Key_B)
		{
			if (player.bombNum() > 0)
			{
				player.rbombNum()--;
				for (Enemy &enemy : enemyVector)
				{
					enemy.rlife() = 0;
					//分数更新
					score += getScore(enemy);
				}
			}
		}
	}
	Scene::keyPressEvent(event);
}

void GameScene::mousePressEvent(QMouseEvent * event)
{
	originalPoint = event->pos();
	//当玩家飞机还存活的时候，即游戏还未结束的时候
	if (player.life() > 0)
	{
		//按到了暂停/继续按钮
		if (pauseResumeRect.contains(originalPoint))
		{
			if (isPause)
			{
				pauseResumeImage = resumePressedImage;
			}
			else
			{
				pauseResumeImage = pausePressedImage;
			}
		}
	}
	Scene::mousePressEvent(event);
}

void GameScene::mouseMoveEvent(QMouseEvent * event)
{
	//当玩家飞机还存活的时候，即游戏还未结束的时候
	if (player.life() > 0)
	{
		QPoint pos = event->pos();
		//原来的鼠标按下处为按钮
		if (pauseResumeRect.contains(originalPoint))
		{
			//鼠标移动到了按钮外面
			if (!pauseResumeRect.contains(pos))
			{
				if (isPause)
				{
					pauseResumeImage = resumeNorImage;
				}
				else
				{
					pauseResumeImage = pauseNorImage;
				}
			}
			else
			{
				if (isPause)
				{
					pauseResumeImage = resumePressedImage;
				}
				else
				{
					pauseResumeImage = pausePressedImage;
				}
			}
		}
	}
	Scene::mouseMoveEvent(event);
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
	Scene::keyReleaseEvent(event);
}

void GameScene::mouseReleaseEvent(QMouseEvent * event)
{
	QPoint pos = event->pos();
	//当玩家飞机还存活的时候，即游戏还未结束的时候
	if (player.life() > 0)
	{
		//从暂停/继续按钮处释放且原来鼠标按下的坐标也要为按钮处
		if (pauseResumeRect.contains(pos) && pauseResumeRect.contains(originalPoint))
		{
			if (isPause)
			{
				pauseResumeImage = pauseNorImage;
			}
			else
			{
				pauseResumeImage = resumeNorImage;
			}
			isPause = !isPause;
		}
	}
	//否则当游戏结束的时候
	else if (isGameOver)
	{
		//点击释放都在重新再来按钮则重新再来
		if (againRect.contains(pos) && againRect.contains(originalPoint))
		{
			GameScene *gameScene = new GameScene(Director::getInstance()->getWindow());
			Director::getInstance()->setNowScene(gameScene);
			gameScene->init();
			gameScene->show();
			deleteLater();
		}
		//...结束游戏
		else if (gameOverRect.contains(pos) && gameOverRect.contains(originalPoint))
		{

		}
	}
	Scene::mouseReleaseEvent(event);
}

void GameScene::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);

	//绘制背景
	painter.drawPixmap(frameGeometry(), backgroundImage);

	//绘制玩家
	painter.drawPixmap(player.x(), player.y(), player.width(), player.height(), player.image());

	//绘制敌机
	for (Enemy &enemy : enemyVector)
	{
		painter.drawPixmap(enemy.x(), enemy.y(), enemy.width(), enemy.height(), enemy.image());
	}

	//绘制玩家子弹
	for (Bullet &playerBullet : playerBulletVector)
	{
		painter.drawPixmap(playerBullet.x(), playerBullet.y(), playerBullet.width(), playerBullet.height(), playerBullet.image());
	}

	//绘制敌机子弹
	for (Bullet &enemyBullet : enemyBulletVector)
	{
		painter.drawPixmap(enemyBullet.x(), enemyBullet.y(), enemyBullet.width(), enemyBullet.height(), enemyBullet.image());
	}

	//绘制道具
	for (Props &props : propsVector)
	{
		painter.drawPixmap(props.x(), props.y(), props.width(), props.height(), props.image());
	}

	//绘制暂停/继续按钮
	painter.drawPixmap(pauseResumeRect, pauseResumeImage);

	//绘制生命
	painter.drawPixmap(0, height() - lifeImage.height(), lifeImage.width(), lifeImage.height(), lifeImage);
	painter.setFont(QFont(u8"微软雅黑", 25, QFont::Light));
	painter.drawText(lifeImage.width(), height() - lifeImage.height(), lifeImage.width(), lifeImage.height(), Qt::AlignCenter, QString::number(player.life()));

	//绘制炸弹数目
	painter.drawPixmap(width() - bombImage.width() * 2, height() - bombImage.height(), bombImage.width(), bombImage.height(), bombImage);
	painter.setFont(QFont(u8"微软雅黑", 25, QFont::Light));
	painter.drawText(width() - bombImage.width(), height() - bombImage.height(), bombImage.width(), bombImage.height(), Qt::AlignCenter, QString::number(player.bombNum()));

	//绘制分数
	painter.setFont(QFont(u8"微软雅黑", 15, QFont::Light));
	painter.drawText(0, 0, 120, 50, Qt::AlignCenter, tr(u8"分数：%1").arg(score));

	//游戏结束则绘制相关信息和选择
	if (isGameOver)
	{
		//游戏结束信息
		painter.setFont(QFont(u8"华文行楷", 40));
		painter.drawText(gameEndTextRect, Qt::AlignCenter, tr(u8"胜败乃兵家常事\n大侠请重新来过"));
		//再来一次
		painter.drawPixmap(againRect, againImage);
		//结束游戏
		painter.drawPixmap(gameOverRect, gameOverImage);
	}

	painter.end();
	Scene::paintEvent(event);
}

void GameScene::gameCycleSlot()
{
	//如果没有暂停且游戏没有结束，则计算状态
	if (!isPause && !isGameOver)
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
					PlayerBullet bullet;
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

					//火力加强
					if (player.isStrengthenFire())
					{
						bulletPropsLastFpsCounter++;
						if (bulletPropsLastFpsCounter == bulletPropsLastFps / player.productBulletFpsInterval())
						{
							bulletPropsLastFpsCounter = 0;
							player.risStrengthenFire() = false;
						}

						//初始化玩家子弹
						PlayerBullet bullet1;
						//设置玩家子弹图片
						bullet1.rimage() = playerBulletImage;
						//设置玩家子弹宽高
						bullet1.rwidth() = bullet1.image().width();
						bullet1.rheight() = bullet1.image().height();
						//设置玩家子弹坐标
						bullet1.rx() = player.x() + player.width() / 6;
						bullet1.ry() = player.y() - bullet1.y();
						//设置玩家子弹每帧行进距离
						bullet1.rdy() = 10 * 60 / fps;
						//将玩家子弹压入玩家子弹数组便于管理计算
						playerBulletVector.append(bullet1);

						//初始化玩家子弹
						PlayerBullet bullet2;
						//设置玩家子弹图片
						bullet2.rimage() = playerBulletImage;
						//设置玩家子弹宽高
						bullet2.rwidth() = bullet2.image().width();
						bullet2.rheight() = bullet2.image().height();
						//设置玩家子弹坐标
						bullet2.rx() = player.x() + player.width() - player.width() / 6;
						bullet2.ry() = player.y() - bullet2.y();
						//设置玩家子弹每帧行进距离
						bullet2.rdy() = 10 * 60 / fps;
						//将玩家子弹压入玩家子弹数组便于管理计算
						playerBulletVector.append(bullet2);
					}
				}
			}

			//切换常态图片
			player.changeImage();

			//如果撞上敌机
			for (int i = 0; i < enemyVector.size(); i++)
			{
				Enemy &enemy = enemyVector[i];
				if (player.isCollided(enemy) && enemy.life() > 0)
				{
					player.rlife() = 0;
					enemy.rlife() = 0;
					score += getScore(enemy);
				}
			}

			//如果撞上道具
			for (int i = 0; i < propsVector.size(); i++)
			{
				Props &props = propsVector[i];
				if (player.isCollided(props))
				{
					//如果是炸弹
					if (props.type() == Props::Type::Bomb)
					{
						player.rbombNum()++;
					}
					//如果是弹药补给
					else if (props.type() == Props::Type::Bullet)
					{
						player.risStrengthenFire() = true;
					}
					propsVector.removeAt(i);
				}
			}
		}
		//否则显示损毁过程
		else
		{
			if (!player.changeImage())
			{
				//游戏结束
				isGameOver = true;
			}
		}


		//计算敌机状态
		//敌机产生
		productEnemyFpsCounter++;
		if (productEnemyFpsCounter == productEnemyFpsInterval)
		{
			productEnemyFpsCounter = 0;

			int enemyIndex = qrand() % 13;

			//初始化敌机
			Enemy enemy;
			if (enemyIndex >= 0 & enemyIndex <= 8)
			{
				//设置敌机类型
				enemy.rtype() = Enemy::Type::Soldier;
				//设置敌机的常态图片
				enemy.rnormalImageVector() = enemy1NormalImageVector;
				//设置敌机的损毁图片
				enemy.rdestroyImageVector() = enemy1DestroyImageVector;
				//设置敌机每隔多少帧产生一次子弹
				enemy.rproductBulletFpsInterval() = 1000 / 60 * 50 / (1000 / fps);
				//设置敌机每帧在y方向上的行进距离
				enemy.rdy() = 3 * 60 / fps;
			}
			else if (enemyIndex >= 9 && enemyIndex <= 11)
			{
				//设置敌机类型
				enemy.rtype() = Enemy::Type::Leader;
				//设置敌机的常态图片
				enemy.rnormalImageVector() = enemy2NormalImageVector;
				//设置敌机的损毁图片
				enemy.rdestroyImageVector() = enemy2DestroyImageVector;
				//设置敌机每隔多少帧产生一次子弹
				enemy.rproductBulletFpsInterval() = 1000 / 60 * 45 / (1000 / fps);
				//设置敌机每帧在y方向上的行进距离
				enemy.rdy() = 2 * 60 / fps;
				//设置敌机生命
				enemy.rlife() = 6;
			}
			else if (enemyIndex == 12)
			{
				//设置敌机类型
				enemy.rtype() = Enemy::Type::General;
				//设置敌机的常态图片
				enemy.rnormalImageVector() = enemy3NormalImageVector;
				//设置敌机的损毁图片
				enemy.rdestroyImageVector() = enemy3DestroyImageVector;
				//设置敌机每隔多少帧产生一次子弹
				enemy.rproductBulletFpsInterval() = 1000 / 60 * 40 / (1000 / fps);
				//设置敌机每帧在y方向上的行进距离
				enemy.rdy() = 1 * 60 / fps;
				//设置敌机生命
				enemy.rlife() = 16;
			}
			//设置敌机每隔多少帧切换一张图片
			enemy.rimageChangeFpsInterval() = 1000 / 60 * 13 / (1000 / fps);
			//设置敌机一开始的图片
			enemy.rimage() = enemy.normalImageVector()[0];
			//设置敌机一开始的宽高
			enemy.rwidth() = enemy.image().width();
			enemy.rheight() = enemy.image().height();
			//设置敌机一开始的随机坐标
			enemy.rx() = qrand() % (width() - enemy.width() + 1);
			enemy.ry() = -enemy.height();

			//敌机加入数组
			enemyVector.append(enemy);
		}

		//计算状态
		for (int i = 0; i < enemyVector.size(); i++)
		{
			Enemy &enemy = enemyVector[i];

			//如果敌机活着
			if (enemy.life() > 0)
			{
				//移动
				//超出地图边界则从内存中删除
				if (!enemy.move(height()))
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
					EnemyBullet bullet;
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
				enemy.changImage();
			}
			//否则展示损毁图片，展示完了之后从数组中推出去
			else
			{
				if (!enemy.changImage())
				{
					enemyVector.removeAt(i);
					i--;
					continue;
				}
			}
		}


		//计算子弹状态
		//玩家子弹
		for (int i = 0; i < playerBulletVector.size(); i++)
		{
			PlayerBullet &bullet = playerBulletVector[i];
			//子弹移动
			//超出地图边界则从内存中删除
			if (!bullet.move(0))
			{
				playerBulletVector.removeAt(i);
				i--;
			}
			//否则判断是否撞到了存活敌机
			else
			{
				for (int j = 0; j < enemyVector.size(); j++)
				{
					Enemy &enemy = enemyVector[j];
					//如果撞到了
					if (bullet.isCollided(enemy) && enemy.life() > 0)
					{
						//敌机生命值扣减
						enemy.rlife()--;
						//获取分数
						score += getScore(enemy);
						//切换到损态图片
						if (enemy.life() <= 4 && enemy.normalImageVector()[0].cacheKey() == enemy2NormalImageVector[0].cacheKey())
						{
							enemy.rnormalImageVector() = enemy2HitImageVector;
							enemy.rnowNormalImageIndex() = 0;
						}
						else if (enemy.life() <= 8 && enemy.normalImageVector()[0].cacheKey() == enemy3NormalImageVector[0].cacheKey())
						{
							enemy.rnormalImageVector() = enemy3HitImageVector;
							enemy.rnowNormalImageIndex() = 0;
						}
						//子弹删除
						playerBulletVector.removeAt(i);
						i--;
						break;
					}
				}
			}
		}

		//敌机子弹
		//子弹移动
		for (int i = 0; i < enemyBulletVector.size(); i++)
		{
			EnemyBullet &bullet = enemyBulletVector[i];
			//移动
			//如果子弹超出地图边界
			if (!bullet.move(height()))
			{
				enemyBulletVector.removeAt(i);
				i--;
			}
			//否则判断是否打到了玩家飞机
			else
			{
				if (bullet.isCollided(player) && player.life() > 0)
				{
					player.rlife()--;
					enemyBulletVector.removeAt(i);
					i--;
				}
			}
		}

		//计算道具
		//道具产生
		productPropsFpsCounter++;
		if (productPropsFpsCounter == productPropsFpsInterval)
		{
			productPropsFpsCounter = 0;

			//初始化道具
			Props props;
			//设置类型
			props.rtype() = static_cast<Props::Type>(qrand() % 2 + 1);
			//设置图片
			if (props.type() == Props::Type::Bomb)
			{
				props.rimage() = bombPropsImage;
			}
			else if (props.type() == Props::Type::Bullet)
			{
				props.rimage() = bulletPropsImage;
			}
			//设置宽高
			props.rwidth() = props.image().width();
			props.rheight() = props.image().height();
			//设置坐标
			props.rx() = qrand() % (width() - props.width() + 1);
			props.ry() = -props.height();
			//设置每帧移动距离
			props.rdy() = 3 * 60 / fps;
			//加入数组方便统一管理
			propsVector.append(props);
		}

		//道具移动
		for (int i = 0; i < propsVector.size(); i++)
		{
			Props &props = propsVector[i];
			props.ry() += props.dy();
			if (props.y() >= height())
			{
				propsVector.removeAt(i);
				i--;
			}
		}
	}


	//绘制游戏画面
	update();
}

int GameScene::getScore(Enemy enemy)
{
	return enemy.life() == 0 ? static_cast<int>(enemy.type()) : 0;
}