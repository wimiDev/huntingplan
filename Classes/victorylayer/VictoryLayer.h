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
	//*ͳ�Ʒ���
	void accountScore(int score);

	//*ͳ��ʣ���ڵ�
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
	//�ּܷ���
	void accounttimer(float dt);
	//�ӽ�������
	void addreward(Ref*sender);
	//��ʣ���ڵ�
	void addresidue(Ref*sender);
	//������
	void accountgold();
	//��Ӷ���
	Action* createAddScoreAction(CCCallFuncN* callback);
	//�����ı���ʾλ��
	//void updateTextPosition(Sprite*panel,ui::Text* text);
	//ͨ��
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
