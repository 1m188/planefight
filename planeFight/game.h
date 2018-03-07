#ifndef GAME_H
#define GAME_H

#include <QLabel>

class Game : public QLabel
{
	Q_OBJECT

public:
	Game(QWidget *parent);
	virtual ~Game();

private:
	bool isPaused;

public:
	virtual void setPaused(bool) = 0;
	virtual bool isCollided(double, double, double, double, double, double, double, double) = 0;
};

#endif // GAME_H
