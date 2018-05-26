#include "playerbullet.h"
#include "enemy.h"

PlayerBullet::PlayerBullet(QWidget *parent)
	: Bullet(parent)
{
	setPixmap(QPixmap(":/planeFight/Resources/bullet1.png"));
	setFixedSize(pixmap()->size());
}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::move_()
{
	if (!getPaused())
	{
		if (y() >= -height())
		{
			move(x(), y() - 10);
			for (QObject *i : parentWidget()->children())
			{
				Enemy *j = dynamic_cast<Enemy *>(i);
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