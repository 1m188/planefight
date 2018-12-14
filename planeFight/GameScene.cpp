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

	//产生敌机的定时器
	connect(productEnemyTimer, &QTimer::timeout, this, &GameScene::productEnemy);
	productEnemyTimer->start(1000);
}

void GameScene::productEnemy()
{
	
}

void GameScene::keyPressEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Space)
	{
		if (!isGameOver)
		{
			for (QObject *i : children())
			{
			}
			for (QObject *i : children())
			{
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

void GameScene::againButtonClicked()
{
	//隐藏结束界面
	gameOverLabel->hide();
	againButton->hide();
	gameoverButton->hide();

	//清除所有的Enemy和Bullet类及其派生类对象
	for (QObject *i : children())
	{
	}

	isGameOver = false;

	//取消暂停状态
	keyPressEvent(new QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Space, Qt::KeyboardModifier::NoModifier));
}