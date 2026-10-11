import Sprite from './sprite';

/**
 * 飞机类 —— 移植自 src/Plane.h/.cpp
 * 在精灵基础上增加：飞行速度、常态/损毁图片轮播、子弹产生计帧、生命数。
 */
export default class Plane extends Sprite {
  /** 每帧两个方向上的飞行距离 */
  dx = 0;
  dy = 0;

  /** 常态图片数组与当前显示索引 */
  normalImages: HTMLImageElement[] = [];
  nowNormalImageIndex = 0;

  /** 损毁图片数组与当前显示索引 */
  destroyImages: HTMLImageElement[] = [];
  nowDestroyImageIndex = 0;

  /** 常态图片切换计帧器 */
  normalImageChangeFpsCounter = 0;
  /** 损毁图片切换计帧器 */
  destroyImageChangeFpsCounter = 0;
  /** 子弹产生计帧器 */
  productBulletFpsCounter = 0;

  /** 每隔多少帧切换一张常态/损毁图片 */
  imageChangeFpsInterval = 0;
  /** 每隔多少帧产生一次子弹 */
  productBulletFpsInterval = 0;

  /** 生命数目 */
  life = 1;

  /**
   * 切换图片 —— 与 C++ Plane::changeImage 逻辑一致。
   * 存活时每隔 imageChangeFpsInterval 帧轮播一张常态图片，返回 true；
   * 阵亡后逐张播放损毁图片，全部展示完毕后返回 false。
   */
  changeImage(): boolean {
    if (this.life > 0) {
      this.normalImageChangeFpsCounter++;
      if (this.normalImageChangeFpsCounter === this.imageChangeFpsInterval) {
        this.normalImageChangeFpsCounter = 0;
        this.image = this.normalImages[this.nowNormalImageIndex];
        this.nowNormalImageIndex++;
        if (this.nowNormalImageIndex >= this.normalImages.length) {
          this.nowNormalImageIndex = 0;
        }
      }
    } else {
      this.destroyImageChangeFpsCounter++;
      if (this.destroyImageChangeFpsCounter === this.imageChangeFpsInterval) {
        this.destroyImageChangeFpsCounter = 0;
        // 损毁图片都展示完了则返回 false（调用方会移除该飞机）
        if (this.nowDestroyImageIndex >= this.destroyImages.length) {
          return false;
        }
        this.image = this.destroyImages[this.nowDestroyImageIndex];
        this.nowDestroyImageIndex++;
      }
    }
    return true;
  }
}
