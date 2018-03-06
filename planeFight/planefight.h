#ifndef PLANEFIGHT_H
#define PLANEFIGHT_H

#include <QtWidgets/QWidget>
#include "ui_planefight.h"

class planeFight : public QWidget
{
	Q_OBJECT

public:
	planeFight(QWidget *parent = 0);
	~planeFight();

private:
	Ui::planeFightClass ui;
};

#endif // PLANEFIGHT_H
