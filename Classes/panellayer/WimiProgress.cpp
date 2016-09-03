#include "WimiProgress.h"

void WimiProgress::setNum(int _val,float percent)
{
	this->_num = _val;
	float oldper=progressTimer->getPercentage();
	auto progAction = ProgressTo::create(0.5f,percent);
	progressTimer->stopAllActions();
	progressTimer->runAction(Sequence::create(progAction, nullptr));
	if (l_number)
	{
		char str_num[10];
		sprintf(str_num, "%d", _num);
		l_number->setString(std::string(str_num));
	}
}

int WimiProgress::getNum()
{
	return _num;
}

WimiProgress * WimiProgress::create(const char* fileName, const char* progName)
{
	WimiProgress* prog = new WimiProgress();
	prog->init();
	prog->progess_bg = Sprite::create(fileName);
	prog->progess_bg->setAnchorPoint(Vec2(0.5f,0.5f));
	prog->progess_bg->setPosition(0,0);
	prog->addChild(prog->progess_bg);

	std::string str_prog = progName;
	prog->sprite_prog = Sprite::create(progName);
	prog->progressTimer = ProgressTimer::create(prog->sprite_prog);
	prog->progressTimer->setPosition(prog->progess_bg->getContentSize().width/2, prog->progess_bg->getContentSize().height/2);
	prog->progess_bg->addChild(prog->progressTimer);
	
	prog->l_number = ui::Text::create("","font/fangzhengzongyijianti.ttf",84);
	prog->l_number->setAnchorPoint(Vec2(0.5f,0.5f));
	prog->l_number->setPosition(Vec2(prog->progess_bg->getContentSize().width / 2, 
		prog->progess_bg->getContentSize().height/2));
	prog->progess_bg->addChild(prog->l_number);
	prog->_num =0;
	if (prog->progressTimer)
	{
		prog->progressTimer->setType(ProgressTimerType::BAR);
		prog->progressTimer->setMidpoint(Vec2(0, 1));
		prog->progressTimer->setBarChangeRate(Vec2(0, 1));

	}
	return prog;
}

WimiProgress * WimiProgress::create(Sprite * sp1, Sprite * sp2)
{
	if (!sp1 || !sp2)
	{
		return nullptr;
	}
	WimiProgress* prog = new WimiProgress();
	prog->init();
	prog->progess_bg = sp1;
	prog->progess_bg->setAnchorPoint(Vec2(0.5f, 0.5f));
	prog->progess_bg->setPosition(0, 0);
	prog->addChild(prog->progess_bg);

	prog->sprite_prog = sp2;
	prog->progressTimer = ProgressTimer::create(prog->sprite_prog);
	prog->progressTimer->setPosition(prog->progess_bg->getContentSize().width / 2, prog->progess_bg->getContentSize().height / 2);
	prog->progess_bg->addChild(prog->progressTimer);

	prog->l_number = ui::Text::create("", "font/fangzhengzongyijianti.ttf", 84);
	prog->l_number->setAnchorPoint(Vec2(0.5f, 0.5f));
	prog->l_number->setPosition(Vec2(prog->progess_bg->getContentSize().width / 2,
	prog->progess_bg->getContentSize().height / 2));
	prog->progess_bg->addChild(prog->l_number);
	prog->_num = 0;
	if (prog->progressTimer)
	{
		prog->progressTimer->setType(ProgressTimerType::BAR);
		prog->progressTimer->setMidpoint(Vec2(0, 1));
		prog->progressTimer->setBarChangeRate(Vec2(0, 1));

	}
	return prog;
}

Sprite * WimiProgress::getSpriteProg()
{
	return this->sprite_prog;
}

Sprite * WimiProgress::getSpritBg()
{
	return this->progess_bg;
}

ProgressTimer * WimiProgress::getProgressTimer()
{
	return this->progressTimer;
}

Action * WimiProgress::createNomalAction()
{
	progess_bg->setTexture(SpriteFrameCache::getInstance()
		->getSpriteFrameByName(ImgPath::path_powerpoolbg_nomal)->getTexture());
	progess_bg->stopActionByTag(5);
	CallFuncN* changeNomal = CallFuncN::create([=](Ref*sender)
	{
		progess_bg->setTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName(ImgPath::path_powerpoolbg_nomal)->getTexture());
	});
	Action* action = Sequence::create(changeNomal,nullptr);
	return action;
}

Action * WimiProgress::createLightAction()
{
	progess_bg->stopAllActions();
	Action* action = nullptr;
	
	CallFuncN* changeNomal = CallFuncN::create(CC_CALLBACK_1(WimiProgress::ChangeNomal, this));
	CallFuncN* changeLight = CallFuncN::create(CC_CALLBACK_1(WimiProgress::ChangeLight,this));
	DelayTime* delaytime = DelayTime::create(0.5f);
	action = RepeatForever::create(
		Sequence::create(delaytime, changeLight, delaytime, changeNomal, nullptr));
	//！！！！！设置动作标志为5！！！！！
	action->setTag(5);
	return action;
}

void WimiProgress::ChangeNomal(Ref * sender)
{
	progess_bg->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(ImgPath::path_powerpoolbg_nomal));
}

void WimiProgress::ChangeLight(Ref * sender)
{
	progess_bg->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(ImgPath::path_powerpoolbg_light));
}
