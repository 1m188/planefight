#include "Scene.h"
#include "Image.h"

Scene::Scene(Window *parent) : QWidget(parent)
{
    //设置大小和窗口一样大
    resize(parent->size());

    //设置背景
    setAutoFillBackground(true);
    QPalette pa;
    pa.setBrush(QPalette::Background, QBrush(Image::getInstance()->backgroundImage.scaled(size())));
    setPalette(pa);

    //样式表设置按钮颜色和透明度
    setStyleSheet("QPushButton{background-color:rgba(254,254,254,0.2);}");
}

Scene::~Scene()
{
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);
}

void Scene::keyReleaseEvent(QKeyEvent *event)
{
    QWidget::keyReleaseEvent(event);
}

void Scene::init()
{
}