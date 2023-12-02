#pragma once

#include "Scene.h"

//设置场景
class SettingScene : public Scene
{
public:
    SettingScene(Window *parent);
    ~SettingScene();

    //初始化场景
    void init() override;

private slots:
    void fpsChooseButtonClicked();          //单击帧数选择按钮
    void returnToStartSceneButtonClicked(); //单击返回开始场景按钮
};
