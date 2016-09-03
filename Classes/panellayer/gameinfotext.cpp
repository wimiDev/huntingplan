#include "gameinfotext.h"


GameInfoText * GameInfoText::create(const char * _string, const char * _font, int _size)
{
	GameInfoText* _gameinfoText = new GameInfoText();
	_gameinfoText->init();
	_gameinfoText->setString(_string);
	_gameinfoText->setFontName(_font);
	_gameinfoText->setFontSize(_size);
	_gameinfoText->setTextColor(Color4B::ORANGE);
	return _gameinfoText;
}

void GameInfoText::showInfoText(CCCallFuncN * callback)
{
	ScaleTo* scaleTo = ScaleTo::create(0.3f, 1.0f);
	FadeOut* _fadeout = FadeOut::create(0.3f);
	this->runAction(Sequence::create(EaseSineIn::create(scaleTo), _fadeout, callback, nullptr));
}
