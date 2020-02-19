#include "SettingScene.h"
#include "Director.h"
#include "StartScene.h"
#include "FpsChooseScene.h"
#include "QLabel"
#include "QPushButton"
#include "QGridLayout"

SettingScene::SettingScene(Window *parent) : Scene(parent)
{
}

SettingScene::~SettingScene()
{
}

void SettingScene::init()
{
    //控件
    QLabel *infoLabel = new QLabel(this);
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setFont(QFont(u8"微软雅黑", 40));
    infoLabel->setText(tr(u8"设  置"));

    QPushButton *fpsChooseButton = new QPushButton(this);
    fpsChooseButton->setFont(QFont(u8"微软雅黑", 15));
    fpsChooseButton->setText(tr(u8"帧数选择"));
    connect(fpsChooseButton, &QPushButton::clicked, this, &SettingScene::fpsChooseButtonClicked);

    QPushButton *returnToStartSceneButton = new QPushButton(this);
    returnToStartSceneButton->setFont(QFont(u8"微软雅黑", 15));
    returnToStartSceneButton->setText(tr(u8"返回开始场景"));
    connect(returnToStartSceneButton, &QPushButton::clicked, this, &SettingScene::returnToStartSceneButtonClicked);

    //布局
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(infoLabel, 0, 0, 10, 15);
    layout->addWidget(fpsChooseButton, 10, 5, 3, 5);
    layout->addWidget(returnToStartSceneButton, 13, 5, 3, 5);
}

void SettingScene::fpsChooseButtonClicked()
{
    FpsChooseScene *fpsChooseScene = new FpsChooseScene(Director::getInstance()->getWindow());
    Director::getInstance()->setNowScene(fpsChooseScene);
    fpsChooseScene->init();
    fpsChooseScene->show();
    deleteLater();
}

void SettingScene::returnToStartSceneButtonClicked()
{
    StartScene *startScene = new StartScene(Director::getInstance()->getWindow());
    Director::getInstance()->setNowScene(startScene);
    startScene->init();
    startScene->show();
    deleteLater();
}