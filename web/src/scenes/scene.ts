import type Director from '../director';

/**
 * 场景基类 —— 移植自 src/Scene.h/.cpp。
 * 原版的背景铺填与按钮透明度由 DOM/CSS 承担，
 * 键盘事件由 Window（此处为 Director）路由到当前场景。
 */
export default class Scene {
  constructor(protected readonly director: Director) {}

  /** 初始化场景（挂载 DOM、启动循环） */
  init(): void {}

  /** 销毁场景（卸载 DOM、解绑事件、停止循环） */
  destroy(): void {}

  /** 键盘按下（对应 Scene::keyPressEvent） */
  handleKeyDown(_event: KeyboardEvent): void {}

  /** 键盘抬起（对应 Scene::keyReleaseEvent） */
  handleKeyUp(_event: KeyboardEvent): void {}
}
