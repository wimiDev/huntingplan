#ifndef __ENEMYLAYER_ENEMYLAYER_H_
#define __ENEMYLAYER_ENEMYLAYER_H_
#include"cocos2d.h"
#include"playscene/TargetMaker.h"
#include"playscene/PlayScene.h"

using namespace cocos2d;
/*
*���˲㣬���е��˻ᱻ���ص������
*create by wimidev
*/
class EnemyLayer
	:public Layer
{
public:
	//*�������˲�
	static EnemyLayer* create();
	//*���˲��ʼ��
	bool init();
	//*����Ϸģʽ��ӵ��ˣ���playscene����
	void GameModule_4AddEnemy();
	void GameModule_2AddEnemy();
	void GameModule_3AddEnemy();
	//*���м����Ϣ
	void killspy();
	/*��ǰҪ��ӵ���Ļһ����˵�����*/
	int targetTotle;
	/*��ǰҪ��ӵ���Ļһ����˵�ʣ������*/
	int enemyResidue;
	//*��Ļ�ϵĵ�������
	int enemyInScene;
	//*������ӵ���
	void addbitenemy(int _kind,int _num,int _dir,Vec2 _pos);
	
private:
	EnemyLayer();
	~EnemyLayer();
	//�����ƶ���֮��Ĵ���
	void Target_Movefinish(Ref*sender);
	void GameModule4_enemyFinsh(Ref*sender);
	//���������꣬����ʼ��ֹ���������ȡ
	void rand_br_start_end_point(int f);

	//*������˵�����
	//*���ص�������
	int rand_enemyKind();

	/*��ǰ��������ʱ��ſռ�*/
	int* tempTargetGropData;

	/*�鵽ĳһ��*/
	int F_grop;

	//�Ƿ��������
	int isComplete;

	//����ı��������꣬����ʼ��������
	Vec2 brSePoint[2];
	Vec2 sePoint[2];

	//�����˶�����
	int direction;
};
#endif