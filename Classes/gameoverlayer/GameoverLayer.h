#ifndef _GAMEOVERLAYER_GAMEOVERLAYER_H_
#define _GAMEOVERLAYER_GAMEOVERLAYER_H_
#include"cocos2d.h"
#include"cocostudio/CocoStudio.h"
#include"cocostudio/CocoLoader.h"
#include"playscene/PlayScene.h"
#include"gameui/MainScene.h"
#include"ui/UIListView.h"
#include"ui/UIText.h"
#include"ui/UITextField.h"
#include"Leaderboard/rankitem.h"
#include"adview/AdviewAd.h"

/*
*��Ϸ�����㣬��Ϸ������ʱ��ᵯ�������
*create by wimidev
*/
using namespace cocos2d;
class GameOverLayer
	:public Layer
{
public:
	//*��ʼ��
	virtual bool init();
	//*������Ϸ������ʵ��
	static GameOverLayer*create();
	//*������߷�
	void accoutHeightScore();
	//*�������
	void accountScore();
	//*�ͷž���֡
	void freedspriteframe();
	//*����ui
	void loadui();
public:
	//������ʾ��
	ui::Text* _textScoreLabel;
	//*����չʾ
	ui::Text* _textscore;
	//*��ұ�ǩ
	ui::Text* _textgoldlabel;
	//*���չʾ
	ui::Text* _textgold;
	//*ȷ��
	ui::Button* _buttonok;
	//*չʾ�㱳��
	Sprite* _sprite_accountbg;
	//*��Ϸ��������
	ui::Text* _gameovertitle;
	//*����
	ui::Button* _replaybutton;
	//*�˵�
	ui::Button* _menubutton;
	//*����
	ui::Button* _sharebutton;
	//*���а��б�
	ui::ListView* _listview1;
	//*����������
	Layer* scoreAccountLayer;
	//�����
	Layer* _inputLayer;
	//�����
	ui::TextField* _inputbox;
	//*��Ϸ������ı���
	Sprite* sprite_bg;
	//*�����ı���
	Sprite* _inputbg;
private:
	//*����ص�
	void ReplayCallback(Ref*sender, ui::Widget::TouchEventType type);
	//*�˵��ص�
	void MenuCallback(Ref*sender, ui::Widget::TouchEventType type);
	//*�����ص�
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*e);
	//*����ص���δ�ã�
	void ShareCallback(Ref*sender, ui::Widget::TouchEventType type);
	//*����ʣ���ڵ�
	void accountBullet();
	//*���а�
	void rankList();
	//ģʽ3��������
	void GameModule3ResateData();
	//ģʽ2��������
	void GameModule2ResateData();
	//�����ݿ��ȡ���ݵ����а�
	void FullLeaderboardFromDataBase();
	//�����߷ֵ����ݿ�
	void AddHightToDataBase(char* _module,char* _username,int _score);
	//���������
	void PushInputBox();
	void TextFieldEvent(Ref*sender,ui::TextField::EventType type);
	//������
	int accountgold(int _score);
	//*ȷ�ϻص�
	void buttonokcallck(Ref*sender, ui::Widget::TouchEventType type);
	//*��ӽ�һص�
	void addgoldcallback(Ref*sender);
	//*�����ص�
	void inputcallback(Ref*sender, ui::Widget::TouchEventType type);
};

#endif
