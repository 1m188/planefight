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
			for (QObject *o : parentWidget()->children())
			{
				Player *p = dynamic_cast<Player *>(o);
				if (p)
				{
					if (isCollided(x(), y(), width(), height(), p->x(), p->y(), p->width(), p->height()))
					{
						p->setLife(p->getLife() - 1);
						setLife(getLife() - 1);
						break;
					}
				}
			}
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