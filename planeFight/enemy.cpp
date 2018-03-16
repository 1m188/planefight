#include "enemy.h"

Enemy::Enemy(QWidget *parent)
	: Plane(parent)
{

}

Enemy::~Enemy()
{

}

void Enemy::move_()
{
	if (getLife() > 0 && (!getPaused()))
	{
		if (y() <= parentWidget()->height())
		{
			move(x(), y() + 5);
		}
		else
		{
			deleteLater();
		}
	}
}

void Enemy::productBullet()
{
	if (!getPaused() && getLife() > 0)
	{
		EnemyBullet *b = new EnemyBullet(parentWidget());
		b->move(x() + width() / 2, y() + height());
		b->show();
	}
}