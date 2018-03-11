#include "enemyleader.h"

EnemyLeader::EnemyLeader(QWidget *parent)
	: Enemy(parent)
{
	addImg(QPixmap(":/planeFight/Resources/enemy2.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/enemy2_down1.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/enemy2_down2.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/enemy2_down3.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/enemy2_down4.png"));

	resize(QPixmap(":/planeFight/Resources/enemy2.png").size());
	int x = qrand() % (parentWidget()->width() - width());
	move(x, -height());

	show();
}

EnemyLeader::~EnemyLeader()
{

}
