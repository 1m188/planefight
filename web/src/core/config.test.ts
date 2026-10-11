import { describe, expect, it } from 'vitest';
import Config from './config';

/** 测试用内存 Storage */
class FakeStorage implements Storage {
  private readonly map = new Map<string, string>();

  get length(): number {
    return this.map.size;
  }

  clear(): void {
    this.map.clear();
  }

  getItem(key: string): string | null {
    return this.map.get(key) ?? null;
  }

  key(index: number): string | null {
    return [...this.map.keys()][index] ?? null;
  }

  removeItem(key: string): void {
    this.map.delete(key);
  }

  setItem(key: string, value: string): void {
    this.map.set(key, String(value));
  }
}

describe('Config（config.ini -> localStorage 移植）', () => {
  it('无存档时保持默认值', () => {
    const config = new Config(new FakeStorage());
    config.init();
    expect(config.fps).toBe(60);
    expect(config.highestScore).toBe(0);
    expect(config.highestScorePlayer).toBe('');
  });

  it('旧存档中的 Fps 字段被忽略（网页版帧率固定为 60）', () => {
    const storage = new FakeStorage();
    storage.setItem('planefight-config', JSON.stringify({ Fps: 30, HighestScore: 7, HighestScorePlayer: '老王' }));
    const config = new Config(storage);
    config.init();
    expect(config.fps).toBe(60);
    expect(config.highestScore).toBe(7);
    expect(config.highestScorePlayer).toBe('老王');
  });

  it('保存后可完整读回（字段名与 C++ config.ini 一致）', () => {
    const storage = new FakeStorage();
    const config = new Config(storage);
    config.highestScore = 123;
    config.highestScorePlayer = '阿强';
    config.save();

    const raw = JSON.parse(storage.getItem('planefight-config') ?? '{}') as Record<string, unknown>;
    expect(raw).toEqual({ HighestScore: 123, HighestScorePlayer: '阿强' });

    const reloaded = new Config(storage);
    reloaded.init();
    expect(reloaded.highestScore).toBe(123);
    expect(reloaded.highestScorePlayer).toBe('阿强');
    expect(reloaded.fps).toBe(60);
  });

  it('存档损坏时回退默认值且不抛异常', () => {
    const storage = new FakeStorage();
    storage.setItem('planefight-config', '{broken json');
    const config = new Config(storage);
    expect(() => config.init()).not.toThrow();
    expect(config.fps).toBe(60);
    expect(config.highestScore).toBe(0);
    expect(config.highestScorePlayer).toBe('');
  });
});
