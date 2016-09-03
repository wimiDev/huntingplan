#include "FireSupport.h"


FireSupport::FireSupport()
{
}
FireSupport::~FireSupport()
{
}
void FireSupport :: OpenFireSupport(Node*scene)
{
	PlayScene* playScene = static_cast<PlayScene*>(scene);
	PanelLayer* _panellayer =static_cast<PanelLayer*>(playScene->getChildByName("panelLayer"));
	Size winSize = Director::getInstance()->getWinSize();
	//Label* l_fireSupport = Label::create(GameStringValue::getStringByKey(std::string("openfiresupport"))->c_str(), "Arial", 36);
	GameInfoText* _firesupportlabel = GameInfoText::create
    (GameStringValue::getStringByKey(std::string("openfiresupport"))->c_str(),
		"font/fangzhengzongyijianti.ttf", 36);
	float p_X = winSize.width / 2 - _firesupportlabel->getContentSize().width / 2;
	float p_Y = -winSize.height/2 +( _panellayer->ariship->getPosition().y + 
		_panellayer->ariship->getContentSize().height
		+ _firesupportlabel->getContentSize().height);
	_firesupportlabel->setPosition(DataOfGame::getInstance()->LayerGetRealPosition(p_X,p_Y));
	_firesupportlabel->setAnchorPoint(Vec2(0.5f,0.5f));
	_firesupportlabel->setTextColor(Color4B::YELLOW);
	_panellayer->addChild(_firesupportlabel,5);
	CCCallFuncN* callback = CCCallFuncN::create([=](Ref*sender){
		_firesupportlabel->removeFromParent();
	});
	_firesupportlabel->showInfoText(callback);
	//最多发射8发导弹
	for (int i = 0; i < DataOfGame::getInstance()->targetsVector.size()&& i < 8; ++i)
	{
		target* enemy = static_cast<target*>(DataOfGame::getInstance()->targetsVector.at(i));
		if (enemy->getKind() == 7)
			continue;
		FireBomb* bullet= FireBomb::create();
		bullet->setPhysicsBody(bullet->createRect(bullet->getContentSize()));
		//bullet->setID(1);
		bullet->setAnchorPoint(Vec2(0.5f,0.5f));
		float p_X = 0;
		p_X = random(-(int)(winSize.width / 2), (int)(winSize.width / 5));
		bullet->setPosition(p_X, -winSize.height/2+bullet->getContentSize().height);
		playScene->bulletLayer->addChild(bullet);
		DataOfGame::getInstance()->bulletsVector.pushBack(bullet);
	}
	Audio::getInstance()->playeffectbykey("firebomb");
}
