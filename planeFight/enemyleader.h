#ifndef ENEMYLEADER_H
#define ENEMYLEADER_H

#include "enemy.h"

class EnemyLeader : public Enemy
{
	Q_OBJECT

public:
	EnemyLeader(QWidget *parent);
	~EnemyLeader();

private:
	
};

#endif // ENEMYLEADER_H
