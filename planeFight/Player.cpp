#include "Player.h"

Player::Player() :Sprite()
{

}

Player::~Player()
{

}

void Player::move(int up, int down, int left, int right)
{
	//按照方向移动
	if (isUping_)
	{
		ry() = y() - dy_;
	}
	if (isDowning_)
	{
		ry() = y() + dy_;
	}
	if (isLefting_)
	{
		rx() = x() - dx_;
	}
	if (isRighting_)
	{
		rx() = x() + dx_;
	}

	//撞墙
	if (y() < up)
	{
		ry() = up;
	}
	else if (y() + height() > down)
	{
		ry() = down - height();
	}
	if (x() < left)
	{
		rx() = left;
	}
	else if (x() + width() > right)
	{
		rx() = right - width();
	}
}