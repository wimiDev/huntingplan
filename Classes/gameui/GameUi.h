
#ifndef __GAMEUI_GAMEUI_H_
#define __GAMEUI_GAMEUI_H_

#include"cocos2d.h"
#include"DataOfGame.h"
#include"ui/UIButton.h"
#include"ui/UITextAtlas.h"
#include"ui/UIText.h"
#include"panellayer/Score.h"
#include"panellayer/Gold.h"
#include"cocostudio/CocoLoader.h"
#include"cocostudio/CocoStudio.h"

using namespace cocos2d;

/*
*游戏ui类，引用最多的是在加分的效果
*create by wimidev
*/

class GameUi
{
public:
	GameUi();
	~GameUi();
	//背景
	Sprite*mainUi;
	//分数
	static Score*score;
	//金币
	static Gold*gold;
};
/*
*游戏ui动作类，单例类
*create by wimidev
*/
class UiAction
{
public:
	//*获取实例
	static UiAction* getInstance();
	//*初始化
	bool  init();
	//*弹出动作
	Action* pushin(float dt, CCCallFuncN& _callback);
	//*收起动作
	Action* pushout(float dt, CCCallFuncN& _callback);
	//*按钮缩放效果
	Action* buttonsacle(float _scale);
private:
	//*实例
	static UiAction* _instance;
};

#endif