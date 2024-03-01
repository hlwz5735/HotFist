#ifndef  _STARTSCENE__
#define  _STARTSCENE__

#include "cocos2d.h"
#include "Global.h"

class StartScene : public ax::Scene {
public:
    bool init() override;
    CREATE_FUNC(StartScene);
private:
    // 动态文字函数
    static void rotateLabelAction(ax::Sprite *pLabel, const ax::Point &pLabelPoint);
    static void moveLabelAction(ax::Sprite *pLabelMove, const ax::Point &pLabelPointMove);

    void showTouchToContinueText(float dt);

    ax::Sprite *text = nullptr;
};

#endif
