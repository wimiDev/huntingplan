
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
	*添加分数显示标签到主场景
	*/
	void addScoreLabelToScene(Node*scene);

	/*
	*更新分数数值
	*/
	void updateScoreLabel(int _score);

	/*
	*加分，同时展示特效
	*/
	void addScoreOnScene(int score,Node*scene,Vec2 point);

	/*
	*减分，同时展示特效
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
	*展示特效
	*/
	void scoreMovefinish(Ref*sender);
};
#endif