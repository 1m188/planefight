#include "playerbullet.h"

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
		}
		else
		{
			deleteLater();
		}
	}
}