#ifndef HOTFISTREMASTER_NEWSTORYSCENE_H
#define HOTFISTREMASTER_NEWSTORYSCENE_H

#include "cocos2d.h"
#include "external/json/document.h"
USING_NS_CC;

class ShowImgCommand;
class MoveImgCommand;

class NewStoryScene: public Scene
{
public:
    NewStoryScene();
    virtual bool init(const std::string& storyName);
    static NewStoryScene* create(const std::string& storyName);

    void update(float dt) override;
private:
    /** 当前进行的事件步骤计数 */
    int commandStep;
    /** 当前事件的等待帧数，逐帧减一 */
    int commandWaitFrame;
    /** 事件总计数 */
    int totalCommandSteps;
    /** 是否处于等待输入的状态 */
    bool isWaitingInput;

    /** 故事场景的主图层 */
    Layer* mainLayer;

    /** 
     * 描述故事的原始JSON文档
     * 
     * TODO 在文档数据结构可以确定后，转换为对应C++对象，从而避免动态使用之
     */
    rapidjson::Document document;
private:
    /** 加载所有资源 */
    void loadResources();
    /** 处理事件 */
    void handleCommand(rapidjson::Value& object);

    void handleShowImgCommand(const ShowImgCommand& cmd);
    void handleMoveImgCommand(const MoveImgCommand& cmd);
};


#endif //HOTFISTREMASTER_NEWSTORYSCENE_H
