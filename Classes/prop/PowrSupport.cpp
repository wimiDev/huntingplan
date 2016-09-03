#include "PowrSupport.h"


PowerSupport::PowerSupport()
{
}


PowerSupport::~PowerSupport()
{
}
PowerSupport* PowerSupport::getinstance()
{
	PowerSupport* powerSupport = new PowerSupport();
	return powerSupport;
}
void PowerSupport::startSupport(Node*_playscene)
{
	//Audio::PlayBgMusic(Audio::path_powerSupport_bgm);
	PanelLayer* _panelLayer = static_cast<PanelLayer*>(_playscene->getChildByName("panelLayer"));
	setsupportTime(10);
	Size visibelSize = Director::getInstance()->getVisibleSize();
	//Vec2 statPoint = Vec2(visibelSize.width / 2 + 100, -visibelSize.height / 2);

	GameInfoText* _firesupportlabel = GameInfoText::create(
		GameStringValue::getStringByKey(std::string("openpowersupport"))->c_str(), 
		"font/fangzhengzongyijianti.ttf", 36);

	Size winSize = Director::getInstance()->getWinSize();

	float p_X = winSize.width / 2 - _firesupportlabel->getContentSize().width / 2;
	float p_Y = -winSize.height/2+(_panelLayer->ariship->getPosition().y+
		_panelLayer->ariship->getContentSize().height
		+ _firesupportlabel->getContentSize().height);

	_firesupportlabel->setPosition(DataOfGame::getInstance()->LayerGetRealPosition(p_X,p_Y));

	_firesupportlabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	_firesupportlabel->setTextColor(Color4B::YELLOW);
	_panelLayer->addChild(_firesupportlabel,5);
	CCCallFuncN* callback = CCCallFuncN::create([](Ref*sender) {
		Label* l_fireSupport = static_cast<Label*>(sender);
		l_fireSupport->removeFromParent();
	});
	_firesupportlabel->showInfoText(callback);
	//l_fireSupport->runAction(Sequence::create(scaleSmart, Spawn::create(moveBy, scaleBig, nullptr), delay, callback, nullptr));
}
void PowerSupport::endSupport()
{

}
void PowerSupport::showSupportTime(int _time,Node*scene)
{
	char s_time[5];
	sprintf(s_time, "%d", _time);
	auto l_time = ui::Text::create(s_time, "font/fangzhengzongyijianti.ttf", 72);
	l_time->setAnchorPoint(Vec2(0.5f, 0.5f));
	l_time->setPosition(DataOfGame::getInstance()->getrealposition(Vec2(1080,620)));
	l_time->setColor(Color3B::YELLOW);
	scene->addChild(l_time,5);
	auto scaleSmall = ScaleTo::create(0.01f,0.3f);
	auto moveBy = MoveBy::create(0.3f, Vec2(-100, 0));
	auto scaleBig = ScaleTo::create(0.3f,1.0);
	auto delay = DelayTime::create(0.7f);
	CCCallFuncN*callback =  CCCallFuncN::create(CC_CALLBACK_1(PowerSupport::removeSupportTime, this));

	auto action = Sequence::create(scaleSmall,Spawn::create(moveBy,scaleBig,nullptr),delay,callback,nullptr);
	l_time->runAction(action);
}
void PowerSupport::removeSupportTime(Ref*sender)
{
	Label* l_time = static_cast<Label*>(sender);
	l_time->removeFromParent();
}