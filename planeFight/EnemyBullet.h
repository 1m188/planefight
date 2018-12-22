#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "Bullet.h"

//敌机子弹类
class EnemyBullet :public Bullet
{
public:
	EnemyBullet();
	~EnemyBullet();

	//移动
	//传入一个移动边界
	//超过边界返回false，否则返回true
	bool move(int border);
};

#endif // !ENEMYBULLET_H
