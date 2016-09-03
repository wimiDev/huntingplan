#ifndef __PANELLAYER_PANELLAYER_H_
#define __PANELLAYER_PANELLAYER_H_

#include"cocos2d.h"
#include"ui/UIText.h"
#include"DataOfGame.h"
#include"Score.h"
#include"Gold.h"
#include"SetingBox.h"
#include"WimiProgress.h"
#include"SpaceBombView.h"
#include"Turret.h"
#include"gameinfotext.h"
#include"ui/UILoadingBar.h"
#include"enemyprocess.h"
#include"wellcomelayer/wellcomelayer.h"

using namespace cocos2d;
class SpaceBombView;
class PanelLayer
	:public Layer
{
public:
	PanelLayer();
	~PanelLayer();
	bool init();
	static PanelLayer* create();
	bool isDanger();
	void addAllToLayer();//�������Ԫ�ؽ����
	//combo���ӣ���չʾ��Ч
	void addCombo(int _addnum);
	//����combo
	void resetCombo();
	//�������
	void addShade();
	//�����Ϸ�ɹ�/��������
	void addshade_text(bool issuffule,std::string _str);
	void removeshade_text();
	void setMissState(int _miss);
	void loadmissicon(Node* _missnode);
	//��ʾ�ڼ���
	void showrount(int _rount);
	void removerount(float dt);
	Vec2 getmidPos();
	//������������
	void loadspriteframe();
	//��ӽ̳�
	void showcourse(int _gamemodule);
	void removecourse();
	//������ʼ��Ӧ�ص�
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*e);
	//*��ʾ������ʾ
	void showtextmessage(const char* _str);
public:
	//������ǩ
	static Score*score;
	static Gold* gold;
	//�ڵ�
	static BulletView*meterbulletView;
	static SpaceBombView*spacebombView;
	static std::vector<BulletView*> bulletViewList;
	//����
	//static TaskCard*taskCard;
	//���ð�ť
	static ui::Button* setingButton;
	 Label* label_HeightScore;
	WimiProgress* enemyNum;
	EnemyProcess* _enemyprocess;
	WimiProgress* comboPower;
	int resetComboing;
	//����֧Ԯ��ť
	ui::Button* button_fireSupport;
	//�ɴ�
	Sprite* ariship;
	//��
	Turret* turret;
	//����
	Sprite* _connonPool;
	//�ڵ�����
	BulletView* _bulletview;
	//����
	Sprite* _shade;
	//missnode
	Node* _nodemiss;
	//*������ť
	ui::Button* _buttonhelp;
	//*�Ƿ���Դ���
	bool _touchenable;
private:
	Vec2* getRealPosition(float x, float y);
	void buttonFireSupportCallback(Ref*sender, ui::Widget::TouchEventType type);
	void setingboxcallback(Ref*sender, ui::Widget::TouchEventType type);
	void buttonhelpCallback(Ref*sender, ui::Widget::TouchEventType type);
};
#endif
