import type Scene from './scenes/scene';

/** 输入框聚焦时按键不路由给场景（留名输入需要正常打字） */
function isTypingTarget(target: EventTarget | null): boolean {
  return target instanceof HTMLInputElement || target instanceof HTMLTextAreaElement;
}

/**
 * 导演类 —— 移植自 src/Director.h/.cpp。
 * 持有当前场景并负责切换；同时承担原版 Window 的键盘事件路由职责。
 */
export default class Director {
  private static instance: Director | null = null;

  static getInstance(root: HTMLElement): Director {
    if (!Director.instance) {
      Director.instance = new Director(root);
    }
    return Director.instance;
  }

  /** 当前响应场景 */
  nowScene: Scene | null = null;

  private constructor(public readonly root: HTMLElement) {
    // 承担原版 Window 的键盘事件路由职责：全局监听并转发给当前场景
    window.addEventListener('keydown', this.keyDownListener);
    window.addEventListener('keyup', this.keyUpListener);
  }

  private readonly keyDownListener = (event: KeyboardEvent): void => {
    this.handleKeyDown(event);
  };

  private readonly keyUpListener = (event: KeyboardEvent): void => {
    this.handleKeyUp(event);
  };

  /**
   * 切换场景：销毁旧场景，初始化新场景。
   * 对应 C++ 中 new Scene + setNowScene + init + show + deleteLater 的组合。
   */
  switchScene(next: Scene): void {
    this.nowScene?.destroy();
    this.nowScene = next;
    next.init();
  }

  /** 键盘按下路由（对应 Window::keyPressEvent） */
  handleKeyDown(event: KeyboardEvent): void {
    if (isTypingTarget(event.target)) {
      return;
    }
    this.nowScene?.handleKeyDown(event);
  }

  /** 键盘抬起路由（对应 Window::keyReleaseEvent） */
  handleKeyUp(event: KeyboardEvent): void {
    if (isTypingTarget(event.target)) {
      return;
    }
    this.nowScene?.handleKeyUp(event);
  }
}
