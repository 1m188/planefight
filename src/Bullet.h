#pragma once

#include "Sprite.h"

//子弹类
class Bullet : public Sprite
{
private:
    //每帧在y方向上移动的距离
    int dy_ = 0;

public:
    Bullet();
    ~Bullet();

    //子弹类别类型
    enum Type
    {
        None,
        Player,
        Enemy,
    };

    //获取子弹类别
    const Bullet::Type type() const { return type_; }
    //获取子弹类别的引用
    Bullet::Type &rtype() { return type_; }

    //获取每帧在y方向上移动的距离
    const int dy() const { return dy_; }
    //获取每帧在y方向上移动的距离的引用
    int &rdy() { return dy_; }

    //移动
    //传入边界，返回true没事，返回false说明子弹超出边界
    bool move(int border);

private:
    //子弹类别
    Bullet::Type type_ = Bullet::Type::None;
};
