#include "BulletLayer.h"

BulletLayer * BulletLayer::create()
{
	BulletLayer* bulletLayer = new BulletLayer();
	bulletLayer->init();
	return bulletLayer;
}

bool BulletLayer::init()
{
	if(!Layer::init())
	return false;
	Size winSize = Director::getInstance()->getWinSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bullet/meterbullet/meterbullettexture.plist");
	return true;
}

void BulletLayer::addBullet()
{
	PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
	PanelLayer*panelLayer = static_cast<PanelLayer*>(playScene->getChildByName("panelLayer"));
	Size _visiablesize = Director::getInstance()->getVisibleSize();
	Vec2 _org = Director::getInstance()->getVisibleOrigin();
	Turret* turret = panelLayer->turret;
	float rota = turret->getRotation();
	if (DataOfGame::getInstance()->_bulletTotle > 0 || 
		playScene->_propList[2]>0 ||
		playScene->_gameModule==4)
	{
		turret->Fire();
		MeterBullet*_bullet = MeterBullet::create("", 0, 1, 1, 1, 5, rota);
		_bullet->setPhysicsBody(_bullet->createRect(_bullet->getContentSize()));
		_bullet->setID(1);
		_bullet->setRotation(rota);
		_bullet->setAnchorPoint(Vec2(0.5f, 0.5f));
		_bullet->setPosition( 0,
			-_visiablesize.height/2 + panelLayer->_connonPool->getContentSize().height /5);
		this->addChild(_bullet);
		DataOfGame::getInstance()->bulletsVector.pushBack(_bullet);
		_bullet->shootIt();
		if (playScene->_propList[2] <= 0)//如果没有能量道具则会计算炮弹的数量
		{
			_bullet->setID(0);
			if (playScene->_gameModule != 4)
			{
				//减炮弹的数量
				DataOfGame::getInstance()->_bulletTotle--;
			}
		}
		Audio::getInstance()->playeffectbykey("meterbullet");
	}
}

void BulletLayer::readyShoot(Vec2 point)
{
	PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
	PanelLayer*panelLayer = static_cast<PanelLayer*>(playScene->getChildByName("panelLayer"));
	Turret* turret = panelLayer->turret;
	Vec2 _org = Director::getInstance()->getVisibleOrigin();
	addAimCircle(ConverPoint(point.x, point.y));
	Size _visiblesize = Director::getInstance()->getVisibleSize();
	Size _winsize = Director::getInstance()->getWinSize();
	Vec2 _point2 = Vec2(_winsize.width / 2, _org.y);
	float rotate = turret->GetRotate(point, _point2);
	turret->Rotate(rotate, CCCallFuncN::create(CC_CALLBACK_1(BulletLayer::turretRotateFinish, this)));
}

Vec2 BulletLayer::ConverPoint(float x, float y)
{
	Size winSize = Director::getInstance()->getWinSize();
	Vec2 point = Vec2();
	if (x >= winSize.width / 2)
	{
		point.x = x - winSize.width / 2;
	}
	else
	{
		point.x = -winSize.width / 2 + x;
	}
	if (y >= winSize.height / 2)
	{
		point.y = y - winSize.height / 2;
	}
	else
	{
		point.y = -winSize.height / 2+ y;
	}
	return point;
}
void BulletLayer::turretRotateFinish(Ref * sender)
{
	addBullet();
}

void BulletLayer::addAimCircle(Vec2 point)
{
	/*AimCircle* aim = AimCircle::create();
	aim->setPosition(point);
	this->addChild(aim);
	aim->Action();*/
	BombParticle* _explosion = BombParticle::create("particle/particle_click1.plist");
	_explosion->setPosition(point);
	this->addChild(_explosion);
}

