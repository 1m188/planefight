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
		}
		else
		{
			deleteLater();
		}
	}
}