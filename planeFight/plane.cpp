#include "plane.h"

Plane::Plane(QWidget *parent)
	: Game(parent), life(1), img({ QVector<QPixmap>{},0 }), destroyImg({ QVector<QPixmap>{},0 }), hitImg({ QVector<QPixmap>{},0 }), imgChangeTimer(new QTimer(this)), destroyImgChangeTimer(new QTimer(this)), productBulletTimer(new QTimer(this)), moveTimer(new QTimer(this))
{
	connect(imgChangeTimer, &QTimer::timeout, this, &Plane::imgChange);
	imgChangeTimer->start(100);
	connect(destroyImgChangeTimer, &QTimer::timeout, this, &Plane::destroyImgChange);
	destroyImgChangeTimer->start(120);
	connect(moveTimer, &QTimer::timeout, this, &Plane::move_);
	moveTimer->start(20);
	connect(productBulletTimer, &QTimer::timeout, this, &Plane::productBullet);
	productBulletTimer->start(500);
}

Plane::~Plane()
{

}

void Plane::imgChange()
{
	if (!getPaused())
	{
		if (img.first.size() > 0 && hitImg.first.size() > 0)
		{
			if (life > 2)
			{
				setPixmap(img.first.at(img.second));
				resize(pixmap()->size());
				img.second++;
				if (img.second >= img.first.size())
				{
					img.second = 0;
				}
			}
			else if (life > 0) //生命小于2大于0的时候切换成损坏图片
			{
				setPixmap(hitImg.first.at(hitImg.second));
				resize(pixmap()->size());
				hitImg.second++;
				if (hitImg.second >= hitImg.first.size())
				{
					hitImg.second = 0;
				}
			}
		}
		else if (img.first.size() > 0)
		{
			if (life > 0)
			{
				setPixmap(img.first.at(img.second));
				resize(pixmap()->size());
				img.second++;
				if (img.second >= img.first.size())
				{
					img.second = 0;
				}
			}
		}
	}
}

void Plane::destroyImgChange()
{
	if (life <= 0 && (!getPaused()))
	{
		if (destroyImg.first.size() > 0)
		{
			setPixmap(destroyImg.first.at(destroyImg.second));
			resize(pixmap()->size());
			destroyImg.second++;
			if (destroyImg.second >= destroyImg.first.size())
			{
				emit planeDestroyed();
				deleteLater();
			}
		}
		else
		{
			emit planeDestroyed();
			deleteLater();
		}
	}
}

void Plane::beCollided()
{
	life--;
}

void Plane::setLife(int life)
{
	this->life = life;
}

const int Plane::getLife() const
{
	return life;
}

void Plane::addImg(QPixmap img)
{
	this->img.first.append(img);
}

void Plane::addDestroyImg(QPixmap destroyImg)
{
	this->destroyImg.first.append(destroyImg);
}

void Plane::addHitImg(QPixmap hitImg)
{
	this->hitImg.first.append(hitImg);
}