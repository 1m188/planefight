#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include "QApplication"
#include "QDeskTopWidget"
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

private slots:
	void productEnemy();
};

#endif // SCENE_H
