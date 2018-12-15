#include "Sprite.h"

Sprite::Sprite() :x_(0), y_(0), width_(0), height_(0), image_()
{

}

Sprite::~Sprite()
{

}

const bool Sprite::isCollided(Sprite s) const
{
	return x_ >= s.x_ - width_&&x_ <= s.x_ + s.width_&&y_ >= s.y_ - height_&&y_ <= s.y_ + s.height_;
}