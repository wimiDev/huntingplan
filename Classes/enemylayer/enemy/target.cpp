#include"target.h"
target::target()
{
	_id = -1;
	_kind = -1;
	_blood = 0;
	_velocity = 0;
	sePoint[2] = {Vec2(),Vec2()};
	brSePoint[2] = { Vec2(),Vec2()};
	setisFlo(false);
	setIsBezier(false);
	this->init();
	this->setTag(101);
	_runingAction = nullptr;
}	
int target::targetHitRule[7] = { 20,30,0,30,50,50,150 };
int target::targetKillRule[7] = { 120,150,300,230,250,250,300 };
Vec2 target::getStartPoint()
{
	Size winSize = Director::getInstance()->getVisibleSize();
	int appear = 0;
	appear = random(1, 2);//确定出现的位置
	if (appear == 1)
	{
		//在y轴上出生
		if (_direction)
		{
			//从左往右
			sePoint[0].x = -this->getContentSize().width/2;
			sePoint[0].y = random(winSize.height / 2, winSize.height-this->getContentSize().height/2);
		}
		else
		{
			//从右往左
			sePoint[0].x = winSize.width+ this->getContentSize().width/2;
			sePoint[0].y = random(winSize.height / 2, winSize.height - this->getContentSize().height / 2);
		}
	}
	else
	{
		//在x轴上出生
		if (_direction)
		{
			sePoint[0].x = random(0.0f, winSize.width * 1 / 3);
			sePoint[0].y = winSize.height+ this->getContentSize().height;
		}
		else
		{
			sePoint[0].x = random(winSize.width * 2 / 3, winSize.width-this->getContentSize().width/2);
			sePoint[0].y = winSize.height+ this->getContentSize().height;
		}
	}
		//log("befor position_x=%f,position_y=%f", sePoint[0].x, sePoint[0].y);
	sePoint[0] = ConverPoint(sePoint[0].x,sePoint[0].y);
		//log("after position_x=%f,position_y=%f", sePoint[0].x, sePoint[0].y);
	if (_direction)
	{
		setRotation(360);
	}
	else
	{
		setRotation(180);
	}
	return sePoint[0];
}
Vec2 target::getNextPoint()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 positionNow = ConverPointTo_0_0(this->getPosition().x, this->getPosition().y);
	if (!isBorder())
	{
		if (_direction)
		{
			//从左往右
			sePoint[1].x = random((int)(positionNow.x+ getContentSize().width / 2),
				(int)(visibleSize.width+ getContentSize().width / 2));
		}
		else
		{
			//从右往左
			if (positionNow.x-this->getContentSize().width/2 < 0)
			{
				sePoint[1].x = 0.000000f;
			}
			else
			{ 
				sePoint[1].x= random(0, (int)(positionNow.x- getContentSize().width / 2));
			}
		}
	}
	else
	{
		//碰到边界返回，方向为反向
		if (_direction)
		{
			_direction = 0;
			//从右往左
			if (positionNow.x - this->getContentSize().width / 2 < 0)
			{
				sePoint[1].x = -getContentSize().width / 2;
			}
			else
			{
				//log("position_x=%f,position_y=%f",this->getPosition().x,this->getPosition().y);
				sePoint[1].x = random(0, (int)(positionNow.x- getContentSize().width / 2));
			}
			setRotation(180);
		}
		else
		{
			//从左往右
			_direction = 1;
			sePoint[1].x = random((int)(positionNow.x), (int)(visibleSize.width+ getContentSize().width / 2));
			setRotation(0);
		}	
	}
	sePoint[1].y = random((int)(visibleSize.height/3), (int)(visibleSize.height));
	
	//log("nextPoint x:%f,y:%f",sePoint[1].x,sePoint[1].y);
	sePoint[1] = ConverPoint(sePoint[1].x,sePoint[1].y);
	return sePoint[1];
}
Vec2 target::ConverPoint(float x, float y)
{
	Size winSize = Size(Director::getInstance()->getVisibleSize().width,
		Director::getInstance()->getVisibleSize().height);
	Vec2 point = Vec2();
	if (x >= winSize.width / 2)
	{
		point.x = x-winSize.width/2;
	}
	else
	{
		point.x = -winSize.width/2+x;
	}
	if (y >= winSize.height / 2)
	{
		point.y = y- winSize.height/2;
	}
	else
	{
		point.y = -winSize.height/2+ y;
	}
	return point;
}
Vec2 target::ConverPointTo_0_0(float x, float y)
{
	Size winSize = Director::getInstance()->getVisibleSize();
	Vec2 point = Vec2(x,y);
	point.x += winSize.width / 2;
	point.y += winSize.height / 2;
	return point;
}

Animate * target::createRuningAnimate(const char* _frame1, const char* _frame2)
{
	Animate* _runanimate = nullptr;
	auto animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName(_frame1));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName(_frame2));
	animation->setDelayPerUnit(1.0f / 24.0f);
	animation->setRestoreOriginalFrame(true);
	_runanimate = Animate::create(animation);
	return _runanimate;
}

bool target::isBorder()
{
	bool _isborder = false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (_direction)
	{
		//从左往右
		if ((this->getPosition().x+getContentSize().width) > visibleSize.width/2)
		{
			_isborder = true;
			//log("_direction=%d,isborder", _direction);
		}
	}
	else
	{
		//从右往左
		if ((this->getPosition().x-getContentSize().width) <= -visibleSize.width/2)
		{
			_isborder = true;
			//log("_direction=%d,isborder", _direction);
		}
	}
	return _isborder;
}
void target::runtoNext(Vec2 point)
{
	float speed = sqrt(std::pow(abs(this->getPosition().x - point.x), 2) +
		std::pow(abs(this->getPosition().y - point.y), 2)) / this->getVelocity();
	MoveTo* moveTo = MoveTo::create(speed, point);
	float rota = getRotate(point);
	//CCLOG("%f",rota);
	RotateTo* rotate =  RotateTo::create(0.5f, rota);
	
	CCCallFuncN* movefinish = CCCallFuncN::create(CC_CALLBACK_1(target::moveFinish, this));

	if (!getIsBezier())
	{ 
		Action* _action = Sequence::create(Spawn::create(moveTo, rotate, nullptr),
			movefinish, nullptr);
		_action->setTag(_ENEMYRUN_TAG_);
		this->runAction(_action);
	}
	else
	{
		//this->runAction(Sequence::create(bezier, movefinish, nullptr));
	}
}
void target::moveFinish(Ref*sender)
{
	target* _target = static_cast<target*>(sender);
	_target->runtoNext(_target->getNextPoint());
}
float target::getRotate(Vec2 nextPoint)
{
	float weith = nextPoint.x - getPosition().x;
	float height = nextPoint.y - getPosition().y;
	float rotate1 = getRotation();
	float rotate2 =std::atan2(height,weith);
	rotate1 = -CC_RADIANS_TO_DEGREES(rotate2);
	return rotate1;
}

void target::animation_callback(Ref*sender)
{
	auto ani = static_cast<target*>(sender);
	DataOfGame::getInstance()->recycle_bin.pushBack(ani);
}
void target::setBlood(int blood, bool isAddCombo)
{
	if (blood < this->_blood&&blood > 0)
	{
		int score = abs(blood - _blood)*this->getHitScore();
		this->setHaveScore(getHaveScore() - score);
		Audio::getInstance()->playeffectbykey("enemyhit");
		GameUi::score->addScoreOnScene(score, this->getParent(), this->getPosition());
		this->_blood = blood;
	}
	else if (blood <= 0)
	{
		this->_blood = blood;
		GameUi::score->addScoreOnScene(this->getHaveScore()*DataOfGame::getInstance()->multiplying_power, this->getParent(), this->getPosition());
		DataOfGame::getInstance()->enemyResidue -= 1;
		bombAnimation();
		DataOfGame::getInstance()->recycle_bin.pushBack(this);
	}
	else
	{
		this->_blood = blood;
	}
}
int target::getBlood()
{
	return this->_blood;
}

void target::bombAnimation()
{
	Audio::getInstance()->playeffectbykey("smallenmeybomb");
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
	//CCCallFuncN*callback=CCCallFuncN::create(CC_CALLBACK_1(target::animation_callback,this));
	//sprite_ani->runAction(Sequence::create(action, action->reverse(), callback, nullptr));

}
