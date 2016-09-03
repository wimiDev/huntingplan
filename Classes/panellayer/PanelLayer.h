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
	void addAllToLayer();//添加所有元素进入层
	//combo增加，并展示特效
	void addCombo(int _addnum);
	//结算combo
	void resetCombo();
	//添加遮罩
	void addShade();
	//添加游戏成功/结束遮罩
	void addshade_text(bool issuffule,std::string _str);
	void removeshade_text();
	void setMissState(int _miss);
	void loadmissicon(Node* _missnode);
	//显示第几关
	void showrount(int _rount);
	void removerount(float dt);
	Vec2 getmidPos();
	//加载所需纹理
	void loadspriteframe();
	//添加教程
	void showcourse(int _gamemodule);
	void removecourse();
	//触摸开始响应回调
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*e);
	//*显示文字提示
	void showtextmessage(const char* _str);
public:
	//分数标签
	static Score*score;
	static Gold* gold;
	//炮弹
	static BulletView*meterbulletView;
	static SpaceBombView*spacebombView;
	static std::vector<BulletView*> bulletViewList;
	//任务卡
	//static TaskCard*taskCard;
	//设置按钮
	static ui::Button* setingButton;
	 Label* label_HeightScore;
	WimiProgress* enemyNum;
	EnemyProcess* _enemyprocess;
	WimiProgress* comboPower;
	int resetComboing;
	//火力支援按钮
	ui::Button* button_fireSupport;
	//飞船
	Sprite* ariship;
	//炮
	Turret* turret;
	//炮塔
	Sprite* _connonPool;
	//炮弹数量
	BulletView* _bulletview;
	//遮罩
	Sprite* _shade;
	//missnode
	Node* _nodemiss;
	//*帮助按钮
	ui::Button* _buttonhelp;
	//*是否可以触摸
	bool _touchenable;
private:
	Vec2* getRealPosition(float x, float y);
	void buttonFireSupportCallback(Ref*sender, ui::Widget::TouchEventType type);
	void setingboxcallback(Ref*sender, ui::Widget::TouchEventType type);
	void buttonhelpCallback(Ref*sender, ui::Widget::TouchEventType type);
};
#endif
