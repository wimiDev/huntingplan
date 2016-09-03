#ifndef __SETINGBOX_H_
#define __SETINGBOX_H_

#include"cocos2d.h"
#include"ui/UIButton.h"
#include"DataOfGame.h"
#include"ui/UIText.h"
#include"playscene/PlayScene.h"
#include"gameui/MainScene.h"

//…Ë÷√ΩÁ√Ê
class SetingBox
	:public Layer
{
public:
	//SetingBox();
	static SetingBox* create(bool _ishavebutton=true);
	void setMusic(bool isPlay);
	void setEffect(bool isPlay);
	void ShowSetingBox(Node*scene);
	CCCallFuncN* exit_button_func;
	bool init();
public:
	Sprite* _bg;
protected:
private:
	ui::Text* label_Music;
	ui::Text* label_Effect;
	ui::Button* button_Menu;
	ui::Button* button_RePlay;
	ui::Button* button_Music;
	ui::Button* button_Effect;
	ui::Button* exitButton;
	ui::Button* _buttonhelp;
	Sprite* _shade;

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*e);
	void ButtonExitCallback(Ref*sender, ui::Widget::TouchEventType type);
	void ButtonMusicCallback(Ref*sender, ui::Widget::TouchEventType type);
	void ButtonEffectCallback(Ref*sender, ui::Widget::TouchEventType type);
	void ButtonReplayCallback(Ref*sender, ui::Widget::TouchEventType type);
	void ButtonMenuCallback (Ref*sender, ui::Widget::TouchEventType type);
	void ButtonHelpCallback(Ref*sender, ui::Widget::TouchEventType type);
};
#endif