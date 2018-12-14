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
	if (isUping)
	{
		setY(getY() - dy);
	}
	if (isDowning)
	{
		setY(getY() + dy);
	}
	if (isLefting)
	{
		setX(getX() - dx);
	}
	if (isRighting)
	{
		setX(getX() + dx);
	}

	//撞墙
	if (getY() < up)
	{
		setY(up);
	}
	else if (getY()+getHeight() > down)
	{
		setY(down - getHeight());
	}
	if (getX() < left)
	{
		setX(left);
	}
	else if (getX() + getWidth() > right)
	{
		setX(right - getWidth());
	}
}