#include "enemybullet.h"

EnemyBullet::EnemyBullet(QWidget *parent)
	: Bullet(parent)
{
	setPixmap(QPixmap(":/planeFight/Resources/bullet2.png"));
	setFixedSize(pixmap()->size());
}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::move_()
{
	if (!getPaused())
	{
		if (y() <= parentWidget()->height())
		{
			move(x(), y() + 10);
			for (QObject *i : parentWidget()->children())
			{
				Player *j = dynamic_cast<Player *>(i);
				if (j)
				{
					if (isCollided(x(), y(), width(), height(), j->x(), j->y(), j->width(), j->height()))
					{
						j->setLife(j->getLife() - 1);
						deleteLater();
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