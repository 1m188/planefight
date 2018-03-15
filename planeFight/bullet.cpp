#include "bullet.h"

Bullet::Bullet(QWidget *parent)
	: Game(parent)
{
	QTimer *moveTimer = new QTimer(this);
	connect(moveTimer, &QTimer::timeout, this, &Bullet::move_);
	moveTimer->start(20);
}

Bullet::~Bullet()
{

}

void Bullet::beCollided()
{
	deleteLater();
}