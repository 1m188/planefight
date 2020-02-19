#pragma once

#include "Plane.h"

//玩家类
class Player : public Plane
{
private:
    //是否上/下/左/右移动
    bool isUping_ = false;
    bool isDowning_ = false;
    bool isLefting_ = false;
    bool isRighting_ = false;

    //是否开火
    bool isFiring_ = false;
    //是否火力加强
    bool isStrengthenFire_ = false;

    //炸弹数目
    int bombNum_ = 1;

public:
    Player();
    ~Player();

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

    //获取是否开火
    const bool isFiring() const { return isFiring_; }
    //获取是否开火的引用
    bool &risFiring() { return isFiring_; }

    //获取是否火力加强
    const bool isStrengthenFire() const { return isStrengthenFire_; }
    //获取是否火力加强的引用
    bool &risStrengthenFire() { return isStrengthenFire_; }

    //获取炸弹数目
    const int bombNum() const { return bombNum_; }
    //获取炸弹数目的引用
    int &rbombNum() { return bombNum_; }

    //玩家飞机移动
    void move(int up, int down, int left, int right);
};
