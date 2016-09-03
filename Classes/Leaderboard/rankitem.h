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
	//����
	ui::Text* _textrank;
	//�û���
	ui::Text* _textname;
	//����
	ui::Text* _textscore;
	//�����ı���
	Sprite* _sprite_rankbg;
	//�û�ͷ��
	Sprite* _icon;
};
#endif // !__LEADERBOARD_RANKITEM_H_
