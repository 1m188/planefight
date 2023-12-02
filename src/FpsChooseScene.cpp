#include "FpsChooseScene.h"
#include "Director.h"
#include "Config.h"
#include "StartScene.h"
#include "QLabel"
#include "QPushButton"
#include "QSlider"
#include "QGridLayout"

FpsChooseScene::FpsChooseScene(Window *parent) : Scene(parent)
{
}

FpsChooseScene::~FpsChooseScene()
{
}

void FpsChooseScene::init()
{
    //控件
    QLabel *infoLabel = new QLabel(this);
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setFont(QFont(u8"微软雅黑", 40));
    infoLabel->setText(tr(u8"帧  数  选  择"));

    QLabel *fpsLabel = new QLabel(this);
    fpsLabel->setAlignment(Qt::AlignCenter);
    fpsLabel->setFont(QFont(u8"微软雅黑", 20));
    fpsLabel->setText(tr(u8"FPS"));

    QLabel *fpsValueLabel = new QLabel(this);
    fpsValueLabel->setAlignment(Qt::AlignCenter);
    fpsValueLabel->setFont(QFont(u8"微软雅黑", 20));
    fpsValueLabel->setText(QString::number(Config::getInstance()->fps()));

    QSlider *fpsSlider = new QSlider(this);
    fpsSlider->setOrientation(Qt::Horizontal);
    fpsSlider->setMinimum(30);
    fpsSlider->setMaximum(60);
    fpsSlider->setSingleStep(1);
    fpsSlider->setValue(Config::getInstance()->fps());
    connect(fpsSlider, &QSlider::valueChanged, this, [=](int value) { fpsValueLabel->setText(QString::number(value)); });
    connect(fpsSlider, &QSlider::sliderReleased, this, [=]() { Config::getInstance()->rfps() = fpsSlider->value(); });

    QPushButton *returnToStartSceneButton = new QPushButton(this);
    returnToStartSceneButton->setFont(QFont(u8"微软雅黑", 15));
    returnToStartSceneButton->setText(tr(u8"返回开始场景"));
    connect(returnToStartSceneButton, &QPushButton::clicked, this, &FpsChooseScene::returnToStartSceneButtonClicked);

    //布局
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(infoLabel, 0, 0, 10, 15);
    layout->addWidget(fpsLabel, 10, 0, 3, 5);
    layout->addWidget(fpsSlider, 10, 5, 3, 5);
    layout->addWidget(fpsValueLabel, 10, 10, 3, 5);
    layout->addWidget(returnToStartSceneButton, 13, 5, 3, 5);
}

void FpsChooseScene::returnToStartSceneButtonClicked()
{
    StartScene *startScene = new StartScene(Director::getInstance()->getWindow());
    Director::getInstance()->setNowScene(startScene);
    startScene->init();
    startScene->show();
    deleteLater();
}