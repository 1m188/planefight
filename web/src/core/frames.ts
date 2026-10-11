/**
 * 帧数换算公式 —— 移植自 C++ 源码中的整数除法表达式。
 *
 * C++ 中的写法（整数运算，从左到右结合）：
 *   1000 / fps                    -> Qt 定时器间隔（毫秒）
 *   1000 / 60 * X / (1000 / fps)  -> 每隔多少帧发生一次事件
 *   S * 60 / fps                  -> 每帧行进距离（像素）
 * 这里用 Math.floor 保持与 C++ 整数除法完全一致的结果。
 */

/** Qt 定时器间隔：1000 / fps（整数除法） */
export function frameMs(fps: number): number {
  return Math.floor(1000 / fps);
}

/** 事件间隔帧数：1000 / 60 * X / (1000 / fps)（整数除法） */
export function framesInterval(x: number, fps: number): number {
  return Math.floor((Math.floor(1000 / 60) * x) / frameMs(fps));
}

/** 每帧行进距离：S * 60 / fps（整数除法） */
export function speedPerFrame(s: number, fps: number): number {
  return Math.floor((s * 60) / fps);
}
