import Plane from './plane';

/**
 * 玩家类 —— 移植自 src/Player.h/.cpp
 * 在飞机基础上增加：方向键状态、火力加强、炸弹数目。
 * （网页版适配：开火改为自动进行，不再需要 isFiring 按键状态。）
 */
export default class Player extends Plane {
  /** 是否正在上/下/左/右移动 */
  isUping = false;
  isDowning = false;
  isLefting = false;
  isRighting = false;

  /** 是否火力加强（吃到弹药补给后三向开火） */
  isStrengthenFire = false;

  /** 炸弹数目 */
  bombNum = 1;

  /**
   * 玩家飞机移动 —— 与 C++ Player::move 一致：
   * 先按方向位移，再向上/下/左/右四条边界夹紧。
   */
  move(up: number, down: number, left: number, right: number): void {
    if (this.isUping) {
      this.y -= this.dy;
    }
    if (this.isDowning) {
      this.y += this.dy;
    }
    if (this.isLefting) {
      this.x -= this.dx;
    }
    if (this.isRighting) {
      this.x += this.dx;
    }

    // 撞墙（边界夹紧）
    if (this.y < up) {
      this.y = up;
    } else if (this.y + this.height > down) {
      this.y = down - this.height;
    }
    if (this.x < left) {
      this.x = left;
    } else if (this.x + this.width > right) {
      this.x = right - this.width;
    }
  }
}
