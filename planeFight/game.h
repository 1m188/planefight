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
	bool getPaused();
	void setPaused(bool);
	bool isCollided(double, double, double, double, double, double, double, double);

signals:
	void collided();

public slots:
	virtual void beCollided() = 0;
};

#endif // GAME_H
