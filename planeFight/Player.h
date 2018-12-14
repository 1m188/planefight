#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"

//玩家类
class Player :public Sprite
{
private:
	//每帧的两个方向上的飞行距离
	int dx;
	int dy;

	//是否上/下/左/右移动
	bool isUping;
	bool isDowning;
	bool isLefting;
	bool isRighting;

public:
	Player();
	~Player();

	void move(int up, int down, int left, int right);
};

#endif // PLAYER_H
