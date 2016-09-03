#include"Gold.h"
////////////////////////////////////////////////////////////////////
//Glod
Gold* Gold::create()
{
	Gold* _gold = new Gold();
	_gold->init();
	Node* _goldnode = CSLoader::createNode("panellayer/nodegold.csb");
	_gold->addChild(_goldnode);
	//±³¾°
	_gold->_sprite_bg = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_gold,"sprite_goldbg"));
	//±êÖ¾
	_gold->_spritelogo = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_gold,"sprite_icon"));
	//±êÇ©
	_gold->_textgold = static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_gold, "text_gold"));
	return _gold;
}


void Gold::setGlodNum(int num)
{
	if (_textgold == nullptr)
	{
		return;
	}
	char str_glod[20];
	sprintf(str_glod, "%d", num);
	_textgold->setString(str_glod);
}

void Gold::showGold(int _num)
{
	if (_textgold == nullptr)
	{
		return;
	}
	char str_glod[20];
	sprintf(str_glod, "%d", _num);
	_textgold->setString(str_glod);
	this->setVisible(true);
	FadeIn* _fadein = FadeIn::create(0.5f);
	FadeOut* _fadeout = FadeOut::create(2.3f);
	CCCallFuncN* _fadefinish = CCCallFuncN::create([=](Ref*sender) 
	{
		this->setVisible(false);
	});
	this->runAction(Sequence::create(_fadein,_fadeout,_fadefinish,nullptr));
}
