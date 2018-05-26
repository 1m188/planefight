#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "bullet.h"
#include "player.h"

class EnemyBullet : public Bullet
{
	Q_OBJECT

public:
	EnemyBullet(QWidget *parent);
	~EnemyBullet();

private:
	
public slots:
	void move_();
};

#endif // ENEMYBULLET_H
