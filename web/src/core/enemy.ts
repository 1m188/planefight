import Plane from './plane';

/**
 * 敌机种类 —— 枚举值与 C++ Enemy::Type 一致。
 * 击杀得分直接使用枚举值（Soldier=1 / Leader=2 / General=3）。
 */
export enum EnemyType {
  None = 0,
  Soldier = 1,
  Leader = 2,
  General = 3,
}

/** 敌机 —— 移植自 src/Enemy.h/.cpp */
export default class Enemy extends Plane {
  /** 敌机种类标识 */
  type: EnemyType = EnemyType.None;

  /**
   * 向下移动。
   * 传入地图下边界；返回 false 表示顶部已越过下边界，应被移除。
   */
  move(down: number): boolean {
    this.y += this.dy;
    return !(this.y >= down);
  }
}

/**
 * 击杀得分 —— 移植自 GameScene::getScore：
 * 敌机阵亡（生命为 0）时按种类枚举值计分，否则不得分。
 */
export function enemyScore(enemy: Enemy): number {
  return enemy.life === 0 ? enemy.type : 0;
}
