
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
	//*��ӷɻ���ʱ����
	float _flytime;
	//*��Ϸ��ʼ
	ui::Button* playButton;
	//*about
	ui::Button* _aboutButton;
	//*���ð�ť
	ui::Button* setButton;
	//*����
	Sprite* sprite_shade;
	//*����
	Sprite* bg_sprite;
	//*��ť�������ѷ���
	Sprite* sprite_buttonpanel;
	//*���ڡ��㡱
	Layer* _aboutlayer;
	void exit_Callback(Ref* sender);
	void play_Callback(Ref*sender, ui::Widget::TouchEventType type);
	void about_Callback(Ref*sender, ui::Widget::TouchEventType type);
	void set_Callback(Ref*sender, ui::Widget::TouchEventType type);
	void addenemycallback(float dt);
};
#endif

