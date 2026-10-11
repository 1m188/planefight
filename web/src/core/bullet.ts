import Sprite from './sprite';

/**
 * 子弹类别 —— 枚举值与 C++ Bullet::Type 一致。
 */
export enum BulletType {
  None = 0,
  Player = 1,
  Enemy = 2,
}

/** 子弹 —— 移植自 src/Bullet.h/.cpp */
export default class Bullet extends Sprite {
  /** 每帧在 y 方向上移动的距离 */
  dy = 0;

  /** 子弹类别 */
  type: BulletType = BulletType.None;

  /**
   * 移动并判断是否越界 —— 与 C++ Bullet::move 一致。
   * 玩家子弹向上飞，敌方子弹向下飞。
   * 传入边界；返回 true 表示仍在地图内，返回 false 表示越界应被移除。
   */
  move(border: number): boolean {
    if (this.type === BulletType.Player) {
      this.y -= this.dy;
      // 整颗子弹越过上边界才移除
      return !(this.y + this.height <= border);
    }
    this.y += this.dy;
    // 顶部越过下边界即移除
    return !(this.y >= border);
  }
}
