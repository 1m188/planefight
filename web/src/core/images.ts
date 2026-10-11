/** 静态资源目录下图片的访问地址（开发与构建产物均可用） */
export function assetUrl(name: string): string {
  return `${import.meta.env.BASE_URL}asset/${name}`;
}

/** 加载单张图片 */
function loadImage(name: string): Promise<HTMLImageElement> {
  return new Promise((resolve, reject) => {
    const image = new window.Image();
    image.onload = () => resolve(image);
    image.onerror = () => reject(new Error(`加载图片失败: ${name}`));
    image.src = assetUrl(name);
  });
}

/** 全部单张图片清单 */
const FILES = {
  background: 'background.png',
  again: 'again.png',
  gameOver: 'gameover.png',
  pauseNor: 'pause_nor.png',
  pausePressed: 'pause_pressed.png',
  resumeNor: 'resume_nor.png',
  resumePressed: 'resume_pressed.png',
  playerBullet: 'bullet1.png',
  enemyBullet: 'bullet2.png',
  life: 'life.png',
  bomb: 'bomb.png',
  bombProps: 'bomb_supply.png',
  bulletProps: 'bullet_supply.png',
  me1: 'me1.png',
  me2: 'me2.png',
  meDestroy1: 'me_destroy_1.png',
  meDestroy2: 'me_destroy_2.png',
  meDestroy3: 'me_destroy_3.png',
  meDestroy4: 'me_destroy_4.png',
  enemy1: 'enemy1.png',
  enemy1Down1: 'enemy1_down1.png',
  enemy1Down2: 'enemy1_down2.png',
  enemy1Down3: 'enemy1_down3.png',
  enemy1Down4: 'enemy1_down4.png',
  enemy2: 'enemy2.png',
  enemy2Down1: 'enemy2_down1.png',
  enemy2Down2: 'enemy2_down2.png',
  enemy2Down3: 'enemy2_down3.png',
  enemy2Down4: 'enemy2_down4.png',
  enemy2Hit: 'enemy2_hit.png',
  enemy3N1: 'enemy3_n1.png',
  enemy3N2: 'enemy3_n2.png',
  enemy3Down1: 'enemy3_down1.png',
  enemy3Down2: 'enemy3_down2.png',
  enemy3Down3: 'enemy3_down3.png',
  enemy3Down4: 'enemy3_down4.png',
  enemy3Down5: 'enemy3_down5.png',
  enemy3Down6: 'enemy3_down6.png',
  enemy3Hit: 'enemy3_hit.png',
} as const;

type ImageKey = keyof typeof FILES;

/**
 * 图片类 —— 移植自 src/Image.h/.cpp。
 * 提前把全部游戏图片加载进内存，失败则整体报错。
 */
export default class Images {
  private static instance: Images | null = null;

  static getInstance(): Images {
    if (!Images.instance) {
      Images.instance = new Images();
    }
    return Images.instance;
  }

  private readonly map = new Map<ImageKey, HTMLImageElement>();

  /** 玩家常态/损毁图片 */
  playerNormalImages: HTMLImageElement[] = [];
  playerDestroyImages: HTMLImageElement[] = [];

  /** 敌机1（士兵）常态/损毁图片 */
  enemy1NormalImages: HTMLImageElement[] = [];
  enemy1DestroyImages: HTMLImageElement[] = [];

  /** 敌机2（领导）常态/损毁/受击图片 */
  enemy2NormalImages: HTMLImageElement[] = [];
  enemy2DestroyImages: HTMLImageElement[] = [];
  enemy2HitImages: HTMLImageElement[] = [];

  /** 敌机3（将军）常态/损毁/受击图片 */
  enemy3NormalImages: HTMLImageElement[] = [];
  enemy3DestroyImages: HTMLImageElement[] = [];
  enemy3HitImages: HTMLImageElement[] = [];

  /** 是否已完成加载 */
  private loaded = false;

  /** 按清单取单张图片 */
  get(key: ImageKey): HTMLImageElement {
    const image = this.map.get(key);
    if (!image) {
      throw new Error(`图片尚未加载: ${key}`);
    }
    return image;
  }

  /** 并行加载全部图片并组装图片数组 */
  async init(): Promise<void> {
    if (this.loaded) {
      return;
    }
    const keys = Object.keys(FILES) as ImageKey[];
    await Promise.all(
      keys.map(async (key) => {
        this.map.set(key, await loadImage(FILES[key]));
      }),
    );

    this.playerNormalImages = [this.get('me1'), this.get('me2')];
    this.playerDestroyImages = [
      this.get('meDestroy1'),
      this.get('meDestroy2'),
      this.get('meDestroy3'),
      this.get('meDestroy4'),
    ];

    this.enemy1NormalImages = [this.get('enemy1')];
    this.enemy1DestroyImages = [
      this.get('enemy1Down1'),
      this.get('enemy1Down2'),
      this.get('enemy1Down3'),
      this.get('enemy1Down4'),
    ];

    this.enemy2NormalImages = [this.get('enemy2')];
    this.enemy2DestroyImages = [
      this.get('enemy2Down1'),
      this.get('enemy2Down2'),
      this.get('enemy2Down3'),
      this.get('enemy2Down4'),
    ];
    this.enemy2HitImages = [this.get('enemy2Hit')];

    this.enemy3NormalImages = [this.get('enemy3N1'), this.get('enemy3N2')];
    this.enemy3DestroyImages = [
      this.get('enemy3Down1'),
      this.get('enemy3Down2'),
      this.get('enemy3Down3'),
      this.get('enemy3Down4'),
      this.get('enemy3Down5'),
      this.get('enemy3Down6'),
    ];
    this.enemy3HitImages = [this.get('enemy3Hit')];

    this.loaded = true;
  }
}
