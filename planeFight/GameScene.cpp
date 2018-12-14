#include "GameScene.h"
#include "QApplication"
#include "QTime"
#include "QTimer"
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
	backgroundImg.load(":/planeFight/Resources/background.png");
	againImg.load(":/planeFight/Resources/again.png");
	gameoverImg.load(":/planeFight/Resources/gameover.png");
	gameOverLabel = new QLabel(this);
	againButton = new QPushButton(this);
	gameoverButton = new QPushButton(this);
	enemyChoose = {};
	productEnemyTimer = new QTimer(this);
	isGameOver = false;

	//设置背景
	setAutoFillBackground(true);
	QPalette p = palette();
	p.setBrush(QPalette::Background, QBrush(backgroundImg));
	setPalette(p);

	//设置游戏结束标题和按钮
	gameOverLabel->setAlignment(Qt::AlignCenter);
	gameOverLabel->setFont(QFont(u8"微软雅黑", 20));
	QPalette pa = QPalette();
	pa.setColor(QPalette::WindowText, Qt::blue);
	gameOverLabel->setPalette(pa);
	gameOverLabel->setText(tr(u8"胜败乃兵家常事，少侠请重新来过"));
	gameOverLabel->resize(gameOverLabel->sizeHint());
	gameOverLabel->move(width() / 2 - gameOverLabel->width() / 2, height() / 2 - gameOverLabel->height() / 2 - 200);
	gameOverLabel->hide();

	againButton->setFocusPolicy(Qt::NoFocus);
	againButton->setIcon(QIcon(againImg));
	againButton->setIconSize(againImg.size());
	againButton->setStyleSheet("QPushButton{border:0px}");
	againButton->resize(againButton->iconSize());
	againButton->move(width() / 2 - againButton->width() / 2, gameOverLabel->y() + gameOverLabel->height() + 50);
	againButton->hide();
	connect(againButton, &QPushButton::clicked, this, &GameScene::againButtonClicked);

	gameoverButton->setFocusPolicy(Qt::NoFocus);
	gameoverButton->setIcon(QIcon(gameoverImg));
	gameoverButton->setIconSize(gameoverImg.size());
	gameoverButton->setStyleSheet("QPushButton{border:0px}");
	gameoverButton->resize(gameoverButton->iconSize());
	gameoverButton->move(width() / 2 - gameoverButton->width() / 2, againButton->y() + againButton->height() + 50);
	gameoverButton->hide();
	connect(gameoverButton, &QPushButton::clicked, &QApplication::quit);

	//设置鼠标样式
	setCursor(Qt::BlankCursor);

	//初始化随机数种子
	qsrand(QTime::currentTime().msec());

	//初始化敌机种类选择
	enemyChoose.push_back(reinterpret_cast<Enemy *(GameScene::*)(QWidget *)>(&GameScene::productSolider));
	enemyChoose.push_back(reinterpret_cast<Enemy *(GameScene::*)(QWidget *)>(&GameScene::productLeader));
	enemyChoose.push_back(reinterpret_cast<Enemy *(GameScene::*)(QWidget *)>(&GameScene::productGeneral));

	//初始化玩家
	Player *player = new Player(this);
	connect(player, &Player::planeDestroyed, this, &GameScene::gameOver);
	player->show();

	//产生敌机的定时器
	connect(productEnemyTimer, &QTimer::timeout, this, &GameScene::productEnemy);
	productEnemyTimer->start(1000);
}

void GameScene::productEnemy()
{
	auto solider = (this->*enemyChoose[rand() % (enemyChoose.size())])(this);
}

//哇，，，这个暂停函数写的好恶心啊，，，暂停这种变量本应该做全局的唯一性变量，，，怎么能够让每一
//个继承了Game类的类都有一个啊，，，，
//然而我懒得改了，，，
//先这样烂着吧，以后什么时候找个时间重新写一遍这个飞机大战，，，
void GameScene::keyPressEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Space)
	{
		if (!isGameOver)
		{
			for (QObject *i : children())
			{
				Game *g = dynamic_cast<Game *>(i);
				if (g)
				{
					if (!g->getPaused() && productEnemyTimer->isActive())
					{
						productEnemyTimer->stop();
						setCursor(Qt::ArrowCursor);
					}
					else if (g->getPaused() && !productEnemyTimer->isActive())
					{
						productEnemyTimer->start(1000);
						setCursor(Qt::BlankCursor);
					}
					break;
				}
			}
			for (QObject *i : children())
			{
				Game *j = dynamic_cast<Game *>(i);
				if (j)
				{
					j->setPaused(!j->getPaused());
				}
			}
		}
	}
	QWidget::keyPressEvent(event);
}

void GameScene::gameOver()
{
	keyPressEvent(new QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Space, Qt::KeyboardModifier::NoModifier));
	isGameOver = true;
	gameOverLabel->show();
	gameOverLabel->raise();
	againButton->show();
	againButton->raise();
	gameoverButton->show();
	gameoverButton->raise();
}

//唉，，，，，暂停变量真该做成全局的东西的，，，，
//结果这里写的及其不顺，，，，
//初始化顺序乱七八糟，，，，
void GameScene::againButtonClicked()
{
	//隐藏结束界面
	gameOverLabel->hide();
	againButton->hide();
	gameoverButton->hide();

	//清除所有的Enemy和Bullet类及其派生类对象
	for (QObject *i : children())
	{
		Enemy *e = dynamic_cast<Enemy *>(i);
		if (e)
		{
			e->deleteLater();
		}
		else
		{
			Bullet *b = dynamic_cast<Bullet *>(i);
			if (b)
			{
				b->deleteLater();
			}
		}
	}

	isGameOver = false;

	//取消暂停状态
	keyPressEvent(new QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Space, Qt::KeyboardModifier::NoModifier));

	//初始化玩家
	Player *player = new Player(this);
	connect(player, &Player::planeDestroyed, this, &GameScene::gameOver);
	player->show();
}