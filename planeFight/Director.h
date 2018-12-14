#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "Window.h"

//导演类
class Director
{
private:
	Director(); //禁止自动默认构造

	static Director *instance; //单例指针

	Window *window; //游戏窗口

public:
	Director(const Director &) = delete;
	Director &operator=(const Director &) = delete;
	~Director();

	static Director *getInstance(); //获取单例指针

	//获取游戏窗口指针
	Window *getWindow();
	//设置游戏窗口指针
	void setWindow(Window *window);
};

#endif // DIRECTOR_H
