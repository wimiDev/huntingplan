#include"BgLayer.h"

bool BgLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}
void BgLayer::killAction()
{
	this->bgSprite->stopAllActions();
	ScaleTo* scaleBig = ScaleTo::create(0.1f,1.1f);
	ScaleTo* scaleNomal = ScaleTo::create(0.1f,1.0f);
	this->bgSprite->runAction(Sequence::create(scaleBig,scaleNomal,nullptr));
}
BgLayer* BgLayer::create(const char* path)
{
	BgLayer* bgLayer = new BgLayer();
	bgLayer->init();
	bgLayer->bgSprite=Sprite::create(path);//path
	bgLayer->bgSprite->setAnchorPoint(Vec2(0.5f,0.5f));
	bgLayer->bgSprite->setPosition(
	bgLayer->getContentSize().width/2,bgLayer->getContentSize().height/2);
	bgLayer->addChild(bgLayer->bgSprite);
	BombParticle* _start= BombParticle::create("particle/start.plist");
	_start->setPosition(bgLayer->getContentSize().width / 2, bgLayer->getContentSize().height / 2);
	bgLayer->addChild(_start);
	return bgLayer;
}