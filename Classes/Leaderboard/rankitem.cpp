#include"rankitem.h"
RankItem * RankItem::create(int _rank, std::string _username, int _score)
{
	std::string _stricon[4] = {"gameoverlayer/golden.png","gameoverlayer/silver.png",
		"gameoverlayer/medal.png","gameoverlayer/rank_bg_1.png"};

	RankItem* _rankitem = new RankItem();
	_rankitem->init();
	std::string _stritempath = "gameoverlayer/rankitem_1.png";
	_rankitem->loadTextures(_stritempath, _stritempath, _stritempath);

	std::string _striconame = "gameoverlayer/golden.png";
	if (_rank >= 5)
	{
		_striconame = _stricon[3].c_str();
	}
	else
	{
		_striconame = _stricon[_rank-1].c_str();
	}
	_rankitem->_sprite_rankbg = Sprite::createWithSpriteFrameName(_striconame.c_str());
	_rankitem->_sprite_rankbg->setPosition(Vec2(34.00, 45.53));
	_rankitem->addChild(_rankitem->_sprite_rankbg);

	char _strrank[20];
	sprintf(_strrank, "%d", _rank);
	_rankitem->_textrank = ui::Text::create(_strrank, "font/fangzhengzongyijianti.ttf", 62);
	_rankitem->_textrank->setString(_strrank);
	_rankitem->_textrank->setPosition(Vec2(459.48, 41));
	_rankitem->addChild(_rankitem->_textrank);

	//_rankitem->_icon = Sprite::create("gameoverlayer/rank_bg_1.png");
	//_rankitem->_icon->setPosition(Vec2(456.33, 49.82));
	//_rankitem->addChild(_rankitem->_icon);
	//_rankitem->setVisible(false);

	_rankitem->_textname = ui::Text::create(_username, "font/fangzhengzongyijianti.ttf", 24);
	_rankitem->_textname->setPosition(Vec2(359.63, 23.28));
	_rankitem->addChild(_rankitem->_textname);

	char _strscore[20];
	sprintf(_strscore, "%d", _score);
	_rankitem->_textscore = ui::Text::create(_strscore, "font/fangzhengzongyijianti.ttf", 36);
	_rankitem->_textscore->setPosition(Vec2(181.50, 41));
	_rankitem->addChild(_rankitem->_textscore);

	return _rankitem;
}

