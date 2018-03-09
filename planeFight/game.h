#ifndef GAME_H
#define GAME_H

#include <QLabel>
#include "QDebug"

class Game : public QLabel
{
	Q_OBJECT

public:
	Game(QWidget *parent);
	virtual ~Game();

private:
	bool isPaused;

public:
	const bool getPaused() const;
	void setPaused(bool);
	const bool isCollided(double, double, double, double, double, double, double, double) const;

signals:
	void collided();

public slots:
	virtual void beCollided() = 0;
};

#endif // GAME_H
