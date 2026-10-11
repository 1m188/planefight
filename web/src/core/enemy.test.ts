import { describe, expect, it } from 'vitest';
import Enemy, { EnemyType, enemyScore } from './enemy';

describe('Enemy.move', () => {
  it('顶部未越过下边界时存活', () => {
    const enemy = new Enemy();
    enemy.dy = 6;
    enemy.y = 693;
    expect(enemy.move(700)).toBe(true);
    expect(enemy.y).toBe(699);
  });

  it('顶部到达下边界即应被移除', () => {
    const enemy = new Enemy();
    enemy.dy = 6;
    enemy.y = 694;
    expect(enemy.move(700)).toBe(false);
    expect(enemy.y).toBe(700);
  });
});

describe('enemyScore（GameScene::getScore 移植）', () => {
  it('阵亡的士兵得 1 分', () => {
    const enemy = new Enemy();
    enemy.type = EnemyType.Soldier;
    enemy.life = 0;
    expect(enemyScore(enemy)).toBe(1);
  });

  it('阵亡的领导得 2 分', () => {
    const enemy = new Enemy();
    enemy.type = EnemyType.Leader;
    enemy.life = 0;
    expect(enemyScore(enemy)).toBe(2);
  });

  it('阵亡的将军得 3 分', () => {
    const enemy = new Enemy();
    enemy.type = EnemyType.General;
    enemy.life = 0;
    expect(enemyScore(enemy)).toBe(3);
  });

  it('存活时不得分', () => {
    const enemy = new Enemy();
    enemy.type = EnemyType.General;
    enemy.life = 16;
    expect(enemyScore(enemy)).toBe(0);
  });
});
