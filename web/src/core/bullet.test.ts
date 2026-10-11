import { describe, expect, it } from 'vitest';
import Bullet, { BulletType } from './bullet';

const image = { width: 5, height: 11 } as unknown as HTMLImageElement;

function makeBullet(type: BulletType, y: number, dy: number): Bullet {
  const bullet = new Bullet();
  bullet.type = type;
  bullet.image = image;
  bullet.width = 5;
  bullet.height = 11;
  bullet.x = 100;
  bullet.y = y;
  bullet.dy = dy;
  return bullet;
}

describe('Bullet.move 玩家子弹（向上，上边界 0）', () => {
  it('在地图内返回 true 并向上移动', () => {
    const bullet = makeBullet(BulletType.Player, 30, 20);
    expect(bullet.move(0)).toBe(true);
    expect(bullet.y).toBe(10);
  });

  it('顶部尚有残留时仍存活', () => {
    const bullet = makeBullet(BulletType.Player, 11, 20);
    expect(bullet.move(0)).toBe(true);
    expect(bullet.y).toBe(-9);
  });

  it('整颗子弹越过上边界后返回 false', () => {
    const bullet = makeBullet(BulletType.Player, 9, 20);
    expect(bullet.move(0)).toBe(false);
    expect(bullet.y).toBe(-11);
  });
});

describe('Bullet.move 敌机子弹（向下，下边界 700）', () => {
  it('在地图内返回 true 并向下移动', () => {
    const bullet = makeBullet(BulletType.Enemy, 680, 10);
    expect(bullet.move(700)).toBe(true);
    expect(bullet.y).toBe(690);
  });

  it('顶部压到下边界即返回 false', () => {
    const bullet = makeBullet(BulletType.Enemy, 690, 10);
    expect(bullet.move(700)).toBe(false);
    expect(bullet.y).toBe(700);
  });
});
