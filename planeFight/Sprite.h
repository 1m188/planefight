#ifndef SPRITE_H
#define SPRITE_H

#include "QPixmap"

//精灵类
class Sprite
{
private:
	//左上角坐标
	int x_;
	int y_;

	//宽高
	int width_;
	int height_;

	//图片
	QPixmap image_;

public:
	Sprite();
	virtual ~Sprite();

	//获取左上角坐标
	const int x() const { return x_; }
	const int y() const { return y_; }
	//获取左上角坐标引用
	int &rx() { return x_; }
	int &ry() { return y_; }

	//获取宽高
	const int width() const { return width_; }
	const int height() const { return height_; }
	//获取宽高引用
	int &rwidth() { return width_; }
	int &rheight() { return height_; }

	//获取图片
	const QPixmap image() const { return image_; }
	//获取图片引用
	QPixmap &rimage() { return image_; }

	//碰撞检测
	const bool isCollided(Sprite s) const;
};

#endif // SPRITE_H
