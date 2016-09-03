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
	//*设置进度
	void SetEnemyNum(int _num,float _per);
public:
	//*进度条的节点
	Node* _nodeenemyprocess;
	//*进度条的背景
	Sprite*_enmeynumbg;
	//*图标
	Sprite* enemyIcon;
	//*数量显示文本
	ui::Text* _textenemynum;
	//*进度条
	ui::LoadingBar* _loadingbarenemy;
	//*数量
	int _enemynum;
private:
};
#endif // !__PANELLAYER_ENEMYPROCESS_H_
