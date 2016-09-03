#include "GameUi.h"

GameUi::GameUi()
{
}


GameUi::~GameUi()
{

}
Score* GameUi::score = new Score();
//TaskCard* GameUi::taskCard = TaskCard::create();
Gold* GameUi::gold = new Gold();
//ui::Button* GameUi::setingButton = nullptr;
//////////////////////////////////////////////

UiAction* UiAction::_instance = nullptr;
UiAction* UiAction::getInstance()
{
	_instance = new UiAction();
	_instance->init();
	return _instance;
}
bool UiAction::init()
{

	return true;
}
Action* UiAction::pushin(float dt, CCCallFuncN& _callback)
{
	Action* _action = nullptr;
	ScaleTo* _scalebig = ScaleTo::create(dt, 1.0f);
	EaseExponentialIn* _easein = EaseExponentialIn::create(_scalebig);

	_action = Sequence::create(_easein, &_callback, nullptr);
	return _action;
}
Action* UiAction::pushout(float dt, CCCallFuncN& _callback)
{
	Action* _action = nullptr;
	ScaleTo* _scalesmall = ScaleTo::create(dt, 0.0f);
	EaseExponentialIn* _easein = EaseExponentialIn::create(_scalesmall);
	_action = Sequence::create(_easein, &_callback, nullptr);
	return _action;
}
Action* UiAction::buttonsacle(float _scale)
{
	Action* _action = nullptr;
	ScaleTo* _scalebig = ScaleTo::create(0.2f, 1 + _scale);
	ScaleTo* _scalesmall = ScaleTo::create(0.35f, 1 - _scale);
	_action = RepeatForever::create(Sequence::create(_scalebig, _scalesmall, nullptr));
	return _action;
}

