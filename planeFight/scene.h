#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include "QApplication"
#include "QDeskTopWidget"
#include "QLabel"
#include "QPushButton"
#include "QBitMap"
#include "QTime"
#include "QTimer"
#include "QKeyEvent"
#include "player.h"
#include "enemysolider.h"
#include "enemyleader.h"
#include "enemygeneral.h"

#include "QDebug"

class Scene : public QWidget
{
	Q_OBJECT

public:
	Scene(QWidget *parent);
	~Scene();

private:
	QPixmap backgroundImg;
	QPixmap againImg;
	QPixmap gameoverImg;
	QLabel *gameOverLabel;
	QPushButton *againButton;
	QPushButton *gameoverButton;
	QVector<Enemy *(Scene::*)(QWidget *)> enemyChoose;
	QTimer *productEnemyTimer;

	EnemySolider *productSolider(QWidget *parent) { return new EnemySolider(parent); }
	EnemyLeader *productLeader(QWidget *parent) { return new EnemyLeader(parent); }
	EnemyGeneral *productGeneral(QWidget *parent) { return new EnemyGeneral(parent); }

protected:
	void keyPressEvent(QKeyEvent *event);

private slots:
	void productEnemy();
	void gameOver();
	void againButtonClicked();	
};

#endif // SCENE_H
