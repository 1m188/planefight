#include "Image.h"

//初始化单例指针
Image *Image::instance = nullptr;

Image::Image()
{
}

Image::~Image()
{
}

Image *Image::getInstance()
{
    if (!instance)
    {
        instance = new Image();
    }
    return instance;
}

void Image::init()
{
    backgroundImage.load(":/Resources/image/background.png");

    againImage.load(":/Resources/image/again.png");
    gameOverImage.load(":/Resources/image/gameover.png");

    pauseNorImage.load(":/Resources/image/pause_nor.png");
    pausePressedImage.load(":/Resources/image/pause_pressed.png");
    resumeNorImage.load(":/Resources/image/resume_nor.png");
    resumePressedImage.load(":/Resources/image/resume_pressed.png");
    pauseResumeImage = pauseNorImage;

    playerNormalImageVector.append(QPixmap(":/Resources/image/me1.png"));
    playerNormalImageVector.append(QPixmap(":/Resources/image/me2.png"));
    playerDestroyImageVector.append(QPixmap(":/Resources/image/me_destroy_1.png"));
    playerDestroyImageVector.append(QPixmap(":/Resources/image/me_destroy_2.png"));
    playerDestroyImageVector.append(QPixmap(":/Resources/image/me_destroy_3.png"));
    playerDestroyImageVector.append(QPixmap(":/Resources/image/me_destroy_4.png"));

    enemy1NormalImageVector.append(QPixmap(":/Resources/image/enemy1.png"));
    enemy1DestroyImageVector.append(QPixmap(":/Resources/image/enemy1_down1.png"));
    enemy1DestroyImageVector.append(QPixmap(":/Resources/image/enemy1_down2.png"));
    enemy1DestroyImageVector.append(QPixmap(":/Resources/image/enemy1_down3.png"));
    enemy1DestroyImageVector.append(QPixmap(":/Resources/image/enemy1_down4.png"));

    enemy2NormalImageVector.append(QPixmap(":/Resources/image/enemy2.png"));
    enemy2DestroyImageVector.append(QPixmap(":/Resources/image/enemy2_down1.png"));
    enemy2DestroyImageVector.append(QPixmap(":/Resources/image/enemy2_down2.png"));
    enemy2DestroyImageVector.append(QPixmap(":/Resources/image/enemy2_down3.png"));
    enemy2DestroyImageVector.append(QPixmap(":/Resources/image/enemy2_down4.png"));
    enemy2HitImageVector.append(QPixmap(":/Resources/image/enemy2_hit.png"));

    enemy3NormalImageVector.append(QPixmap(":/Resources/image/enemy3_n1.png"));
    enemy3NormalImageVector.append(QPixmap(":/Resources/image/enemy3_n2.png"));
    enemy3DestroyImageVector.append(QPixmap(":/Resources/image/enemy3_down1.png"));
    enemy3DestroyImageVector.append(QPixmap(":/Resources/image/enemy3_down2.png"));
    enemy3DestroyImageVector.append(QPixmap(":/Resources/image/enemy3_down3.png"));
    enemy3DestroyImageVector.append(QPixmap(":/Resources/image/enemy3_down4.png"));
    enemy3DestroyImageVector.append(QPixmap(":/Resources/image/enemy3_down5.png"));
    enemy3DestroyImageVector.append(QPixmap(":/Resources/image/enemy3_down6.png"));
    enemy3HitImageVector.append(QPixmap(":/Resources/image/enemy3_hit.png"));

    playerBulletImage.load(":/Resources/image/bullet1.png");
    enemyBulletImage.load(":/Resources/image/bullet2.png");

    lifeImage.load(":/Resources/image/life.png");

    bombImage.load(":/Resources/image/bomb.png");
    bombPropsImage.load(":/Resources/image/bomb_supply.png");
    bulletPropsImage.load(":/Resources/image/bullet_supply.png");
}