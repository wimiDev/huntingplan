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
*游戏结束层，游戏结束的时候会弹出这个层
*create by wimidev
*/
using namespace cocos2d;
class GameOverLayer
	:public Layer
{
public:
	//*初始化
	virtual bool init();
	//*创建游戏结束层实例
	static GameOverLayer*create();
	//*结算最高分
	void accoutHeightScore();
	//*计算分数
	void accountScore();
	//*释放精灵帧
	void freedspriteframe();
	//*加载ui
	void loadui();
public:
	//分数显示层
	ui::Text* _textScoreLabel;
	//*分数展示
	ui::Text* _textscore;
	//*金币标签
	ui::Text* _textgoldlabel;
	//*金币展示
	ui::Text* _textgold;
	//*确认
	ui::Button* _buttonok;
	//*展示层背景
	Sprite* _sprite_accountbg;
	//*游戏结束标题
	ui::Text* _gameovertitle;
	//*重玩
	ui::Button* _replaybutton;
	//*菜单
	ui::Button* _menubutton;
	//*分享
	ui::Button* _sharebutton;
	//*排行榜列表
	ui::ListView* _listview1;
	//*分数结束层
	Layer* scoreAccountLayer;
	//输入层
	Layer* _inputLayer;
	//输入框
	ui::TextField* _inputbox;
	//*游戏结束层的背景
	Sprite* sprite_bg;
	//*输入框的背景
	Sprite* _inputbg;
private:
	//*重玩回调
	void ReplayCallback(Ref*sender, ui::Widget::TouchEventType type);
	//*菜单回调
	void MenuCallback(Ref*sender, ui::Widget::TouchEventType type);
	//*触摸回调
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*e);
	//*分享回调（未用）
	void ShareCallback(Ref*sender, ui::Widget::TouchEventType type);
	//*计算剩余炮弹
	void accountBullet();
	//*排行榜
	void rankList();
	//模式3重置数据
	void GameModule3ResateData();
	//模式2重置数据
	void GameModule2ResateData();
	//从数据库读取数据到排行榜
	void FullLeaderboardFromDataBase();
	//添加最高分到数据库
	void AddHightToDataBase(char* _module,char* _username,int _score);
	//弹出输入框
	void PushInputBox();
	void TextFieldEvent(Ref*sender,ui::TextField::EventType type);
	//结算金币
	int accountgold(int _score);
	//*确认回调
	void buttonokcallck(Ref*sender, ui::Widget::TouchEventType type);
	//*添加金币回调
	void addgoldcallback(Ref*sender);
	//*输入框回调
	void inputcallback(Ref*sender, ui::Widget::TouchEventType type);
};

#endif
