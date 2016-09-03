#include "Turret.h"


Turret::Turret()
{
}


Turret::~Turret()
{

}
Turret* Turret::create(const char path[50])
{
	Turret* turret = new Turret();
	turret->initWithFile(path);
	return turret;
}
Turret * Turret::create( Sprite * _sp2)
{
	Turret* turret = new Turret();
	turret->_cannon2 = _sp2;
	return turret;
}
void Turret::Rotate(float rotate, CCCallFuncN* fire)
{
	this->stopAllActions();
	auto rotateTo = RotateTo::create(abs(rotate - this->getRotation()) / _velocity,rotate);
	this->runAction(Sequence::create(rotateTo, fire, nullptr));
}

void Turret::Fire()
{
	auto animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("panellayer/connonf1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("panellayer/connonf2.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("panellayer/connonf3.png"));
	animation->setDelayPerUnit(1.0f / 50.0f);
	animation->setRestoreOriginalFrame(false);
	//this->stopAllActions();
	this->runAction(Animate::create(animation));
}
float Turret::GetRotate(Vec2 _point1, Vec2 _point2)
{
	//CCLOG("_point1x = %f,_point1y = %f",_point1.x,_point1.y);
	// CCLOG("_point2x = %f,_point2y = %f",_point2.x,_point2.y);
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Vec2 _org = Director::getInstance()->getVisibleOrigin();
	float rota = 0.0;
	float touch_X = _point1.x - _point2.x;
	float p_Y = _point1.y - _point2.y;
	// CCLOG("touchx = %f,p_Y = %f",touch_X,p_Y);
	if (touch_X >= 0)
	{
		//0~~90
		rota = (float)atan(p_Y*1.0 / touch_X);
		rota = (float)90 - CC_RADIANS_TO_DEGREES(rota);
	}
	else
	{
		//0~~-90
		//touch_X = visiableSize.width / 2 - Point.x;
		rota = (float)atan(p_Y*1.0 / touch_X);
		rota = (float)-(90 + CC_RADIANS_TO_DEGREES(rota));
	}
	//CCLOG("totate = %f",rota);
	return rota;
}

 float Turret::_velocity=0;
 float Turret::_fireVel=0;
 int Turret::_total=0;
 bool Turret::isFire=0;
 int Turret::_velocityList[4] = {0,0,0,0};