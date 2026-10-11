import { describe, expect, it } from 'vitest';
import Plane from './plane';

/** 测试用假图片，changeImage 只比较引用 */
const img = (id: string) => ({ id }) as unknown as HTMLImageElement;

function makePlane(): Plane {
  const plane = new Plane();
  plane.imageChangeFpsInterval = 2;
  plane.normalImages = [img('n0'), img('n1')];
  plane.destroyImages = [img('d0'), img('d1')];
  plane.image = plane.normalImages[0];
  return plane;
}

describe('Plane.changeImage 存活轮播', () => {
  it('每 2 帧切换一张常态图片并循环', () => {
    const plane = makePlane();
    // f1: 计帧器 1，未到间隔
    plane.changeImage();
    expect(plane.image).toBe(plane.normalImages[0]);
    // f2: 到间隔，赋值 normal[0]，索引推进到 1
    expect(plane.changeImage()).toBe(true);
    expect(plane.image).toBe(plane.normalImages[0]);
    // f4: 赋值 normal[1]，索引回绕到 0
    plane.changeImage();
    expect(plane.changeImage()).toBe(true);
    expect(plane.image).toBe(plane.normalImages[1]);
    expect(plane.nowNormalImageIndex).toBe(0);
    // f6: 回绕后重新显示 normal[0]
    plane.changeImage();
    expect(plane.changeImage()).toBe(true);
    expect(plane.image).toBe(plane.normalImages[0]);
  });

  it('存活状态下永远不会返回 false', () => {
    const plane = makePlane();
    for (let frame = 0; frame < 20; frame++) {
      expect(plane.changeImage()).toBe(true);
    }
  });
});

describe('Plane.changeImage 阵亡损毁动画', () => {
  it('逐张播放损毁图片，播完后返回 false', () => {
    const plane = makePlane();
    plane.life = 0;
    // f1: 计帧器 1，图片未变
    expect(plane.changeImage()).toBe(true);
    expect(plane.image).toBe(plane.normalImages[0]);
    // f2: 显示损毁图 0
    expect(plane.changeImage()).toBe(true);
    expect(plane.image).toBe(plane.destroyImages[0]);
    // f4: 显示损毁图 1
    plane.changeImage();
    expect(plane.changeImage()).toBe(true);
    expect(plane.image).toBe(plane.destroyImages[1]);
    // f5: 最后一展示帧
    expect(plane.changeImage()).toBe(true);
    // f6: 损毁图片播完，返回 false
    expect(plane.changeImage()).toBe(false);
  });
});
