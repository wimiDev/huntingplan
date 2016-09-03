#ifndef _STARTSCENE_STARTSCENE_H_
#define _STARTSCENE_STARTSCENE_H_
#include"cocos2d.h"
#include"cocostudio/CocoLoader.h"
#include"cocostudio/CocoStudio.h"
#include"gameui/MainScene.h"

using namespace cocos2d;
class StartScene
	:public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(StartScene);
	void changeother(Scene* _scene);
	int _page;
private:
	void jummianscene(float dt);
	void changetowimi(Ref* _sender);
	Sprite* _bg;
};
#endif // !_STARTSCENE_STARTSCENE_H_
