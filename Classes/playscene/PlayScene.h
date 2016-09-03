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
	*֡�ص�
	*/
	void Update(float dt);
	/*
	*��ˢ��
	*/
	void gameLogic(float dt);
	/*
	*��������ص�
	*/
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*e);
	void onTouchEnded(cocos2d::Touch*touch, cocos2d::Event*touch_event);
	void onTouchMove(cocos2d::Touch*touch, cocos2d::Event*touch_event);
	/*
	*����������ײ�ص�
	*/
	bool w_onContactBegin(const PhysicsContact& contact);//��һ�νӴ��ص�
	bool w_onContactpreSolve(const PhysicsContact& contact);//������״�໥�Ӵ�
	void w_onContactPostSolve(const PhysicsContact& contact);//�໥�Ӵ������ִ�У�������ص��ﴦ���˺�ֵ��
	void w_onContectSeparate(const PhysicsContact& contact);//������״�յ�һ��ֹͣ�Ӵ�
	/*
	*����������
	*/
	void w_onEnter();
	//��ʼ����Ϸ����
	void initGameData(int _gameModule);
	/*
	*����
	*/
	void Replay();
	//��Ϸ���������̵�
	void GameOverShop();
	//���miss
	void addmiss();
public:
	//������
	BgLayer* bgLayer;
	//panellayer��
	PanelLayer* panelLayer;
	//���˲�
	EnemyLayer* enemyLayer;
	//�ڵ�����̨��
	BulletLayer* bulletLayer;
	//�Ƿ���Ϸ����
	// 1--��Ϸ����
	// -1--��ս�ɹ�
	// 0--������Ϸ
	// 2--��Ϸδ����
	int isGameover;
	//ģʽ4��©�ĵ�������
	int _omitEnemy;
	//*��Ϸ����ʱ��
	int gameTime;
	//*���ص��˵�ʱ������
	int _statetime;
	//*module4��������
	int _module4dp;
	//*��һ�μ���ʱ������module4��
	int _nexttime;
	//��ײ����
	Sprite*edgeShpe;
	//��ӵ��˵�ʱ����
	float _addEnemyTimer;
	//��������
	int combo;
	//��Ϸģʽ
	int _gameModule;
	//��Ϸ״̬��־
	int _gameState;
	//����id
	int _propId;
	int _propList[3];
	float _powertime;
	//��������
	int reward_num;
	//�û���
	std::string _username;
	//�Ƿ�����˼��
	int _killspy;
	//��������
	bool _enabletouch;
	//*��Ϸģʽ4���Ѷ��ݶ�
	int _grads;
private:
	//��ȡ���������ǲ�����̨
	bool getTouchIsturret(Vec2 point);
	/*
	*�������棬��ʱ��,1�붨ʱ
	*/
	void timerByProt(float dt);
	void gameOverTimer_ones(float dt);
	void ShowVictorySceneCallback(float dt);
	//*�����Ϸ����״̬
	void changeGameState();
	//��Ϸģʽ1����
	void gameModule4Update();

	//��Ϸģʽ2�ĸ��·���
	void gameModule2Update();

	//��Ϸģʽ3��֡ˢ��
	void gameModule3Update();

	//��Ϸģʽ4�߼�
	void gameModule4Logic();
	//��Ϸģʽ2�߼�
	void gameModule2Logic();
	//��Ϸģʽ3��ӵ���
	void gameModule3AddEnemy();
	/*��Ϸʤ��*/
	void victory();
	/*
	*��Ϸ����
	*/
	void GameOver();
	//*��Ϸ��ʼ����������ص�
	void buycallback();
	//*��Ϸ��������������ص�
	void gameoverbuy();
	//��Ϸ��Դ���꣬δ����
	void buynotthing();
	//2.0s�����̵�
	void pushgameshop(float dt);
	//�������ڷ��䣬���붨ʱ��
	void timer_05(float dt);
	// 
	void resetfire(float dt);
private:
	//����
	int gameOverTimer;
	//*��Ϸ����
	std::string _gameoverpoint;
	//*�Ƿ��ڷ���
	int _isfire;
	//*����ʱ��
	int _firetime;
	//*��������
	Vec2 _touchlocation;
};

#endif
