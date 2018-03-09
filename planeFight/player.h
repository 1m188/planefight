#ifndef PLAYER_H
#define PLAYER_H

#include "plane.h"

class Player : public Plane
{
	Q_OBJECT

public:
	Player(QWidget *parent);
	~Player();

private:
	

public slots:
	void move_();
	void productBullet();
};

#endif // PLAYER_H
