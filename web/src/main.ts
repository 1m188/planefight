import './style.css';
import Config from './core/config';
import Images from './core/images';
import Director from './director';
import GameScene from './scenes/gameScene';

/** 资源加载失败时的错误提示节点 */
function errorMessageNode(error: unknown): HTMLElement {
  const box = document.createElement('div');
  box.className = 'boot-error';
  const message = document.createElement('p');
  message.textContent = `游戏资源加载失败：${error instanceof Error ? error.message : String(error)}`;
  const retry = document.createElement('button');
  retry.type = 'button';
  retry.textContent = '重新加载';
  retry.addEventListener('click', () => window.location.reload());
  box.append(message, retry);
  return box;
}

async function main(): Promise<void> {
  // 初始化游戏数据（对应 Config::init）
  const config = Config.getInstance();
  config.init();

  const root = document.getElementById('app');
  if (!root) {
    throw new Error('找不到 #app 挂载点');
  }
  const director = Director.getInstance(root);

  // 初始化图片（对应 Image::init）
  const images = Images.getInstance();
  try {
    await images.init();
  } catch (error) {
    root.replaceChildren(errorMessageNode(error));
    return;
  }

  // 只做核心战斗：进页面直接进入游戏主场景
  director.switchScene(new GameScene(director, images, config));
}

// 预加载提示：图片加载期间给出反馈（加载完成时整个 DOM 会被场景替换）
const bootRoot = document.getElementById('app');
if (bootRoot && !bootRoot.childElementCount) {
  const loading = document.createElement('div');
  loading.className = 'boot-loading';
  loading.textContent = '正在加载飞机大战…';
  bootRoot.append(loading);
}

void main();
