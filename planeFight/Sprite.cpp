#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::~Sprite()
{

}

bool Sprite::isCollided(Sprite s) const
{
	return x >= s.x - width&&x <= s.x + s.width&&y >= s.y - height&&y <= s.y + s.height;
}