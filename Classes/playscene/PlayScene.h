#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include"ContactDeal.h"
#include"bglayer/BgLayer.h"
#include"panellayer/PanelLayer.h"
#include"enemylayer/EnemyLayer.h"
#include"bulletlayer/BulletLayer.h"
#include"victorylayer/VictoryLayer.h"
#include"gameoverlayer/GameoverLayer.h"
#include"particle/bombparticle.h"


using namespace cocos2d;
class PanelLayer;
class EnemyLayer;
class BulletLayer;
class VictoryLayer;

class PlayScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int _gameModule);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual void onEnterTransitionDidFinish();
    // implement the "static create()" method manually
    CREATE_FUNC(PlayScene);
	/*
	*帧回调
	*/
	void Update(float dt);
	/*
	*秒刷新
	*/
	void gameLogic(float dt);
	/*
	*触摸输入回调
	*/
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*e);
	void onTouchEnded(cocos2d::Touch*touch, cocos2d::Event*touch_event);
	void onTouchMove(cocos2d::Touch*touch, cocos2d::Event*touch_event);
	/*
	*物理世界碰撞回调
	*/
	bool w_onContactBegin(const PhysicsContact& contact);//第一次接触回调
	bool w_onContactpreSolve(const PhysicsContact& contact);//两个形状相互接触
	void w_onContactPostSolve(const PhysicsContact& contact);//相互接触处理后执行，在这个回调里处理伤害值等
	void w_onContectSeparate(const PhysicsContact& contact);//两个形状刚第一次停止接触
	/*
	*进入主场景
	*/
	void w_onEnter();
	//初始化游戏数据
	void initGameData(int _gameModule);
	/*
	*重玩
	*/
	void Replay();
	//游戏结束补充商店
	void GameOverShop();
	//添加miss
	void addmiss();
public:
	//背景层
	BgLayer* bgLayer;
	//panellayer层
	PanelLayer* panelLayer;
	//敌人层
	EnemyLayer* enemyLayer;
	//炮弹，炮台层
	BulletLayer* bulletLayer;
	//是否游戏结束
	// 1--游戏结束
	// -1--挑战成功
	// 0--正在游戏
	// 2--游戏未就绪
	int isGameover;
	//模式4遗漏的敌人数量
	int _omitEnemy;
	//*游戏进行时间
	int gameTime;
	//*加载敌人的时间向量
	int _statetime;
	//*module4数据向量
	int _module4dp;
	//*下一次加载时间间隔（module4）
	int _nexttime;
	//碰撞盒子
	Sprite*edgeShpe;
	//添加敌人的时间间隔
	float _addEnemyTimer;
	//连击计数
	int combo;
	//游戏模式
	int _gameModule;
	//游戏状态标志
	int _gameState;
	//道具id
	int _propId;
	int _propList[3];
	float _powertime;
	//奖励分数
	int reward_num;
	//用户名
	std::string _username;
	//是否击落了间谍
	int _killspy;
	//触摸允许
	bool _enabletouch;
	//*游戏模式4的难度梯度
	int _grads;
private:
	//获取触摸到的是不是炮台
	bool getTouchIsturret(Vec2 point);
	/*
	*能量增益，定时器,1秒定时
	*/
	void timerByProt(float dt);
	void gameOverTimer_ones(float dt);
	void ShowVictorySceneCallback(float dt);
	//*变更游戏进行状态
	void changeGameState();
	//游戏模式1更新
	void gameModule4Update();

	//游戏模式2的更新方法
	void gameModule2Update();

	//游戏模式3的帧刷新
	void gameModule3Update();

	//游戏模式4逻辑
	void gameModule4Logic();
	//游戏模式2逻辑
	void gameModule2Logic();
	//游戏模式3添加敌人
	void gameModule3AddEnemy();
	/*游戏胜利*/
	void victory();
	/*
	*游戏结束
	*/
	void GameOver();
	//*游戏开始，补给购买回调
	void buycallback();
	//*游戏结束，补给购买回调
	void gameoverbuy();
	//游戏资源用完，未购买
	void buynotthing();
	//2.0s弹出商店
	void pushgameshop(float dt);
	//重置正在发射，半秒定时器
	void timer_05(float dt);
	// 
	void resetfire(float dt);
private:
	//数据
	int gameOverTimer;
	//*游戏结语
	std::string _gameoverpoint;
	//*是否在发射
	int _isfire;
	//*发射时间
	int _firetime;
	//*触摸坐标
	Vec2 _touchlocation;
};

#endif
