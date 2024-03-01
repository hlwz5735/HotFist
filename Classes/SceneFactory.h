#ifndef _Scene_Factory__
#define _Scene_Factory__

#include "cocos2d.h"

USING_NS_AX;

class SceneFactory
{
public:
	static Scene* story00();
	static Scene* story01();
	static Scene* story02();
	static Scene* story03();
	static Scene* story04();
	static Scene* story05();
	static Scene* storyEnd();

	static Scene* loadLevel(const std::string& levelName);

	static Scene* startScene();
	static Scene* aboutScene();
	static Scene* titleScene();
	static Scene* gameOverScene();
	static Scene* pauseLayer();
	static Scene* ctnLayer();
};
#endif