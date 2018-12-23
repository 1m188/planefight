#ifndef ENEMY_H
#define ENEMY_H

#include "Plane.h"

//敌机
class Enemy :public Plane
{
public:
	Enemy();
	~Enemy();

	//表示敌机类型的枚举
	enum Type
	{
		//无
		None,
		//士兵（第一类敌机）
		Soldier,
		//领导（第二类敌机）
		Leader,
		//将军（第三类敌机）
		General,
	};

	//获取敌机种类标识
	const Enemy::Type type() const { return type_; }
	//获取敌机种类标识的引用
	Enemy::Type &rtype() { return type_; }

	//移动
	//传入参数为地图下边界
	//没超出地图下边界则返回true，否则返回false
	bool move(int down);

private:
	//标识敌机种类
	Enemy::Type type_ = Enemy::Type::None;
};

#endif // ENEMY_H
