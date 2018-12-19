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

bool Player::changeImage()
{
	//如果玩家飞机活着则切换常态图片
	if (life_ > 0)
	{
		normalImageChangeFpsCounter_++;
		if (normalImageChangeFpsCounter_ == imageChangeFpsInterval_)
		{
			normalImageChangeFpsCounter_ = 0;
			rimage() = normalImageVector_[nowNormalImageIndex_];
			nowNormalImageIndex_++;
			//倘若一轮图片显示完了之后，继续显示下一轮图片
			if (nowNormalImageIndex_ >= normalImageVector_.size())
			{
				nowNormalImageIndex_ = 0;
			}
		}
	}
	//否则切换损毁图片
	else
	{
		destroyImageChangeFpsCounter_++;
		if (destroyImageChangeFpsCounter_ == imageChangeFpsInterval_)
		{
			destroyImageChangeFpsCounter_ = 0;
			//倘若一轮图片显示完了之后，进入游戏结束阶段
			if (nowDestroyImageIndex_ >= destroyImageVector_.size())
			{
				return false;
			}
			//否则显示下一张图片
			else
			{
				rimage() = destroyImageVector_[nowDestroyImageIndex_];
				nowDestroyImageIndex_++;
			}
		}
	}
	return true;
}