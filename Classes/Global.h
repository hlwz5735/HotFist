#ifndef _Global__
#define _Global__

#define DESKTOP_RUNTIME (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

// 重力加速度
#define GRAVITY 0.7f

// 水平方向最大速度
#define  VelocityX 5

// 竖直方向最大速度
#define  maxVelocityY 15

// 调试线框绘制标记
#define DebugDrawRects 1

constexpr float SCALE_FACTOR = 1.f;

#endif
