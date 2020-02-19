#pragma once

#include "Window.h"
#include "Scene.h"

//导演类
class Director
{
private:
    Director(); //禁止自动默认构造

    static Director *instance; //单例指针

    Window *window;  //游戏窗口
    Scene *nowScene; //当前响应场景

public:
    Director(const Director &) = delete;
    Director &operator=(const Director &) = delete;
    ~Director();

    static Director *getInstance(); //获取单例指针

    //获取游戏窗口指针
    Window *getWindow();
    //设置游戏窗口指针
    void setWindow(Window *window);

    //获取当前响应场景
    Scene *getNowScene();
    //设置当前响应场景
    void setNowScene(Scene *nowScene);
};
