
#ifndef __SCORE_H_
#define __SCORE_H_
#include"cocos2d.h"
#include"DataOfGame.h"
#include"ui/UIText.h"
#include"cocostudio/CocoStudio.h"
#include"cocostudio/CocoLoader.h"

using namespace cocos2d;
class Score
{
public:
	Score();
	~Score();
	static Score* create();
	/*
	*��ӷ�����ʾ��ǩ��������
	*/
	void addScoreLabelToScene(Node*scene);

	/*
	*���·�����ֵ
	*/
	void updateScoreLabel(int _score);

	/*
	*�ӷ֣�ͬʱչʾ��Ч
	*/
	void addScoreOnScene(int score,Node*scene,Vec2 point);

	/*
	*���֣�ͬʱչʾ��Ч
	*/
	void SubScoreOnScene(int score);
public:
	Node* _nodescore;
	Sprite* _spritebg;
private:
	ui::Text* scoreLabel;
	ui::Text* _scoreTitle;
	
	Vec2 _startPos;
	/*
	*չʾ��Ч
	*/
	void scoreMovefinish(Ref*sender);
};
#endif