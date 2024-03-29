/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#define USE_AUDIO_ENGINE 1

#include "AppDelegate.h"
#include "Global.h"
#include "InputManager.h"
#include "audio/AudioEngine.h"
#include "scenes/DebugTitleScene.h"

USING_NS_AX;

/** 设计分辨率 */
static Size designResolutionSize = Size(640, 360);

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
    AudioEngine::end();
    Director::destroyInstance();
    InputManager::destroyInstance();
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs() {
    // set OpenGL context attributes: red, green, blue, alpha, depth, stencil, multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages() {
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getGLView();

    if (!glview) {
#if DESKTOP_RUNTIME
        const auto factor = SCALE_FACTOR;
        glview = GLViewImpl::createWithRect("HotFistRemaster",
                                            cocos2d::Rect(0, 0, designResolutionSize.width * factor,
                                                          designResolutionSize.height * factor));
        // glview = GLViewImpl::createWithFullScreen("HotFistRemaster");
#else
        glview = GLViewImpl::create("HotFistRemaster");
#endif
        director->setGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(
        designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);

    // 设置内容缩放因数为1
    director->setContentScaleFactor(1);

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = DebugTitleScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    AudioEngine::pauseAll();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    AudioEngine::resumeAll();
}
