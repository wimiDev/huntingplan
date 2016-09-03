#ifndef _VICTORYLAYER_VICTORYLAYER_H_
#define _VICTORYLAYER_VICTORYLAYER_H_
#define _ADDSCORESPEED 3
#include"cocos2d.h"
//#include"gameui/GameUi.h"
#include"playscene/PlayScene.h"
#include"gameui/MainScene.h"
#include"adview/AdviewAd.h"
using namespace cocos2d;

class VictoryLayer
	:public Layer
{
public:
	virtual bool init();
	static VictoryLayer* create();
	//*统计分数
	void accountScore(int score);

	//*统计剩余炮弹
	void accountBullet(int countBullet,int& score);
	//virtual void onEnter();
	//virtual void onExit();
private:
	void RestartCallback(Ref * sender, ui::Widget::TouchEventType type);
	void NextMenuCallback(Ref * sender, ui::Widget::TouchEventType type);
	void JmpMenuCallback(Ref * sender, ui::Widget::TouchEventType type);
	void passallcallback(Ref * sender, ui::Widget::TouchEventType type);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*e);
	void GameModule3ResetData();
	//void GameModule2RestData();
	//总分计算
	void accounttimer(float dt);
	//加奖励分数
	void addreward(Ref*sender);
	//加剩余炮弹
	void addresidue(Ref*sender);
	//计算金币
	void accountgold();
	//添加动作
	Action* createAddScoreAction(CCCallFuncN* callback);
	//更正文本显示位置
	//void updateTextPosition(Sprite*panel,ui::Text* text);
	//通关
	void passallround();

private:
	Sprite* sprite_bg;	
	Sprite* sprite_rect1;
	Sprite* sprite_rect2;
	Sprite* sprite_rect3;
	Sprite* sprite_rect4;
	int _bulletResidue;
	ui::Text* text_score;
	ui::Text* text_residue;
	ui::Text* text_gift;
	ui::Text* text_gold;
	ui::Button* nextround;
	ui::Button* replay;
	ui::Button* menu;
	int _addscore;
	int _score;
	int _addspeed;

};
#endif
