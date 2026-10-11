/**
 * 精灵类 —— 移植自 src/Sprite.h/.cpp
 * 所有游戏对象（飞机 / 子弹 / 道具）的基类。
 */
export default class Sprite {
  /** 左上角坐标 */
  x = 0;
  y = 0;

  /** 宽高 */
  width = 0;
  height = 0;

  /** 当前图片 */
  image: HTMLImageElement | null = null;

  /**
   * 碰撞检测 —— 与 C++ Sprite::isCollided 逐行一致：
   * 判断自身左上角是否落入对方矩形向外扩展自身宽高后的区域。
   */
  isCollided(s: Sprite): boolean {
    return (
      this.x >= s.x - this.width &&
      this.x <= s.x + s.width &&
      this.y >= s.y - this.height &&
      this.y <= s.y + s.height
    );
  }
}
