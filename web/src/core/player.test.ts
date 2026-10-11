import { describe, expect, it } from 'vitest';
import Player from './player';

const WIDTH = 900;
const HEIGHT = 700;
const PLANE_WIDTH = 102;
const PLANE_HEIGHT = 126;

function makePlayer(x: number, y: number, speed: number): Player {
  const player = new Player();
  player.width = PLANE_WIDTH;
  player.height = PLANE_HEIGHT;
  player.x = x;
  player.y = y;
  player.dx = speed;
  player.dy = speed;
  return player;
}

describe('Player.move 边界夹紧', () => {
  it('向左越界时夹到左边界', () => {
    const player = makePlayer(10, 100, 20);
    player.isLefting = true;
    player.move(0, HEIGHT, 0, WIDTH);
    expect(player.x).toBe(0);
  });

  it('向上越界时夹到上边界', () => {
    const player = makePlayer(100, 10, 20);
    player.isUping = true;
    player.move(0, HEIGHT, 0, WIDTH);
    expect(player.y).toBe(0);
  });

  it('向右越界时夹到右边界', () => {
    const player = makePlayer(890, 100, 20);
    player.isRighting = true;
    player.move(0, HEIGHT, 0, WIDTH);
    expect(player.x).toBe(WIDTH - PLANE_WIDTH);
  });

  it('向下越界时夹到下边界（初始位置即贴底）', () => {
    const player = makePlayer(100, HEIGHT - PLANE_HEIGHT, 20);
    player.isDowning = true;
    player.move(0, HEIGHT, 0, WIDTH);
    expect(player.y).toBe(HEIGHT - PLANE_HEIGHT);
  });

  it('上下同时按住时相互抵消', () => {
    const player = makePlayer(100, 300, 20);
    player.isUping = true;
    player.isDowning = true;
    player.move(0, HEIGHT, 0, WIDTH);
    expect(player.y).toBe(300);
  });

  it('斜向移动同时作用两个方向', () => {
    const player = makePlayer(100, 300, 20);
    player.isRighting = true;
    player.isUping = true;
    player.move(0, HEIGHT, 0, WIDTH);
    expect(player.x).toBe(120);
    expect(player.y).toBe(280);
  });
});
