# Project-2
寒假写的，补一个提交。大学写的第一个小项目，记录一下吧。
## 第三方库

- SDL2

## 文件组成

- `main.c`主文件
- `Config.h`各种常量的声明
- `Resource.c`图片，字体文件等资源统一加载，销毁
- `Data.c`输出文本信息
- `CheckCollision.c`碰撞检测
- `Plane.c,Prop.c `分别实现飞机类和道具类
- `BulletsControl.c,EnemyControl.c,PlayerControl.c`实现子弹、敌人和玩家的各种操作
- `PlaneWar.exe`
- `image`可能用到的图片素材

## 设计思路

#### 开始界面

- `Play`点击开始游戏
- `Help`出现操作和道具的解释界面

#### 玩家移动

`w,a,s,d`分别对应`前进，左移，右移，后移` 

#### 子弹

##### Player

`space`键发射子弹

- 普通
- 双排

##### Enemy

- 激光
- 快速
- 触边反弹

#### 道具

- 治疗：HP += 10
- 攻击：攻击+1
- 双排子弹
- 护盾

#### 敌机（普通）

- 射出激光
- 移动速度更快
- 左右横跳

#### Boss攻击模式

- 弹幕
- 大范围激光（HP 小于50%时触发）
