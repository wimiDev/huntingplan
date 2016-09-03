#include "MeterTarget.h"


MeterTarget::MeterTarget():target()
{
	moveCallback = CCCallFuncN::create(CC_CALLBACK_1(MeterTarget::moveFinish,this));
}


MeterTarget::~MeterTarget()
{
}
MeterTarget* MeterTarget::create(const char path[50])
{
	MeterTarget* sprite = new MeterTarget();
	sprite->initWithFile(path);
	if (sprite)
		return sprite;
	return nullptr;
}
MeterTarget* MeterTarget::create(const char path[50], int id, int kind, int blood, float velocity)
{
	MeterTarget* sprite = new MeterTarget();
	sprite->initWithSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/meterenemy/meterenemy_1.png"));
	sprite->setId(id);
	sprite->setKind(kind);
	sprite->setBlood(blood,false);
	sprite->setVelocity(velocity);
	auto animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/meterenemy/meterenemy_1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/meterenemy/meterenemy_2.png"));
	animation->setDelayPerUnit(1.0f / 24.0f);
	animation->setRestoreOriginalFrame(true);
	sprite->_runingAction=Animate::create(animation);
	sprite->runAction(RepeatForever::create(sprite->_runingAction));
	return sprite;
}
void MeterTarget::setBlood(int blood, bool isAddCombo)
{
	if (blood < this->_blood&&blood > 0)
	{
		int score = abs(blood - _blood)*this->getHitScore();
		this->setHaveScore(getHaveScore() - score);
		GameUi::score->addScoreOnScene(score, this->getParent(), this->getPosition());
		this->_blood = blood;
		Audio::getInstance()->playeffectbykey("enemyhit");
	}
	else if (blood <= 0)
	{
		this->_blood = blood;
		GameUi::score->addScoreOnScene(this->getHaveScore()*DataOfGame::getInstance()->multiplying_power,
			this->getParent(), this->getPosition());
		DataOfGame::getInstance()->enemyResidue -= 1;
		DataOfGame::getInstance()->enemyOnScene -= 1;
		bombAnimation();
	}
	else
	{
		this->_blood = blood;
	}
}
void MeterTarget::bombAnimation()
{
	BombParticle* _explosion = nullptr;
	if (this->getKind() == 1)
	{
		_explosion = BombParticle::create("particle/particle_bomb2.plist");
		Audio::getInstance()->playeffectbykey("smallenemybomb");
	}
	else
	{
		_explosion =  BombParticle::create("particle/particle_bomb1.plist");
		Audio::getInstance()->playeffectbykey("bigenemybomb");
	}
	_explosion->setPosition(this->getPosition());
	this->getParent()->addChild(_explosion);
	this->stopAllActions();
	DataOfGame::getInstance()->recycle_bin.pushBack(this);
}

void MeterTarget::moveFinish(Ref*sender)
{
	target* _target = static_cast<target*>(sender);
	DataOfGame::getInstance()->recycle_bin.pushBack(_target);
}

void MeterTarget::runtoNext(Vec2 point)
{
	float speed = sqrt(std::pow(abs(this->getPosition().x - point.x), 2)
		+ std::pow(abs(this->getPosition().y - point.y), 2)) / this->getVelocity();
	MoveTo* moveTo = MoveTo::create(speed, point);
	float rota = getRotate(point);
	RotateTo* rotate = RotateTo::create(0.5f, rota);
	CCCallFuncN* movefinish = CCCallFuncN::create(CC_CALLBACK_1(target::moveFinish, this));
	this->runAction(Sequence::create(Spawn::create(moveTo, rotate, nullptr),
	movefinish,  nullptr));
}
