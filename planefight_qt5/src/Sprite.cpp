#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

const bool Sprite::isCollided(Sprite s) const
{
    return x_ >= s.x_ - width_ && x_ <= s.x_ + s.width_ && y_ >= s.y_ - height_ && y_ <= s.y_ + s.height_;
}