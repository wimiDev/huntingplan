#ifndef __LEADERBOARD_RANKITEM_H_
#define __LEADERBOARD_RANKITEM_H_
#define _LEADERBOARDSIZE 5
#include"cocos2d.h"
#include"cocostudio/CocoStudio.h"
#include"cocostudio/CocoLoader.h"
#include"ui/UIListView.h"
#include"ui/UIText.h"
#include"ui/UIButton.h"

using namespace cocos2d;
class RankItem
	:public ui::Button
{
public:
	static RankItem* create(int _rank, std::string _username, int _score);
	//int _rank;
	//std::string _username;
	//int _score;

private:
	//排名
	ui::Text* _textrank;
	//用户名
	ui::Text* _textname;
	//分数
	ui::Text* _textscore;
	//排名的背景
	Sprite* _sprite_rankbg;
	//用户头像
	Sprite* _icon;
};
#endif // !__LEADERBOARD_RANKITEM_H_
