#include "Enemy.h"

Enemy::Enemy() :Sprite()
{

}

Enemy::~Enemy()
{

}

bool Enemy::move(int down)
{
	ry() += dy_;
	//倘若敌机完全超出地图边界返回false
	//否则返回true
	return !(y() >= down);
}