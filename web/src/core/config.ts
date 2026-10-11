/** localStorage 存储键（对应 C++ 的 config.ini） */
const STORAGE_KEY = 'planefight-config';

/** 读取浏览器 localStorage；不可用（隐私模式等）时返回 null */
function safeLocalStorage(): Storage | null {
  try {
    if (typeof window === 'undefined' || !window.localStorage) {
      return null;
    }
    return window.localStorage;
  } catch {
    return null;
  }
}

/**
 * 设置类 —— 移植自 src/Config.h/.cpp。
 * 最高分、最高分保持者；config.ini 文件换成 localStorage 中的 JSON，
 * 字段名（HighestScore / HighestScorePlayer）与 C++ 保持一致。
 * （网页版适配：没有帧数设置界面，帧率固定为原版设置上限 60，
 *   不再读写存档中的 Fps 字段，避免旧存档把帧率钉在 30。）
 */
export default class Config {
  private static instance: Config | null = null;

  static getInstance(): Config {
    if (!Config.instance) {
      Config.instance = new Config();
    }
    return Config.instance;
  }

  /** 帧数（网页版固定 60；原版默认 30，可在设置中调 30 ~ 60） */
  fps = 60;
  /** 最高分 */
  highestScore = 0;
  /** 最高分保持者 */
  highestScorePlayer = '';

  private readonly storage: Storage | null;

  constructor(storage: Storage | null = safeLocalStorage()) {
    this.storage = storage;
  }

  /** 初始化：存在存档则读取，等价于 Config::init */
  init(): void {
    const raw = this.storage?.getItem(STORAGE_KEY);
    if (raw == null) {
      return;
    }
    try {
      const json = JSON.parse(raw) as Record<string, unknown>;
      if (typeof json.HighestScore === 'number') {
        this.highestScore = json.HighestScore;
      }
      if (typeof json.HighestScorePlayer === 'string') {
        this.highestScorePlayer = json.HighestScorePlayer;
      }
    } catch {
      // 存档损坏时保持默认值
    }
  }

  /** 保存数据，等价于 Config::uninit */
  save(): void {
    if (!this.storage) {
      return;
    }
    try {
      this.storage.setItem(
        STORAGE_KEY,
        JSON.stringify({
          HighestScore: this.highestScore,
          HighestScorePlayer: this.highestScorePlayer,
        }),
      );
    } catch {
      // 写入失败（如隐私模式）时静默忽略
    }
  }
}
