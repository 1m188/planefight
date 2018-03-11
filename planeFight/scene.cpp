#include "scene.h"

Scene::Scene(QWidget *parent)
	: QWidget(parent), backgroundImg(QPixmap(":/planeFight/Resources/background.png"))
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

	//敌机种类

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
	EnemySolider *e = new EnemySolider(this);
	qDebug() << children().size();
}