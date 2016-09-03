#include "FireBomb.h"

FireBomb * FireBomb::create()
{
	FireBomb* fireBomb = new FireBomb();
	fireBomb->init();
	fireBomb->initWithFile("bullet/firebullet/firebullet_1.png");
	fireBomb->setID(0);
	fireBomb->setBlood(1);
	fireBomb->setKind(4);
	fireBomb->setVelocity(500.0);
	fireBomb->setKillability(1);
	fireBomb->flushTime = 0.3f;
	fireBomb->floEnemy = nullptr;
	BombParticle* _bulletfire = BombParticle::create("particle/particle_bullet_f1.plist");
	_bulletfire->setPosition(fireBomb->getContentSize().width/2,-fireBomb->getContentSize().height/2);
	fireBomb->addChild(_bulletfire);
	fireBomb->schedule(schedule_selector(FireBomb::timerCallback), fireBomb->flushTime);
	fireBomb->floEnemy =fireBomb->scanEnemy();
	if(fireBomb->floEnemy)
	fireBomb->floEnemy->setisFlo(true);
	fireBomb->setName("firebomb");
	return fireBomb;
}

void FireBomb::setBlood(int blood)
{
	this->_blood = blood;
}

int FireBomb::getBlood()
{
	return this->_blood;
}

void FireBomb::runNextPoint(const Vec2 nextPoint)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//*如果已经移出屏幕边界
	if (getPosition().x > visibleSize.width ||
		getPosition().y > visibleSize.height)
	{
		this->unscheduleAllSelectors();
		DataOfGame::getInstance()->recycle_bin.pushBack(this);
		return;
	}
	//*计算下一次刷新的时间
	flushTime = random(1,3)*0.1;
	//*计算角度
	float p_X = 0;
	float p_Y = 0;
	float rotate = 0;
	p_X = nextPoint.x-getPosition().x;
	p_Y = nextPoint.y - getPosition().y;
	if (p_X >= 0)
	{
		rotate = std::atan(p_Y/p_X);
		rotate=90-CC_RADIANS_TO_DEGREES(rotate);
	}
	else
	{
		rotate = std::atan(p_Y /- p_X);
		rotate = -(90 - CC_RADIANS_TO_DEGREES(rotate));
	}
	setRotation(rotate);
	//CCLOG("px=%f,py=%f=%f,firebomb rotate=%f",p_X,p_Y,rotate);
	this->stopAllActions();
	float sum = std::sqrt(std::pow(p_X, 2) + std::pow(p_Y,2));
	MoveTo* moveNext = MoveTo::create(sum/getVelocity(),nextPoint);
	this->runAction(moveNext);
}

void FireBomb::timerCallback(float dt)
{
	float p_Y = Director::getInstance()->getVisibleSize().height;
	Vec2 nextPoint = Vec2(getPosition().x,p_Y);
	if (floEnemy!=nullptr&&floEnemy->getBlood()>0&&floEnemy->getisFlo())
	{
		nextPoint= floEnemy->getPosition();
	}
	else
	{
		nextPoint = Vec2(this->getPosition().x, p_Y);
	}
	//*获得目标
	runNextPoint(nextPoint);
}
target* FireBomb::scanEnemy()
{
	target* _enemy = nullptr;
	for (int i = 0; i < DataOfGame::getInstance()->targetsVector.size(); ++i)
	{
		target* enemy = static_cast<target*>(DataOfGame::getInstance()->targetsVector.at(i));
		if (!enemy->getisFlo()&&enemy->getKind()!=7)
		{
			_enemy = enemy;
			break;
		}
	}
	return _enemy;
}
target* FireBomb::getFloEnemy()
{
	return this->floEnemy;
}
