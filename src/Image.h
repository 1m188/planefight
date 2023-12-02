#pragma once

#include "QPixmap"

//图片类
//用来提前加载游戏图片到内存中
class Image
{
private:
    Image();                //禁止自动默认构造
    static Image *instance; //单例指针

public:
    Image(const Image &) = delete;
    Image &operator=(const Image &) = delete;
    ~Image();

    //获取单例指针
    static Image *getInstance();

    //初始化
    void init();

    //图片
    QPixmap backgroundImage; //背景图片

    QPixmap againImage;    //再来一次游戏按钮
    QPixmap gameOverImage; //游戏结束按钮

    QPixmap pauseNorImage;      //暂停按钮（没按下时）
    QPixmap pausePressedImage;  //暂停按钮（按下时）
    QPixmap resumeNorImage;     //继续按钮（没按下时）
    QPixmap resumePressedImage; //继续按钮（按下时）
    QPixmap pauseResumeImage;   //实际被绘制的暂停/继续按钮

    QVector<QPixmap> playerNormalImageVector;  //玩家常态图片
    QVector<QPixmap> playerDestroyImageVector; //玩家损毁图片

    QVector<QPixmap> enemy1NormalImageVector;  //敌机1常态图片
    QVector<QPixmap> enemy1DestroyImageVector; //敌机1损毁图片

    QVector<QPixmap> enemy2NormalImageVector;  //敌机2常态图片
    QVector<QPixmap> enemy2DestroyImageVector; //敌机2损毁图片
    QVector<QPixmap> enemy2HitImageVector;     //敌机2损态图片

    QVector<QPixmap> enemy3NormalImageVector;  //敌机3常态图片
    QVector<QPixmap> enemy3DestroyImageVector; //敌机3损毁图片
    QVector<QPixmap> enemy3HitImageVector;     //敌机3损态图片

    QPixmap playerBulletImage; //玩家子弹图片
    QPixmap enemyBulletImage;  //敌机子弹图片

    QPixmap lifeImage; //生命图片

    QPixmap bombImage;        //炸弹图片
    QPixmap bombPropsImage;   //炸弹道具图片
    QPixmap bulletPropsImage; //弹药补给图片
};
