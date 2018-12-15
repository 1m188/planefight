#ifndef BULLET_H
#define BULLET_H

#include "Sprite.h"

//子弹类
class Bullet :public Sprite
{
private:
	//每帧在y方向上移动的距离
	int dy_ = 0;

public:
	Bullet();
	~Bullet();

	//获取每帧在y方向上移动的距离
	const int dy() const { return dy_; }
	//获取每帧在y方向上移动的距离的引用
	int &rdy() { return dy_; }
};

#endif // BULLET_H
