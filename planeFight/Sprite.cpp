#include "Sprite.h"

Sprite::Sprite() :x(0), y(0), width(0), height(0), image()
{

}

Sprite::~Sprite()
{

}

bool Sprite::isCollided(Sprite s) const
{
	return x >= s.x - width&&x <= s.x + s.width&&y >= s.y - height&&y <= s.y + s.height;
}