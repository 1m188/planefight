import { describe, expect, it } from 'vitest';
import { frameMs, framesInterval, speedPerFrame } from './frames';

describe('frameMs（1000 / fps 整数除法）', () => {
  it('30fps 为 33ms，45fps 为 22ms，60fps 为 16ms', () => {
    expect(frameMs(30)).toBe(33);
    expect(frameMs(45)).toBe(22);
    expect(frameMs(60)).toBe(16);
  });
});

describe('framesInterval（1000 / 60 * X / (1000 / fps) 整数除法）', () => {
  it('30fps 下与 C++ 计算结果一致', () => {
    expect(framesInterval(13, 30)).toBe(6); // 图片轮播 / 玩家开火间隔
    expect(framesInterval(100, 30)).toBe(48); // 敌机产生间隔
    expect(framesInterval(1000, 30)).toBe(484); // 道具产生间隔
    expect(framesInterval(700, 30)).toBe(339); // 弹药补给持续
    expect(framesInterval(50, 30)).toBe(24); // 士兵开火
    expect(framesInterval(45, 30)).toBe(21); // 领导开火
    expect(framesInterval(40, 30)).toBe(19); // 将军开火
  });

  it('60fps 下间隔值等于 X', () => {
    expect(framesInterval(13, 60)).toBe(13);
    expect(framesInterval(100, 60)).toBe(100);
    expect(framesInterval(1000, 60)).toBe(1000);
    expect(framesInterval(700, 60)).toBe(700);
  });

  it('45fps 下与 C++ 计算结果一致', () => {
    expect(framesInterval(13, 45)).toBe(9);
    expect(framesInterval(100, 45)).toBe(72);
    expect(framesInterval(1000, 45)).toBe(727);
    expect(framesInterval(700, 45)).toBe(509);
  });
});

describe('speedPerFrame（S * 60 / fps 整数除法）', () => {
  it('30fps 下速度翻倍', () => {
    expect(speedPerFrame(10, 30)).toBe(20); // 玩家 / 玩家子弹
    expect(speedPerFrame(5, 30)).toBe(10); // 敌机子弹
    expect(speedPerFrame(3, 30)).toBe(6); // 士兵 / 道具
    expect(speedPerFrame(2, 30)).toBe(4); // 领导
    expect(speedPerFrame(1, 30)).toBe(2); // 将军
  });

  it('60fps 下速度为原始值', () => {
    expect(speedPerFrame(10, 60)).toBe(10);
    expect(speedPerFrame(5, 60)).toBe(5);
    expect(speedPerFrame(3, 60)).toBe(3);
  });

  it('45fps 下与 C++ 计算结果一致', () => {
    expect(speedPerFrame(10, 45)).toBe(13);
    expect(speedPerFrame(5, 45)).toBe(6);
    expect(speedPerFrame(3, 45)).toBe(4);
    expect(speedPerFrame(2, 45)).toBe(2);
    expect(speedPerFrame(1, 45)).toBe(1);
  });
});
