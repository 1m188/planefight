#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"

//敌机
class Enemy :public Sprite
{
private:
	//每次在y方向上移动的距离
	int dy_ = 0;

	//常态图片数组
	QVector<QPixmap> normalImageVector_;
	//当前显示常态图片索引
	int nowNormalImageIndex_ = 0;

	//损毁图片数组
	QVector<QPixmap> destroyImageVector_;
	//当前显示损毁图片索引
	int nowDestroyImageIndex_ = 0;

	//常态图片切换计帧器
	int normalImageChangeFpsCounter_ = 0;
	//损毁图片切换计帧器
	int destroyImageChangeFpsCounter_ = 0;
	//子弹产生计帧器
	int productBulletFpsCounter_ = 0;

	//每隔多少帧切换一张常态/损毁图片
	int imageChangeFpsInterval_ = 0;
	//每隔多少帧产生子弹
	int productBulletFpsInterval_ = 0;

	//生命数目
	int life_ = 1;

public:
	Enemy();
	~Enemy();

	//获取每次在y方向上移动的距离
	const int dy() const { return dy_; }
	//获取每次在y方向上移动的距离的引用
	int &rdy() { return dy_; }

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

	//获取常态图片切换计帧器
	const int normalImageChangeFpsCounter() const { return normalImageChangeFpsCounter_; }
	//获取常态图片切换计帧器的引用
	int &rnormalImageChangeFpsCounter() { return normalImageChangeFpsCounter_; }

	//获取损毁图片切换计帧器
	const int destroyImageChangeFpsCounter() const { return destroyImageChangeFpsCounter_; }
	//获取损毁图片切换计帧器的引用
	int &rdestroyImageChangeFpsCounter() { return destroyImageChangeFpsCounter_; }

	//获取每隔多少帧切换一张常态/损毁图片
	const int imageChangeFpsInterval() const { return imageChangeFpsInterval_; }
	//获取每隔多少帧切换一张常态/损毁图片的引用
	int &rimageChangeFpsInterval() { return imageChangeFpsInterval_; }

	//获取子弹产生计帧器
	const int productBulletFpsCounter() const { return productBulletFpsCounter_; }
	//获取子弹产生计帧器的引用
	int &rproductBulletFpsCounter() { return productBulletFpsCounter_; }

	//获取每隔多少帧产生子弹
	const int productBulletFpsInterval() const { return productBulletFpsInterval_; }
	//获取每隔多少帧产生子弹的引用
	int &rproductBulletFpsInterval() { return productBulletFpsInterval_; }

	//获取生命数目
	const int life() const { return life_; }
	int &rlife() { return life_; }
};

#endif // ENEMY_H
