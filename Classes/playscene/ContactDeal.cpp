#include "ContactDeal.h"


ContactDeal::ContactDeal()
{
}


ContactDeal::~ContactDeal()
{
}
void ContactDeal::bulletContact(Node*A, Node*B, Node*scene)
{
	target* _target = static_cast<target*>(A);
	Bullet* _bullet = static_cast<Bullet*>(B);
	int bullet_kind = _bullet->getKind();
	switch (bullet_kind)
	{
	case 1:
	{
		_bullet->setBlood(_bullet->getBlood() - 1);
		BombParticle* _explosion = BombParticle::create("particle/particle_bullet_b1.plist");
	_explosion->setPosition(_bullet->getPosition());
	_bullet->getParent()->addChild(_explosion);
		if (_bullet->getBlood() <= 0)
		{
			DataOfGame::getInstance()->recycle_bin.pushBack(_bullet);
		}
	}
	break;
	case 2:
	{

	}
	break;
	case 3:
	{

	}
	break;
	case 4:
	{
		FireBomb* fireBomb = static_cast<FireBomb*>(B);
		fireBomb->setBlood(fireBomb->getBlood()-1);
		if (fireBomb->getBlood() <= 0)
		{
			if (fireBomb->getFloEnemy()!=nullptr)
			{
				target* enemy= fireBomb->getFloEnemy();
				enemy->setisFlo(false);
			}
			DataOfGame::getInstance()->recycle_bin.pushBack(fireBomb);
		}
		BombParticle* _explosion = BombParticle::create("particle/particle_bullet_b2.plist");
		_explosion->setPosition(_bullet->getPosition());
		_bullet->getParent()->addChild(_explosion);
	}break;
	default:
		break;
	}
	
}

void ContactDeal::targetContact(Node*A, Node*B, Node*scene)
{
	target* _target = static_cast<target*>(A);
	Bullet* _bullet = static_cast<Bullet*>(B);
	int target_kind = _target->getKind();
	if(_bullet->getKind()!=4)
	{
		if(_target->getBlood())
		_target->setBlood(_target->getBlood() - _bullet->getKillability(),true); 
		if (_target->getBlood() <= 0)
		{
			PlayScene* _playscene =static_cast<PlayScene*> (_bullet->getParent()->getParent());
			PanelLayer*panelLayer =static_cast<PanelLayer*>(_playscene->getChildByName("panelLayer"));
			BgLayer* bglayer= static_cast<BgLayer*>
				(_playscene->getChildByName("bgLayer"));
			panelLayer->addCombo(1);
			bglayer->killAction();
		}
	}
	else
	{ 
		if (_target->getBlood())
		_target->setBlood(_target->getBlood() - _bullet->getKillability(), false);
	}

}
void ContactDeal::AddProp(int _propId,Node*_target)
{

}
void ContactDeal::AddpropAction(int kind,Node*_target,Node*playScene)
{
	
}
void ContactDeal::bomb(float radius,int maxSize,Node*bombBody, Node*playScene)
{
	//Vec2 bombPoint = bombBody->getPosition();//设置爆炸点
	//for (int i = 0; i < DataOfGame::getInstance()->targetsVector.size(); ++i)
	//{
	//	target* v_target = static_cast<target*>(DataOfGame::getInstance()->targetsVector.at(i));
	//	if (v_target == bombBody)
	//	{
	//		continue;
	//	}
	//	Vec2 targetPoint = v_target->getPosition();//获取屏幕上敌人的坐标
	//	float targetRadius = v_target->getContentSize().width / 2;//获取其他敌人的碰撞半径
	//	float c_circle = sqrt(pow(abs(targetPoint.x - bombPoint.x), 2) + pow(abs(targetPoint.y - bombPoint.y), 2));//圆心距
	//	if (c_circle < (radius + targetRadius))//发生碰撞
	//	{
	//		//TODO:被爆炸影响到的敌人的处理
	//		v_target->setBlood(0,true);
	//		GameUi::score->addScoreOnScene(v_target->getKillScore(), playScene, v_target->getPosition());
	//		DataOfGame::getInstance()->recycle_bin.pushBack(v_target);
	//		DataOfGame::getInstance()->combo++;
	//	}
	//}
	//Audio::PlayEffect(Audio::path_target1Bomb_eff);
	//DataOfGame::getInstance()->addCombo(0,playScene);
}
