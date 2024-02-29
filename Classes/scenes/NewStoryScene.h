#ifndef HOTFISTREMASTER_NEWSTORYSCENE_H
#define HOTFISTREMASTER_NEWSTORYSCENE_H

#include "cocos2d.h"
#include "components/MessageTip.h"
#include "external/json/document.h"
USING_NS_CC;

class ShowImgCommand;
class MoveImgCommand;
class ShowMsgCommand;

class NewStoryScene: public Scene
{
public:
    NewStoryScene();
    virtual bool initWithStoryName(const std::string& storyName);
    static NewStoryScene* create(const std::string& storyName);

    void update(float dt) override;

    void onExit() override;

private:
    /** 当前进行的事件步骤计数 */
    int commandStep;

    /** 当前事件的等待时间 */
    float commandWaitFrame;

    /** 事件总计数 */
    int totalCommandSteps;
    /** 是否处于等待输入的状态 */
    bool isWaitingInput;

    /** 故事场景的主图层 */
    Layer* mainLayer;

    Sprite* topMessageDialog;
    Sprite* bottomMessageDialog;
    Sprite* topAvatar;
    Sprite* bottomAvatar;
    Label* topMessageLabel;
    Label* bottomMessageLabel;
    MessageTip *messageTip;

    /** 
     * 描述故事的原始JSON文档
     * 
     * TODO 在文档数据结构可以确定后，转换为对应C++对象，从而避免动态使用之
     */
    rapidjson::Document document;
private:
    /** 加载所有资源 */
    void loadResources();
    /** 释放所有已加载的资源 */
    void releaseResources();

    /** 处理事件 */
    void handleCommand(rapidjson::Value& object);

    void handleShowImgCommand(const ShowImgCommand& cmd) const;
    void handleMoveImgCommand(const MoveImgCommand& cmd) const;
    void handleShowMsgCommand(const ShowMsgCommand& cmd);


    void _initMessageDialog();
    Label* _createMessageLabel();
};

#endif //HOTFISTREMASTER_NEWSTORYSCENE_H
