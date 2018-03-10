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
			move(x(), y() + 10);
		}
		else
		{
			deleteLater();
		}
	}
}

void Enemy::productBullet()
{

}