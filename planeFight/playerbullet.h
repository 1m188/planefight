#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "bullet.h"

class PlayerBullet : public Bullet
{
	Q_OBJECT

public:
	PlayerBullet(QWidget *parent);
	~PlayerBullet();

private:
	
public slots:
	void move_();
};

#endif // PLAYERBULLET_H
