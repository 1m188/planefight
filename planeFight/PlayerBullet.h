#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "Bullet.h"

//玩家子弹类
class PlayerBullet :public Bullet
{
public:
	PlayerBullet();
	~PlayerBullet();

	//移动
	//传入一个边界
	//没超出边界返回true，否则返回false
	bool move(int border);
};

#endif // !PLAYERBULLET_H
