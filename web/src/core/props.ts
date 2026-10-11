import Sprite from './sprite';

/**
 * 道具类别 —— 枚举值与 C++ Props::Type 一致。
 */
export enum PropsType {
  None = 0,
  Bomb = 1,
  Bullet = 2,
}

/** 道具 —— 移植自 src/Props.h/.cpp（移动逻辑在 GameScene 中，与 C++ 相同） */
export default class Props extends Sprite {
  /** 每帧的行进距离 */
  dy = 0;

  /** 标识类型的 id */
  type: PropsType = PropsType.None;
}
