#include "startscene.h"

cocos2d::Scene * StartScene::createScene()
{
	Scene* _scene = Scene::create();
	Layer* _layer = StartScene::create();
	_scene->addChild(_layer);
	return _scene;
}

bool StartScene::init()
{
	if(!Layer::init())
	{ 
		return false;
	}
	this->scheduleOnce(schedule_selector(StartScene::jummianscene),2.0f);
	Layer* _startlayer = static_cast<Layer*>(CSLoader::createNode("startscene/startlayer.csb"));
	_bg = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_startlayer,"sprite_startimg"));
	this->addChild(_startlayer);
	return true;
}

void StartScene::changeother(Scene * _scene)
{
	Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, _scene));
}

void StartScene::jummianscene(float dt)
{
	FadeOut* _fadeout = FadeOut::create(0.5f);
	CCCallFuncN* _fofinish = CCCallFuncN::create(CC_CALLBACK_1(StartScene::changetowimi,this));
	_bg->runAction(Sequence::create(_fadeout,_fofinish,nullptr));


}

void StartScene::changetowimi(Ref * _sender)
{		
	_bg->removeFromParentAndCleanup(true);
	_bg = Sprite::create("startscene/startimg.png");
	_bg->setPosition(DataOfGame::getInstance()->getrealposition(Vec2(540,360)));
	this->addChild(_bg);
	FadeIn* _fadein = FadeIn::create(0.5f);
	DelayTime* _delay = DelayTime::create(1.0f);
	FadeOut* _fadeout = FadeOut::create(0.5f);
	CCCallFuncN* _fofinish = CCCallFuncN::create([=](Ref*sender) {
	Scene* _mianscene = MainScene::createScene();
	changeother(_mianscene);
	});
	_bg->runAction(Sequence::create(_fadein,_delay,_fadeout,_fofinish,nullptr));
}
