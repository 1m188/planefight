#ifndef PLANE_H
#define PLANE_H

#include "game.h"
#include "QTimer"

class Plane : public Game
{
	Q_OBJECT

public:
	Plane(QWidget *parent);
	virtual ~Plane();

private:
	QTimer *imgChangeTimer;
	QTimer *destroyImgChangeTimer;
	QTimer *productBulletTimer;
	QTimer *moveTimer;

public:
	int life;

	QPair<QVector<QPixmap>, int> img;
	QPair<QVector<QPixmap>, int> destroyImg;

private slots:
	void imgChange();
	void destroyImgChange();

public slots:
	virtual void move_() = 0;
	virtual void productBullet() = 0;
	void beCollided();
};

#endif // PLANE_H
