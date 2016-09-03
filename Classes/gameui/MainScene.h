
#ifndef __MainScene_H_
#define __MainScene_H_
#include "cocos2d.h"
#include"ui/UIButton.h"
#include"DataOfGame.h"
#include"moduleselectscene/moduleselectscene.h"
#include"cocostudio/CocoLoader.h"
#include"cocostudio/CocoStudio.h"
#include"panellayer/SetingBox.h"
#include"startbglayer.h"
#include"playscene/TargetMaker.h"
#include"adview/AdviewAd.h"

using namespace cocos2d;
class MainScene :
	public Layer
{
public:
	MainScene();
	~MainScene();
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);
	void initUi();
private:
	//*添加飞机的时间间隔
	float _flytime;
	//*游戏开始
	ui::Button* playButton;
	//*about
	ui::Button* _aboutButton;
	//*设置按钮
	ui::Button* setButton;
	//*遮罩
	Sprite* sprite_shade;
	//*背景
	Sprite* bg_sprite;
	//*按钮容器，已废弃
	Sprite* sprite_buttonpanel;
	//*关于“层”
	Layer* _aboutlayer;
	void exit_Callback(Ref* sender);
	void play_Callback(Ref*sender, ui::Widget::TouchEventType type);
	void about_Callback(Ref*sender, ui::Widget::TouchEventType type);
	void set_Callback(Ref*sender, ui::Widget::TouchEventType type);
	void addenemycallback(float dt);
};
#endif

