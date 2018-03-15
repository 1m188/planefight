#include "player.h"

Player::Player(QWidget *parent)
	: Plane(parent)
{
	addImg(QPixmap(":/planeFight/Resources/me1.png"));
	addImg(QPixmap(":/planeFight/Resources/me2.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/me_destroy_1.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/me_destroy_2.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/me_destroy_3.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/me_destroy_4.png"));

	move(parentWidget()->width() / 2 - width() / 2, parentWidget()->height() - height());

	show();
}

Player::~Player()
{
	
}

void Player::move_()
{
	if (getLife() > 0 && (!getPaused()))
	{
		QPoint pos = parentWidget()->mapFromGlobal(QCursor::pos());
		move(pos.x() - width() / 2, pos.y() - height() / 2);
		if (pos.x() <= width() / 2)
		{
			move(0, y());
		}
		if (pos.y() <= height() / 2)
		{
			move(x(), 0);
		}
		if (pos.x() >= parentWidget()->width() - width() / 2)
		{
			move(parentWidget()->width() - width(), y());
		}
		if (pos.y() >= parentWidget()->height() - height() / 2)
		{
			move(x(), parentWidget()->height() - height());
		}
	}
}

void Player::productBullet()
{
	if (!getPaused() && getLife() > 0)
	{
		PlayerBullet *b = new PlayerBullet(parentWidget());
		b->move(x() + width() / 2, y());
		b->show();
	}
}