#include "scene.h"

Scene::Scene(QWidget *parent)
	: QWidget(parent), backgroundImg(QPixmap(":/planeFight/Resources/background.png"))
{
	setWindowTitle(tr(u8"·É»ú´óÕ½"));
	setFixedSize(700, 940);
	QRect rect = frameGeometry();
	rect.moveCenter(QApplication::desktop()->availableGeometry().center());
	move(rect.topLeft());

	QPalette p = palette();
	p.setBrush(QPalette::Background, QBrush(backgroundImg));
	setPalette(p);

	setCursor(Qt::BlankCursor);
	Player *player = new Player(this);

	show();
}

Scene::~Scene()
{

}
