#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "bullet.h"

class EnemyBullet : public Bullet
{
	Q_OBJECT

public:
	EnemyBullet(QWidget *parent);
	~EnemyBullet();

private:
	
};

#endif // ENEMYBULLET_H
