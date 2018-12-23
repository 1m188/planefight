#include "Plane.h"

Plane::Plane() :Sprite()
{
}

Plane::~Plane()
{
}

bool Plane::changeImage()
{
	//如果生命大于0切换常态图片
	if (life_ > 0)
	{
		//切换常态图片
		normalImageChangeFpsCounter_++;
		if (normalImageChangeFpsCounter_ == imageChangeFpsInterval_)
		{
			normalImageChangeFpsCounter_ = 0;
			rimage() = normalImageVector_[nowNormalImageIndex_];
			nowNormalImageIndex_++;
			if (nowNormalImageIndex_ >= normalImageVector_.size())
			{
				nowNormalImageIndex_ = 0;
			}
		}
	}
	//否则展示损毁图片
	else
	{
		destroyImageChangeFpsCounter_++;
		if (destroyImageChangeFpsCounter_ == imageChangeFpsInterval_)
		{
			destroyImageChangeFpsCounter_ = 0;
			//倘若损毁图片都展示完了则从数组中推出去
			if (nowDestroyImageIndex_ >= destroyImageVector_.size())
			{
				return false;
			}
			//否则继续展示下一张图片
			else
			{
				rimage() = destroyImageVector_[nowDestroyImageIndex_];
				nowDestroyImageIndex_++;
			}
		}
	}
	return true;
}