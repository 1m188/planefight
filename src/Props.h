﻿#pragma once

#include "Sprite.h"

//道具类
class Props : public Sprite
{
private:
    //每帧的行进距离
    int dy_ = 0;

public:
    Props();
    ~Props();

    //表示道具类型
    enum Type
    {
        //无
        None,
        //炸弹
        Bomb,
        //弹药补给
        Bullet,
    };

    //获取道具类型的id
    const Props::Type type() const { return type_; }
    //获取道具类型的id的引用
    Props::Type &rtype() { return type_; }

    //获取每帧的行进距离
    const int dy() const { return dy_; }
    //获取每帧的行进距离的引用
    int &rdy() { return dy_; }

private:
    //标识类型的id
    Props::Type type_ = Props::Type::None;
};
