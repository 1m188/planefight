#include "EnemyBullet.h"

EnemyBullet::EnemyBullet() :Bullet()
{
}

EnemyBullet::~EnemyBullet()
{
}

bool EnemyBullet::move(int border)
{
	ry() += dy();
	if (y() >= border)
	{
		return false;
	}
	else
	{
		return true;
	}
}