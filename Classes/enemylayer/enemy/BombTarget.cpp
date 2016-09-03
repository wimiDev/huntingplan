#include "BombTarget.h"


BombTarget::BombTarget()
{
}


BombTarget::~BombTarget()
{
}

BombTarget* BombTarget::create(const char path[50],int id, int kind, int blood, float v, int r_bomb)
{
	BombTarget* bombTarget =new  BombTarget();
	bombTarget->initWithSpriteFrameName("enemytexture/bombenemy/bombenemy_1.png");
	bombTarget->setId(id);
	bombTarget->setKind(kind);
	bombTarget->setBlood(blood,false);
	bombTarget->setVelocity(v);
	bombTarget->setr_Bomb(125.0);
	bombTarget->_runingAction=bombTarget->createRuningAnimate
	("enemytexture/bombenemy/bombenemy_1.png","enemytexture/bombenemy/bombenemy_2.png");
	
	bombTarget->runAction(RepeatForever::create(bombTarget->_runingAction));
	return bombTarget;
}
void BombTarget::setBlood(int blood,bool isAddCombo)
{
	if (blood < this->_blood&&blood > 0)
	{
		int score = abs(blood - _blood)*this->getHitScore();
		ScaleBy* scaleBig = ScaleBy::create(0.3f,1.5f);
		
		Sprite*bombCircle=Sprite::create("target/bombcircle.png");
		bombCircle->setScale(3.0f);
		bombCircle->setPosition(getContentSize().width/2,getContentSize().height/2);
		RotateBy* _rotateby = RotateBy::create(0.5f, 90);
		bombCircle->runAction(RepeatForever::create(_rotateby));
		this->addChild(bombCircle);
		this->setHaveScore(getHaveScore() - score);
		GameUi::score->addScoreOnScene(score, this->getParent(), this->getPosition());
		this->_blood = blood;
		Audio::getInstance()->playeffectbykey("enemyhit");
	}
	else if (blood <= 0)
	{
		this->_blood = blood;
		GameUi::score->addScoreOnScene(this->getHaveScore() * 
			DataOfGame::getInstance()->multiplying_power, this->getParent(), this->getPosition());
		DataOfGame::getInstance()->enemyResidue -= 1;
		DataOfGame::getInstance()->enemyOnScene -= 1;
		bombAnimation();
	}
	else
	{
		this->_blood = blood;
	}
}
void BombTarget::bombAnimation()
{
	
	//auto animation = Animation::create();
	//for (int i = 0; i < ImgPath::path_meterTarget_Bomb_Animation.size(); ++i)
	//{
	//	animation->addSpriteFrameWithFile(ImgPath::path_meterTarget_Bomb_Animation.at(i));
	//}
	//animation->setDelayPerUnit(1.0f / 24);
	//animation->setRestoreOriginalFrame(false);
	//Sprite* sprite_ani = Sprite::create();
	//sprite_ani->setAnchorPoint(Vec2(0.5f, 0.5f));
	//sprite_ani->setPosition(this->getPosition());
	////TODO:this->getparent有时候获取到的是空，发生异常
	//if (this->getParent() == nullptr)
	//{
	//	log("bombAnimation getParent==nullptr");
	//	return;
	//}
	//this->getParent()->addChild(sprite_ani, 2);
	//auto action = Animate::create(animation);
	//this->stopAllActions();
	//CCCallFuncN*callback = CCCallFuncN::create(CC_CALLBACK_1(BombTarget::BeginBomb, this));
	//sprite_ani->runAction(Sequence::create(action, action->reverse(), callback, nullptr));
	BombParticle* _explosion = BombParticle::create("particle/particle_bomb4.plist");
	_explosion->setPosition(this->getPosition());
	this->getParent()->addChild(_explosion);
	Audio::getInstance()->playeffectbykey("bigenemybomb");
	//this->stopAllActions();
	Bomb::BeginBomb(this->getr_Bomb(),true, this, this->getParent());
	DataOfGame::getInstance()->recycle_bin.pushBack(this);
}
void BombTarget::BeginBomb(Ref*sender)
{
	auto ani = static_cast<Sprite*>(sender);
	DataOfGame::getInstance()->recycle_bin.pushBack(ani);
}