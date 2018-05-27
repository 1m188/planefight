#include "enemygeneral.h"

EnemyGeneral::EnemyGeneral(QWidget *parent)
	: Enemy(parent)
{
	setLife(5);

	addImg(QPixmap(":/planeFight/Resources/enemy3_n1.png"));
	addImg(QPixmap(":/planeFight/Resources/enemy3_n2.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/enemy3_down1.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/enemy3_down2.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/enemy3_down3.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/enemy3_down4.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/enemy3_down5.png"));
	addDestroyImg(QPixmap(":/planeFight/Resources/enemy3_down6.png"));
	addHitImg(QPixmap(":/planeFight/Resources/enemy3_hit.png"));

	resize(QPixmap(":/planeFight/Resources/enemy3_n1.png").size());
	int x = qrand() % (parentWidget()->width() - width());
	move(x, -height());

	show();
}

EnemyGeneral::~EnemyGeneral()
{

}
