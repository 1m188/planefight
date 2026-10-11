import type Director from '../director';
import type Config from '../core/config';
import Bullet, { BulletType } from '../core/bullet';
import Enemy, { enemyScore, EnemyType } from '../core/enemy';
import { framesInterval, speedPerFrame } from '../core/frames';
import { assetUrl as assetUrlFor } from '../core/images';
import type Images from '../core/images';
import Player from '../core/player';
import Props, { PropsType } from '../core/props';
import type Sprite from '../core/sprite';
import Scene from './scene';

/** 对应 qrand() % n：[0, n) 内的随机整数 */
function randInt(n: number): number {
  return Math.floor(Math.random() * n);
}

interface Rect {
  x: number;
  y: number;
  width: number;
  height: number;
}

/** Qt 中矩形包含点的判定 */
function rectContains(rect: Rect, x: number, y: number): boolean {
  return x >= rect.x && x < rect.x + rect.width && y >= rect.y && y < rect.y + rect.height;
}

/** Qt 微软雅黑字体族 */
const YAHEI = '"Microsoft YaHei", "微软雅黑", system-ui, sans-serif';

/** 设备像素比上限（保证 4K/高清屏清晰的同时控制渲染开销） */
const MAX_DPR = 2;

/**
 * 游戏场景 —— 移植自 src/GameScene.h/.cpp。
 * 用 requestAnimationFrame + 固定步长累加器模拟 Qt 的 QTimer
 * （间隔 1000 / fps），逐帧计帧逻辑与 C++ 完全一致。
 *
 * 网页版适配：canvas 占满整个浏览器视口（无滚动条、一屏显示），
 * 游戏场地尺寸跟随窗口并实时响应 resize；
 * 背景图等比例缩放至一边贴住画布，另一边用多张拼接铺满。
 */
export default class GameScene extends Scene {
  private readonly images: Images;
  private readonly config: Config;

  private readonly stage = document.createElement('div');
  private canvas!: HTMLCanvasElement;
  private ctx!: CanvasRenderingContext2D;

  // 游戏结束覆盖层
  private overlay!: HTMLDivElement;
  private overlayText!: HTMLDivElement;
  private recordInfo!: HTMLDivElement;
  private recordLabel!: HTMLLabelElement;
  private recordForm!: HTMLFormElement;
  private nameInput!: HTMLInputElement;
  private againButton!: HTMLImageElement;

  /** 场地尺寸 = 浏览器视口尺寸（跟随窗口实时变化） */
  private width = 0;
  private height = 0;

  // 实体
  private readonly player = new Player();
  private playerBullets: Bullet[] = [];
  private enemies: Enemy[] = [];
  private enemyBullets: Bullet[] = [];
  private props: Props[] = [];

  // 敌机产生计帧器 / 间隔
  private productEnemyFpsCounter = 0;
  private productEnemyFpsInterval = 0;

  // 道具产生计帧器 / 间隔
  private productPropsFpsCounter = 0;
  private productPropsFpsInterval = 0;

  // 弹药补给计帧器 / 持续帧数
  private bulletPropsLastFpsCounter = 0;
  private bulletPropsLastFps = 0;

  /** 当前分数 */
  private score = 0;

  /** 帧数 */
  private fps = 60;

  /** 背景等比缩放后的单张尺寸（等比缩放至一边贴住画布，另一边不足时平铺拼接） */
  private backgroundTileWidth = 0;
  private backgroundTileHeight = 0;

  // 暂停相关
  private isPause = false;
  private pauseResumeImage!: HTMLImageElement;
  private pauseResumeRect: Rect = { x: 0, y: 0, width: 0, height: 0 };
  private originalPoint = { x: 0, y: 0 };
  private mousePressed = false;

  // 游戏结束
  private isGameOver = false;

  // 游戏循环
  private rafId = 0;
  private lastTime = 0;
  private accumulator = 0;

  constructor(director: Director, images: Images, config: Config) {
    super(director);
    this.images = images;
    this.config = config;
  }

  /** 初始化游戏场景 —— 对应 GameScene::init */
  override init(): void {
    this.fps = this.config.fps;
    this.score = 0;
    this.isPause = false;
    this.isGameOver = false;
    this.mousePressed = false;
    this.playerBullets = [];
    this.enemies = [];
    this.enemyBullets = [];
    this.props = [];

    this.stage.className = 'game-stage';
    this.canvas = document.createElement('canvas');
    this.canvas.className = 'game-canvas';
    this.overlay = this.buildGameOverOverlay();
    this.stage.append(this.canvas, this.overlay);
    this.director.root.replaceChildren(this.stage);
    this.ctx = this.canvas.getContext('2d') as CanvasRenderingContext2D;
    this.applyCanvasSize();

    // 初始化玩家飞机（底部居中）
    const player = this.player;
    player.normalImages = this.images.playerNormalImages;
    player.destroyImages = this.images.playerDestroyImages;
    player.imageChangeFpsInterval = framesInterval(13, this.fps);
    player.productBulletFpsInterval = framesInterval(13, this.fps);
    player.image = player.normalImages[0];
    player.width = player.image.width;
    player.height = player.image.height;
    player.x = this.width / 2 - player.width / 2;
    player.y = this.height - player.height;
    player.dx = speedPerFrame(10, this.fps);
    player.dy = speedPerFrame(10, this.fps);
    player.life = 1;
    player.bombNum = 1;
    player.isStrengthenFire = false;
    player.isUping = player.isDowning = player.isLefting = player.isRighting = false;
    player.nowNormalImageIndex = 0;
    player.nowDestroyImageIndex = 0;
    player.normalImageChangeFpsCounter = 0;
    player.destroyImageChangeFpsCounter = 0;
    player.productBulletFpsCounter = 0;

    // 初始化敌机产生
    this.productEnemyFpsCounter = 0;
    this.productEnemyFpsInterval = framesInterval(100, this.fps);

    // 初始化道具产生
    this.productPropsFpsCounter = 0;
    this.productPropsFpsInterval = framesInterval(1000, this.fps);

    // 初始化弹药补给的持续
    this.bulletPropsLastFpsCounter = 0;
    this.bulletPropsLastFps = framesInterval(700, this.fps);

    // 暂停/继续按钮（右上角）
    const pauseNor = this.images.get('pauseNor');
    this.pauseResumeImage = pauseNor;
    this.pauseResumeRect = {
      x: this.width - pauseNor.width,
      y: 0,
      width: pauseNor.width,
      height: pauseNor.height,
    };

    // 事件绑定
    window.addEventListener('blur', this.onBlur);
    window.addEventListener('resize', this.onResize);
    this.canvas.addEventListener('mousedown', this.onMouseDown);
    window.addEventListener('mousemove', this.onMouseMove);
    window.addEventListener('mouseup', this.onMouseUp);
    this.againButton.addEventListener('click', this.onAgainClicked);

    // 启动游戏循环
    this.lastTime = 0;
    this.accumulator = 0;
    this.rafId = requestAnimationFrame(this.tick);

    // 调试/自动化测试钩子：暴露场景实例便于验证核心状态
    (window as unknown as Record<string, unknown>).__PLANEFIGHT_SCENE = this;
  }

  /** 销毁场景 —— 停止循环、解绑事件、卸载 DOM */
  override destroy(): void {
    cancelAnimationFrame(this.rafId);
    window.removeEventListener('blur', this.onBlur);
    window.removeEventListener('resize', this.onResize);
    this.canvas.removeEventListener('mousedown', this.onMouseDown);
    window.removeEventListener('mousemove', this.onMouseMove);
    window.removeEventListener('mouseup', this.onMouseUp);
    this.againButton.removeEventListener('click', this.onAgainClicked);
    delete (window as unknown as Record<string, unknown>).__PLANEFIGHT_SCENE;
    this.director.root.replaceChildren();
  }

  /**
   * 画布尺寸适配：
   * canvas 占满整个浏览器视口（CSS 尺寸 = 窗口内尺寸，无滚动条一屏显示），
   * 物理分辨率按设备像素比设置保证高清；同时更新场地尺寸、
   * 背景平铺参数、暂停按钮位置，并把玩家夹回新的边界内。
   */
  private applyCanvasSize(): void {
    this.width = window.innerWidth;
    this.height = window.innerHeight;

    const dpr = Math.min(window.devicePixelRatio || 1, MAX_DPR);
    this.canvas.style.width = `${this.width}px`;
    this.canvas.style.height = `${this.height}px`;
    this.canvas.width = Math.round(this.width * dpr);
    this.canvas.height = Math.round(this.height * dpr);
    this.ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
    this.ctx.imageSmoothingEnabled = true;

    // 背景平铺参数：等比例缩放至其中一边恰好贴住画布，
    // 另一边若未能覆盖画布，则用多张拼接铺满（不变形地铺满整个屏幕）
    const background = this.images.get('background');
    const backgroundScale = Math.min(
      this.width / background.width,
      this.height / background.height,
    );
    this.backgroundTileWidth = background.width * backgroundScale;
    this.backgroundTileHeight = background.height * backgroundScale;

    // 暂停按钮保持在右上角
    const pauseNor = this.images.get('pauseNor');
    this.pauseResumeRect = {
      x: this.width - pauseNor.width,
      y: 0,
      width: pauseNor.width,
      height: pauseNor.height,
    };

    // 窗口变小时把玩家夹回新的边界内
    const player = this.player;
    if (player.width > 0 && player.height > 0) {
      if (player.x > this.width - player.width) player.x = this.width - player.width;
      if (player.x < 0) player.x = 0;
      if (player.y > this.height - player.height) player.y = this.height - player.height;
      if (player.y < 0) player.y = 0;
    }

    this.updateOverlayLayout();
  }

  /** 窗口尺寸变化时重新适配画布 */
  private readonly onResize = (): void => {
    this.applyCanvasSize();
  };

  /** 按当前画布 CSS 高度更新游戏结束覆盖层的排版（对应原版 1/3 屏高处） */
  private updateOverlayLayout(): void {
    const rect = this.canvas.getBoundingClientRect();
    this.overlay.style.paddingTop = `${Math.floor(rect.height / 3)}px`;
  }

  /** 构建游戏结束覆盖层（对应游戏结束时的绘制与 QInputDialog 留名流程） */
  private buildGameOverOverlay(): HTMLDivElement {
    const overlay = document.createElement('div');
    overlay.className = 'gameover-overlay';

    this.overlayText = document.createElement('div');
    this.overlayText.className = 'gameover-text';
    this.overlayText.textContent = '胜败乃兵家常事\n大侠请重新来过';

    // 最高分信息
    this.recordInfo = document.createElement('div');
    this.recordInfo.className = 'gameover-record';

    // 破纪录留名（对应 QInputDialog::getText，名字不能为空）
    this.recordForm = document.createElement('form');
    this.recordForm.className = 'record-form';
    this.recordForm.style.display = 'none';
    this.recordLabel = document.createElement('label');
    this.recordLabel.className = 'record-label';
    this.nameInput = document.createElement('input');
    this.nameInput.className = 'record-input';
    this.nameInput.type = 'text';
    this.nameInput.maxLength = 12;
    this.nameInput.placeholder = '留下你的大名';
    this.nameInput.autocomplete = 'off';
    const submitButton = document.createElement('button');
    submitButton.type = 'submit';
    submitButton.textContent = '确  定';
    this.recordForm.append(this.recordLabel, this.nameInput, submitButton);
    this.recordForm.addEventListener('submit', this.onRecordSubmit);

    // 再来一次
    this.againButton = document.createElement('img');
    this.againButton.className = 'again-button';
    this.againButton.src = assetUrlFor('again.png');
    this.againButton.alt = '再来一次';
    this.againButton.draggable = false;

    overlay.append(this.overlayText, this.recordInfo, this.recordForm, this.againButton);
    return overlay;
  }

  /** 提交留名 —— 名字为空时不保存（对应 C++ 中的 while 循环直到输入非空） */
  private readonly onRecordSubmit = (event: Event): void => {
    event.preventDefault();
    const name = this.nameInput.value.trim();
    if (!name) {
      return;
    }
    this.config.highestScorePlayer = name;
    this.config.save();
    this.recordForm.style.display = 'none';
    this.againButton.style.display = '';
  };

  /** 再来一次 —— 对应 mouseReleaseEvent 中 againRect 命中后的场景重建 */
  private readonly onAgainClicked = (): void => {
    this.director.switchScene(new GameScene(this.director, this.images, this.config));
  };

  /** 窗口失焦时清空按键状态，防止切走后键位卡住（Web 适配） */
  private readonly onBlur = (): void => {
    const player = this.player;
    player.isUping = false;
    player.isDowning = false;
    player.isLefting = false;
    player.isRighting = false;
    this.mousePressed = false;
  };

  /** 客户端坐标 -> 画布坐标 */
  private toCanvasPoint(event: MouseEvent): { x: number; y: number } {
    const rect = this.canvas.getBoundingClientRect();
    return {
      x: ((event.clientX - rect.left) / rect.width) * this.width,
      y: ((event.clientY - rect.top) / rect.height) * this.height,
    };
  }

  /** 鼠标按下 —— 对应 GameScene::mousePressEvent */
  private readonly onMouseDown = (event: MouseEvent): void => {
    const pos = this.toCanvasPoint(event);
    this.originalPoint = pos;
    this.mousePressed = true;
    if (this.player.life > 0 && rectContains(this.pauseResumeRect, pos.x, pos.y)) {
      this.pauseResumeImage = this.isPause
        ? this.images.get('resumePressed')
        : this.images.get('pausePressed');
    }
  };

  /** 鼠标按住移动 —— 对应 GameScene::mouseMoveEvent（Qt 未开启追踪，仅按住时触发） */
  private readonly onMouseMove = (event: MouseEvent): void => {
    if (!this.mousePressed || this.player.life <= 0) {
      return;
    }
    if (!rectContains(this.pauseResumeRect, this.originalPoint.x, this.originalPoint.y)) {
      return;
    }
    const pos = this.toCanvasPoint(event);
    const inside = rectContains(this.pauseResumeRect, pos.x, pos.y);
    this.pauseResumeImage = inside
      ? this.isPause
        ? this.images.get('resumePressed')
        : this.images.get('pausePressed')
      : this.isPause
        ? this.images.get('resumeNor')
        : this.images.get('pauseNor');
  };

  /** 鼠标释放 —— 对应 GameScene::mouseReleaseEvent */
  private readonly onMouseUp = (event: MouseEvent): void => {
    if (!this.mousePressed) {
      return;
    }
    this.mousePressed = false;
    const pos = this.toCanvasPoint(event);
    if (this.player.life > 0) {
      // 从暂停/继续按钮处释放且按下处也在按钮内才切换
      if (
        rectContains(this.pauseResumeRect, pos.x, pos.y) &&
        rectContains(this.pauseResumeRect, this.originalPoint.x, this.originalPoint.y)
      ) {
        this.pauseResumeImage = this.isPause
          ? this.images.get('pauseNor')
          : this.images.get('resumeNor');
        this.isPause = !this.isPause;
      }
    }
  };

  /** 键盘按下 —— 对应 GameScene::keyPressEvent */
  override handleKeyDown(event: KeyboardEvent): void {
    if (event.repeat) {
      return; // 对应 isAutoRepeat 过滤
    }
    switch (event.code) {
      case 'KeyW':
        event.preventDefault();
        this.player.isUping = true;
        break;
      case 'KeyS':
        event.preventDefault();
        this.player.isDowning = true;
        break;
      case 'KeyA':
        event.preventDefault();
        this.player.isLefting = true;
        break;
      case 'KeyD':
        event.preventDefault();
        this.player.isRighting = true;
        break;
      case 'KeyB':
        // 使用炸弹，全图轰炸（与 C++ 一致，不检查暂停状态）
        event.preventDefault();
        this.useBomb();
        break;
    }
  }

  /** 键盘抬起 —— 对应 GameScene::keyReleaseEvent */
  override handleKeyUp(event: KeyboardEvent): void {
    switch (event.code) {
      case 'KeyW':
        this.player.isUping = false;
        break;
      case 'KeyS':
        this.player.isDowning = false;
        break;
      case 'KeyA':
        this.player.isLefting = false;
        break;
      case 'KeyD':
        this.player.isRighting = false;
        break;
    }
  }

  /** 使用炸弹：清空全部敌机并按种类计分 */
  private useBomb(): void {
    if (this.player.bombNum > 0) {
      this.player.bombNum--;
      for (const enemy of this.enemies) {
        enemy.life = 0;
        this.score += enemyScore(enemy);
      }
    }
  }

  /** 获取分数（敌机阵亡时按种类计分） */
  private getScore(enemy: Enemy): number {
    return enemyScore(enemy);
  }

  /** 游戏循环 —— 对应 gameCycleSlot：没有暂停且没有结束时才计算状态，每帧都重绘 */
  private readonly tick = (time: number): void => {
    this.rafId = requestAnimationFrame(this.tick);

    if (this.lastTime === 0) {
      this.lastTime = time;
    }
    let delta = time - this.lastTime;
    this.lastTime = time;
    // 切后台保护：离开久了回来不疯狂补帧
    if (delta > 250) {
      delta = 250;
    }
    this.accumulator += delta;

    // 逻辑步长取精确的 1000 / fps（60fps 时恰为 16.67ms）：
    // Qt 的 QTimer 用整数毫秒（16ms -> 实际 62.5Hz），网页版取精确值，
    // 在 60Hz 显示器上逻辑帧与刷新率恰好 1:1，运动最平滑。
    const stepMs = 1000 / this.fps;
    while (this.accumulator >= stepMs) {
      this.accumulator -= stepMs;
      this.step();
    }

    this.draw();
  };

  /** 一次固定步长的状态计算 —— 对应 gameCycleSlot 的计算部分 */
  private step(): void {
    if (!this.isPause && !this.isGameOver) {
      this.updatePlayer();
      // 玩家损毁动画播完触发的这一帧直接返回（对应 C++ 的 return）
      if (!this.isGameOver) {
        this.updateEnemies();
        this.updatePlayerBullets();
        this.updateEnemyBullets();
        this.updateProps();
      }
    }
  }

  /** 计算玩家状态 */
  private updatePlayer(): void {
    const player = this.player;
    // 玩家存活
    if (player.life > 0) {
      // 移动
      player.move(0, this.height, 0, this.width);

      // 开火（网页版适配：自动开火，无需按键；计帧节奏与原版按住 J 时一致）
      player.productBulletFpsCounter++;
      if (player.productBulletFpsCounter === player.productBulletFpsInterval) {
        player.productBulletFpsCounter = 0;
        const bulletImage = this.images.get('playerBullet');
        // 中央子弹（对应 bullet.rx/ry 的设置）
        this.spawnPlayerBullet(
          player.x + Math.floor(player.width / 2) - Math.floor(bulletImage.width / 2),
          player.y,
        );

        // 火力加强：额外左右两发
        if (player.isStrengthenFire) {
          this.bulletPropsLastFpsCounter++;
          if (
            this.bulletPropsLastFpsCounter ===
            Math.floor(this.bulletPropsLastFps / player.productBulletFpsInterval)
          ) {
            this.bulletPropsLastFpsCounter = 0;
            player.isStrengthenFire = false;
          }

          this.spawnPlayerBullet(player.x + Math.floor(player.width / 6), player.y);
          this.spawnPlayerBullet(
            player.x + player.width - Math.floor(player.width / 6),
            player.y,
          );
        }
      }

      // 切换常态图片
      player.changeImage();

      // 如果撞上敌机：同归于尽
      for (const enemy of this.enemies) {
        if (player.isCollided(enemy) && enemy.life > 0) {
          player.life = 0;
          enemy.life = 0;
          this.score += this.getScore(enemy);
        }
      }

      // 如果撞上道具
      for (let i = 0; i < this.props.length; i++) {
        const props = this.props[i];
        if (player.isCollided(props)) {
          if (props.type === PropsType.Bomb) {
            player.bombNum++;
          } else if (props.type === PropsType.Bullet) {
            player.isStrengthenFire = true;
          }
          this.props.splice(i, 1);
          i--;
        }
      }
    }
    // 否则显示损毁过程
    else {
      if (!player.changeImage()) {
        // 游戏结束
        this.isGameOver = true;

        // 如果是最高分
        if (this.score > this.config.highestScore) {
          this.config.highestScore = this.score;
          this.config.save();
          this.showGameOverOverlay(true);
        } else {
          this.showGameOverOverlay(false);
        }
        return;
      }
    }
  }

  /** 产生一颗玩家子弹 */
  private spawnPlayerBullet(x: number, y: number): void {
    const image = this.images.get('playerBullet');
    const bullet = new Bullet();
    bullet.type = BulletType.Player;
    bullet.image = image;
    bullet.width = image.width;
    bullet.height = image.height;
    bullet.x = x;
    bullet.y = y;
    bullet.dy = speedPerFrame(10, this.fps);
    this.playerBullets.push(bullet);
  }

  /** 计算敌机状态：产生 + 移动 + 开火 + 动画 */
  private updateEnemies(): void {
    // 敌机产生
    this.productEnemyFpsCounter++;
    if (this.productEnemyFpsCounter === this.productEnemyFpsInterval) {
      this.productEnemyFpsCounter = 0;
      this.spawnEnemy();
    }

    for (let i = 0; i < this.enemies.length; i++) {
      const enemy = this.enemies[i];

      // 如果敌机活着
      if (enemy.life > 0) {
        // 移动，超出地图下边界则移除
        if (!enemy.move(this.height)) {
          this.enemies.splice(i, 1);
          i--;
          continue;
        }

        // 开火
        enemy.productBulletFpsCounter++;
        if (enemy.productBulletFpsCounter === enemy.productBulletFpsInterval) {
          enemy.productBulletFpsCounter = 0;
          this.spawnEnemyBullet(enemy);
        }

        // 切换常态图片
        enemy.changeImage();
      }
      // 否则展示损毁图片，展示完了之后移除
      else {
        if (!enemy.changeImage()) {
          this.enemies.splice(i, 1);
          i--;
        }
      }
    }
  }

  /** 产生一架敌机（按 9:3:1 随机出 士兵/领导/将军） */
  private spawnEnemy(): void {
    const enemyIndex = randInt(13); // 对应 qrand() % 13

    const enemy = new Enemy();
    if (enemyIndex <= 8) {
      // 士兵（第一类敌机）
      enemy.type = EnemyType.Soldier;
      enemy.normalImages = this.images.enemy1NormalImages;
      enemy.destroyImages = this.images.enemy1DestroyImages;
      enemy.productBulletFpsInterval = framesInterval(50, this.fps);
      enemy.dy = speedPerFrame(3, this.fps);
    } else if (enemyIndex <= 11) {
      // 领导（第二类敌机）
      enemy.type = EnemyType.Leader;
      enemy.normalImages = this.images.enemy2NormalImages;
      enemy.destroyImages = this.images.enemy2DestroyImages;
      enemy.productBulletFpsInterval = framesInterval(45, this.fps);
      enemy.dy = speedPerFrame(2, this.fps);
      enemy.life = 6;
    } else {
      // 将军（第三类敌机）
      enemy.type = EnemyType.General;
      enemy.normalImages = this.images.enemy3NormalImages;
      enemy.destroyImages = this.images.enemy3DestroyImages;
      enemy.productBulletFpsInterval = framesInterval(40, this.fps);
      enemy.dy = speedPerFrame(1, this.fps);
      enemy.life = 16;
    }
    enemy.imageChangeFpsInterval = framesInterval(13, this.fps);
    enemy.image = enemy.normalImages[0];
    enemy.width = enemy.image.width;
    enemy.height = enemy.image.height;
    enemy.x = randInt(this.width - enemy.width + 1);
    enemy.y = -enemy.height;

    this.enemies.push(enemy);
  }

  /** 产生一颗敌机子弹 */
  private spawnEnemyBullet(enemy: Enemy): void {
    const image = this.images.get('enemyBullet');
    const bullet = new Bullet();
    bullet.type = BulletType.Enemy;
    bullet.image = image;
    bullet.width = image.width;
    bullet.height = image.height;
    bullet.x = enemy.x + Math.floor(enemy.width / 2) - Math.floor(bullet.width / 2);
    bullet.y = enemy.y + enemy.height;
    bullet.dy = speedPerFrame(5, this.fps);
    this.enemyBullets.push(bullet);
  }

  /** 计算玩家子弹：移动、越界移除、命中敌机 */
  private updatePlayerBullets(): void {
    for (let i = 0; i < this.playerBullets.length; i++) {
      const bullet = this.playerBullets[i];
      // 子弹移动，超出地图上边界则移除
      if (!bullet.move(0)) {
        this.playerBullets.splice(i, 1);
        i--;
        continue;
      }

      // 判断是否撞到了存活敌机
      for (const enemy of this.enemies) {
        if (bullet.isCollided(enemy) && enemy.life > 0) {
          // 敌机生命值扣减
          enemy.life--;
          // 获取分数
          this.score += this.getScore(enemy);
          // 受击换图：领导血量 <= 4、将军血量 <= 8 时切换到受击态
          // （用图片身份比较对应 C++ 中的 cacheKey 比较）
          if (
            enemy.life <= 4 &&
            enemy.normalImages[0] === this.images.enemy2NormalImages[0]
          ) {
            enemy.normalImages = this.images.enemy2HitImages;
            enemy.nowNormalImageIndex = 0;
          } else if (
            enemy.life <= 8 &&
            enemy.normalImages[0] === this.images.enemy3NormalImages[0]
          ) {
            enemy.normalImages = this.images.enemy3HitImages;
            enemy.nowNormalImageIndex = 0;
          }
          // 子弹删除
          this.playerBullets.splice(i, 1);
          i--;
          break;
        }
      }
    }
  }

  /** 计算敌机子弹：移动、越界移除、命中玩家 */
  private updateEnemyBullets(): void {
    for (let i = 0; i < this.enemyBullets.length; i++) {
      const bullet = this.enemyBullets[i];
      // 移动，超出地图下边界则移除
      if (!bullet.move(this.height)) {
        this.enemyBullets.splice(i, 1);
        i--;
      }
      // 否则判断是否打到了玩家飞机
      else {
        if (bullet.isCollided(this.player) && this.player.life > 0) {
          this.player.life--;
          this.enemyBullets.splice(i, 1);
          i--;
        }
      }
    }
  }

  /** 计算道具：产生 + 移动 */
  private updateProps(): void {
    // 道具产生
    this.productPropsFpsCounter++;
    if (this.productPropsFpsCounter === this.productPropsFpsInterval) {
      this.productPropsFpsCounter = 0;

      const props = new Props();
      props.type = (randInt(2) + 1) as PropsType; // 对应 qrand() % 2 + 1
      const image =
        props.type === PropsType.Bomb
          ? this.images.get('bombProps')
          : this.images.get('bulletProps');
      props.image = image;
      props.width = image.width;
      props.height = image.height;
      props.x = randInt(this.width - props.width + 1);
      props.y = -props.height;
      props.dy = speedPerFrame(3, this.fps);
      this.props.push(props);
    }

    // 道具移动，超出下边界移除
    for (let i = 0; i < this.props.length; i++) {
      const props = this.props[i];
      props.y += props.dy;
      if (props.y >= this.height) {
        this.props.splice(i, 1);
        i--;
      }
    }
  }

  /** 游戏结束覆盖层展示（isNewRecord 时先留名，再显示再来一次按钮） */
  private showGameOverOverlay(isNewRecord: boolean): void {
    this.updateOverlayLayout();
    this.recordInfo.textContent = isNewRecord
      ? `新纪录！${this.score} 分`
      : `${this.highestScoreText()}　·　本局 ${this.score} 分`;
    this.recordLabel.textContent = `游戏结束了，你的分数是${this.score}，为最高分！请在这里留下你的大名`;
    this.overlay.classList.add('visible');
    if (isNewRecord) {
      this.recordForm.style.display = 'flex';
      this.againButton.style.display = 'none';
      this.nameInput.value = '';
      this.nameInput.focus();
    } else {
      this.recordForm.style.display = 'none';
      this.againButton.style.display = '';
    }
  }

  /** 绘制精灵 */
  private drawSprite(sprite: Sprite): void {
    if (sprite.image) {
      this.ctx.drawImage(sprite.image, sprite.x, sprite.y, sprite.width, sprite.height);
    }
  }

  /** 绘制游戏画面 —— 对应 GameScene::paintEvent */
  private draw(): void {
    const ctx = this.ctx;
    const width = this.width;
    const height = this.height;

    // 绘制背景：等比例缩放，其中一边恰好贴住画布，
    // 另一边未覆盖的部分用多张图片拼接补满（不变形地铺满整个屏幕）
    const background = this.images.get('background');
    const cols = Math.ceil(width / this.backgroundTileWidth);
    const rows = Math.ceil(height / this.backgroundTileHeight);
    for (let row = 0; row < rows; row++) {
      for (let col = 0; col < cols; col++) {
        ctx.drawImage(
          background,
          col * this.backgroundTileWidth,
          row * this.backgroundTileHeight,
          this.backgroundTileWidth,
          this.backgroundTileHeight,
        );
      }
    }

    // 绘制玩家
    this.drawSprite(this.player);

    // 绘制敌机
    for (const enemy of this.enemies) {
      this.drawSprite(enemy);
    }

    // 绘制玩家子弹
    for (const bullet of this.playerBullets) {
      this.drawSprite(bullet);
    }

    // 绘制敌机子弹
    for (const bullet of this.enemyBullets) {
      this.drawSprite(bullet);
    }

    // 绘制道具
    for (const props of this.props) {
      this.drawSprite(props);
    }

    // 绘制暂停/继续按钮
    const pr = this.pauseResumeRect;
    ctx.drawImage(this.pauseResumeImage, pr.x, pr.y, pr.width, pr.height);

    // 绘制生命
    const life = this.images.get('life');
    ctx.drawImage(life, 0, height - life.height, life.width, life.height);
    ctx.fillStyle = '#000';
    ctx.textAlign = 'center';
    ctx.textBaseline = 'middle';
    ctx.font = `300 33px ${YAHEI}`;
    ctx.fillText(
      String(this.player.life),
      life.width + life.width / 2,
      height - life.height + life.height / 2,
    );

    // 绘制炸弹数目
    const bomb = this.images.get('bomb');
    ctx.drawImage(bomb, width - bomb.width * 2, height - bomb.height, bomb.width, bomb.height);
    ctx.fillText(
      String(this.player.bombNum),
      width - bomb.width + bomb.width / 2,
      height - bomb.height + bomb.height / 2,
    );

    // 绘制分数
    ctx.font = `300 20px ${YAHEI}`;
    ctx.fillText(`分数：${this.score}`, 60, 25);

    // 绘制操作说明与最高分（网页版适配：常驻提示，避免不知道怎么操作）
    ctx.fillStyle = 'rgba(0, 0, 0, 0.55)';
    ctx.font = `300 16px ${YAHEI}`;
    ctx.fillText('WASD 移动　·　B 炸弹　·　点击右上角暂停', width / 2, 20);
    ctx.fillText(this.highestScoreText(), width / 2, 42);
  }

  /** 最高分展示文本 */
  private highestScoreText(): string {
    const name = this.config.highestScorePlayer;
    return `最高分：${this.config.highestScore}${name ? `（${name}）` : ''}`;
  }
}
