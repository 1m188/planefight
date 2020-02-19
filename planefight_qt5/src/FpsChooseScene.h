#pragma once

#include "Scene.h"

//帧数选择场景
class FpsChooseScene : public Scene
{
public:
    FpsChooseScene(Window *parent);
    ~FpsChooseScene();

    //初始化场景
    void init() override;

private slots:
    void returnToStartSceneButtonClicked(); //单击返回开始场景按钮
};
