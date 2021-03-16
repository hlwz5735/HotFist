#ifndef HOTFISTREMASTER_NEWSTORYSCENE_H
#define HOTFISTREMASTER_NEWSTORYSCENE_H

#include "cocos2d.h"
#include "external/json/document.h"
USING_NS_CC;

class NewStoryScene: public Scene
{
public:
    NewStoryScene();
    virtual bool init(const std::string& storyName);
    static NewStoryScene* create(const std::string& storyName);

    virtual void update(float dt) override;
private:
    int eventStep;
    int eventWaitFrame;
    bool eventWaiting;
    int eventCount;

    Layer* mainLayer;

    Vector<Sprite*> imgVector;
    std::unordered_map<std::string, int> imgTag2IdxMap;

    rapidjson::Document document;
private:
    void loadResources();

    void handleEvent(rapidjson::Value &object);
};


#endif //HOTFISTREMASTER_NEWSTORYSCENE_H
