#include "enemysolider.h"

EnemySolider::EnemySolider(QWidget *parent)
	: Enemy(parent)
{
	addImg(QPixmap(":/planeFight/Resources/enemy1.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/enemy1_down1.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/enemy1_down2.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/enemy1_down3.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/enemy1_down4.png"));

	resize(QPixmap(":/planeFight/Resources/enemy1.png").size());
	int x = qrand() % (parentWidget()->width() - width());
	move(x, -height());

	show();
}

EnemySolider::~EnemySolider()
{

}
