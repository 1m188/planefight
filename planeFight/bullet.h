#ifndef BULLET_H
#define BULLET_H

#include "game.h"
#include "QTimer"

class Bullet : public Game
{
	Q_OBJECT

public:
	Bullet(QWidget *parent);
	virtual ~Bullet();

private:
	
public slots:
	void beCollided();
	virtual void move_() = 0;
};

#endif // BULLET_H
