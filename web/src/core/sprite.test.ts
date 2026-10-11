import { describe, expect, it } from 'vitest';
import Sprite from './sprite';

function makeSprite(x: number, y: number, width: number, height: number): Sprite {
  const sprite = new Sprite();
  sprite.x = x;
  sprite.y = y;
  sprite.width = width;
  sprite.height = height;
  return sprite;
}

describe('Sprite.isCollided（C++ 扩边矩形判定公式）', () => {
  it('两矩形重叠时碰撞', () => {
    const a = makeSprite(10, 10, 20, 20);
    const b = makeSprite(5, 5, 30, 30);
    expect(a.isCollided(b)).toBe(true);
  });

  it('左上角恰好落在对方扩边矩形边界上时碰撞（>= 判定）', () => {
    const a = makeSprite(0, 0, 20, 20);
    const b = makeSprite(20, 20, 30, 30);
    expect(a.isCollided(b)).toBe(true);
  });

  it('x 方向差一个像素则不碰撞', () => {
    const a = makeSprite(-1, 0, 20, 20);
    const b = makeSprite(20, 20, 30, 30);
    expect(a.isCollided(b)).toBe(false);
  });

  it('右下角恰好压线时碰撞（<= 判定）', () => {
    const a = makeSprite(50, 50, 20, 20);
    const b = makeSprite(20, 20, 30, 30);
    expect(a.isCollided(b)).toBe(true);
  });

  it('右下方向差一个像素则不碰撞', () => {
    const a = makeSprite(51, 50, 20, 20);
    const b = makeSprite(20, 20, 30, 30);
    expect(a.isCollided(b)).toBe(false);
  });

  it('仅 y 方向超出则不碰撞', () => {
    const a = makeSprite(10, 100, 20, 20);
    const b = makeSprite(10, 10, 30, 30);
    expect(a.isCollided(b)).toBe(false);
  });
});
