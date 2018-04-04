#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include "QApplication"
#include "QDeskTopWidget"
#include "QTime"
#include "QTimer"
#include "player.h"
#include "enemysolider.h"
#include "enemyleader.h"
#include "enemygeneral.h"

class Scene : public QWidget
{
	Q_OBJECT

public:
	Scene(QWidget *parent);
	~Scene();

private:
	QPixmap backgroundImg;
	QVector<Enemy *(Scene::*)(QWidget *)> enemyChoose;

	EnemySolider *productSolider(QWidget *parent) { return new EnemySolider(parent); }
	EnemyLeader *productLeader(QWidget *parent) { return new EnemyLeader(parent); }
	EnemyGeneral *productGeneral(QWidget *parent) { return new EnemyGeneral(parent); }

private slots:
	void productEnemy();
};

#endif // SCENE_H
