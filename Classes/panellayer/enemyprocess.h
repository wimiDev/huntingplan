#ifndef __PANELLAYER_ENEMYPROCESS_H_
#define __PANELLAYER_ENEMYPROCESS_H_
#include"cocos2d.h"
#include"ui/UIText.h"
#include"ui/UILoadingBar.h"
#include"cocostudio/CocoLoader.h"
#include"cocostudio/CocoStudio.h"
#include"DataOfGame.h"

using namespace cocos2d;
class EnemyProcess
{
public:
	static EnemyProcess*create();
	//*���ý���
	void SetEnemyNum(int _num,float _per);
public:
	//*�������Ľڵ�
	Node* _nodeenemyprocess;
	//*�������ı���
	Sprite*_enmeynumbg;
	//*ͼ��
	Sprite* enemyIcon;
	//*������ʾ�ı�
	ui::Text* _textenemynum;
	//*������
	ui::LoadingBar* _loadingbarenemy;
	//*����
	int _enemynum;
private:
};
#endif // !__PANELLAYER_ENEMYPROCESS_H_
