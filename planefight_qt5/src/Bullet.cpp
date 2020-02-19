#include "Bullet.h"

Bullet::Bullet() : Sprite()
{
}

Bullet::~Bullet()
{
}

bool Bullet::move(int border)
{
    bool isOutOfBorder = true;
    if (type_ == Bullet::Type::Player)
    {
        ry() -= dy();
        isOutOfBorder = !(y() + height() <= border);
    }
    else
    {
        ry() += dy();
        isOutOfBorder = !(y() >= border);
    }
    return isOutOfBorder;
}