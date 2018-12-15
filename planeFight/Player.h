#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"

//玩家类
class Player :public Sprite
{
private:
	//每帧的两个方向上的飞行距离
	int dx_ = 0;
	int dy_ = 0;

	//是否上/下/左/右移动
	bool isUping_ = false;
	bool isDowning_ = false;
	bool isLefting_ = false;
	bool isRighting_ = false;

	//常态图片数组
	QVector<QPixmap> normalImageVector_;
	//当前显示常态图片索引
	int nowNormalImageIndex_ = 0;

	//损毁图片数组
	QVector<QPixmap> destroyImageVector_;
	//当前显示损毁图片索引
	int nowDestroyImageIndex_ = 0;

	//每隔多少帧切换一张常态/损毁图片
	int imageChangeFps_ = 0;

	//生命数目
	int life_ = 1;

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

	//获取当前显示常态图片索引
	const int nowNormalImageIndex() const { return nowNormalImageIndex_; }
	//获取当前显示常态图片索引的引用
	int &rnowNormalImageIndex() { return nowNormalImageIndex_; }
	//获取当前显示损毁图片索引
	const int nowDestroyImageIndex() const { return nowDestroyImageIndex_; }
	//获取当前显示损毁图片索引的引用
	int &rnowDestroyImageIndex() { return nowDestroyImageIndex_; }

	//获取每隔多少帧切换一张常态/损毁图片
	const int imageChangeFps() const { return imageChangeFps_; }
	//获取每隔多少帧切换一张常态/损毁图片的引用
	int &rimageChangeFps() { return imageChangeFps_; }

	//获取生命数目
	const int life() const { return life_; }
	//获取生命数目引用
	int &rlife() { return life_; }

	//玩家飞机移动
	void move(int up, int down, int left, int right);
};

#endif // PLAYER_H
