#ifndef _MODULESELECTSCENE_MODULESELECTSCENE_H_
#define _MODULESELECTSCENE_MODULESELECTSCENE_H_

#include"cocos2d.h"
#include"ui/UIButton.h"
#include"cocostudio/CocoLoader.h"
#include"cocostudio/CocoStudio.h"
#include"DataOfGame.h"
#include"shop/GameShop.h"
#include"playscene/PlayScene.h"

class ModuleSelectScene
	:public Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(ModuleSelectScene);
	void initUi();
private:
	void pbModule1_Callback(Ref*sender, ui::Widget::TouchEventType type);
	void pbModule2_Callback(Ref*sender, ui::Widget::TouchEventType type);
	void pbModule3_Callback(Ref*sender, ui::Widget::TouchEventType type);
	void back_Callback(Ref*sender, ui::Widget::TouchEventType type);
	void buycallback();
private:
	Sprite* _bgsprite;
	ui::Button* _module1button;
	ui::Button* _module2button;
	ui::Button* _module3button;
	ui::Button* _buttonback;
	ui::Text* _textround;
	int _gamemodle;
};


#endif
