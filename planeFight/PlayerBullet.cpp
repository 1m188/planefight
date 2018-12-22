#include "PlayerBullet.h"

PlayerBullet::PlayerBullet() :Bullet()
{
}

PlayerBullet::~PlayerBullet()
{
}

bool PlayerBullet::move(int border)
{
	ry() -= dy();
	if (y() + height() <= border)
	{
		return false;
	}
	else
	{
		return true;
	}
}