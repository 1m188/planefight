#include "scene.h"

Scene::Scene(QWidget *parent)
	: QWidget(parent), backgroundImg(QPixmap(":/planeFight/Resources/background.png")), enemyChoose(QVector<Enemy *(Scene::*)(QWidget *)>{})
{
	setWindowTitle(tr(u8"飞机大战"));
	setFixedSize(700, 940);
	QRect rect = frameGeometry();
	rect.moveCenter(QApplication::desktop()->availableGeometry().center());
	move(rect.topLeft());
	//设置背景
	QPalette p = palette();
	p.setBrush(QPalette::Background, QBrush(backgroundImg));
	setPalette(p);
	//设置鼠标样式
	setCursor(Qt::BlankCursor);

	//初始化随机数种子
	qsrand(QTime::currentTime().msec());

	//初始化敌机种类选择
	enemyChoose.push_back(reinterpret_cast<Enemy *(Scene::*)(QWidget *)>(&Scene::productSolider));
	enemyChoose.push_back(reinterpret_cast<Enemy *(Scene::*)(QWidget *)>(&Scene::productLeader));
	enemyChoose.push_back(reinterpret_cast<Enemy *(Scene::*)(QWidget *)>(&Scene::productGeneral));

	//初始化玩家
	Player *player = new Player(this);

	//产生敌机的定时器
	QTimer *productEnemyTimer = new QTimer(this);
	connect(productEnemyTimer, &QTimer::timeout, this, &Scene::productEnemy);
	productEnemyTimer->start(1000);

	show();
}

Scene::~Scene()
{

}

void Scene::productEnemy()
{
	auto solider = (this->*enemyChoose[rand() % (enemyChoose.size())])(this);
}