#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"

//玩家类
class Player :public Sprite
{
private:
	//每帧的两个方向上的飞行距离
	int dx_;
	int dy_;

	//是否上/下/左/右移动
	bool isUping_;
	bool isDowning_;
	bool isLefting_;
	bool isRighting_;

	//常态图片数组
	QVector<QPixmap> normalImageVector_;

	//损毁图片数组
	QVector<QPixmap> destroyImageVector_;

public:
	Player();
	~Player();

	//获取每帧的两个方向上的飞行距离
	const int dx() const { return dx_; }
	const int dy() const { return dy_; }
	//获取每帧的两个方向上的飞行距离的引用
	int &rdx() { return dx_; }
	int &rdy() { return dy_; }

	//获取是否上/下/左/右移动
	const bool isUping() const { return isUping_; }
	const bool isDowning() const { return isDowning_; }
	const bool isLefting() const { return isLefting_; }
	const bool isRighting() const { return isRighting_; }
	//获取是否上/下/左/右移动的引用
	bool &risUping() { return isUping_; }
	bool &risDowning() { return isDowning_; }
	bool &risLefting() { return isLefting_; }
	bool &risRighting() { return isRighting_; }

	//获取常态/损毁图片数组
	QVector<QPixmap> normalImageVector() { return normalImageVector_; }
	QVector<QPixmap> destroyImageVector() { return destroyImageVector_; }
	//获取常态/损毁图片数组的引用
	QVector<QPixmap> &rnormalImageVector() { return normalImageVector_; }
	QVector<QPixmap> &rdestroyImageVector() { return destroyImageVector_; }

	//玩家飞机移动
	void move(int up, int down, int left, int right);
};

#endif // PLAYER_H
