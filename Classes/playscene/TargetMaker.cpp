#include "TargetMaker.h"


TargetMaker::TargetMaker()
{
	
}

TargetMaker* TargetMaker::_instance = nullptr;
TargetMaker::~TargetMaker()
{
}
TargetMaker * TargetMaker::getinstance()
{
	if (_instance == nullptr)
		_instance = new TargetMaker();
	return _instance;
}
PhysicsBody* TargetMaker::createPcircle(float r)
{
	PhysicsBody* body = PhysicsBody::createCircle(r, PhysicsMaterial(0.0f, 1.0f, 0.0f));
	body->setMass(100000);
	body->setCategoryBitmask(TARGET_MASK);
	body->setContactTestBitmask(TARGET_CATE_MASK);
	body->setCollisionBitmask(TARGET_COLL_MASK);
	return body;
}
float TargetMaker::getEnemyAttribute(int kind, char* Attribute, std::string _jsonstring)
{
	float gid = -1;
	rapidjson::Document d;
	d.Parse<0>(_jsonstring.c_str());
	if (d.HasParseError())
	{
		CCLOG("jsonData Error");
		return -1;
	}
	char str_kind[5];
	sprintf(str_kind,"%d",kind);
	if (!d.HasMember(str_kind))
	{
		CCLOG("no nember of %s",str_kind);
		return -1;
	}
	rapidjson::Value& enemy_value = d[str_kind];
	if (!enemy_value.HasMember(Attribute))
	{
		CCLOG("no nember of %s", Attribute);
		return -1;
	}
	gid = enemy_value[Attribute].GetDouble();
	return gid;
}
void TargetMaker::loadenemytexture()
{
	//敌人纹理加载
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemytexture/meterenemy/meterenemytexture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemytexture/hardenemy/hardenemytexture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemytexture/propenemy/propenemytexture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemytexture/freedomenemy/freedomenemytexture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemytexture/bombenemy/bombenemytexture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemytexture/timidenemy/plist_timidenemytexture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemytexture/repairenemy/plist_repairenemytexture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemytexture/spyenemy/plist_spyenemy.plist");
}
void TargetMaker::unloadenemytexture()
{
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("enemytexture/meterenemy/meterenemytexture.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("enemytexture/hardenemy/hardenemytexture.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("enemytexture/propenemy/propenemytexture.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("enemytexture/freedomenemy/freedomenemytexture.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("enemytexture/bombenemy/bombenemytexture.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("enemytexture/timidenemy/plist_timidenemytexture.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("enemytexture/repairenemy/plist_repairenemytexture.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("enemytexture/spyenemy/plist_spyenemy.plist");
}
target* TargetMaker::Make_Target(int kind)
{
	target* C_target = nullptr;
	if (!FileUtils::getInstance()->isFileExist("enemyvalue/enemyvalue.json"))
	{
		CCLOG("file is not exist!");
	}
	std::string jsonstring = FileUtils::getInstance()->getStringFromFile("enemyvalue/enemyvalue.json");
	int id = getEnemyAttribute(kind,"id", jsonstring);
	int tkind = kind;
	int blood =  getEnemyAttribute(kind, "blood", jsonstring);
	float velocity = getEnemyAttribute(kind, "velocity", jsonstring);
	switch (kind)
	{
		case 1:
		{
			MeterTarget* meterTarget = MeterTarget::create("", id, kind, blood, velocity);
			if (meterTarget == nullptr)
				return nullptr;
			meterTarget->setHitScore(meterTarget->targetHitRule[0]);
			meterTarget->setHaveScore(meterTarget->targetKillRule[0]);
			meterTarget->setAnchorPoint(Vec2(0.5, 0.5));
			meterTarget->setPhysicsBody(createPcircle(meterTarget->getContentSize().height / 2));
			DataOfGame::getInstance()->targetsVector.pushBack(meterTarget);
			C_target = meterTarget;
		}
		break;
		case 2:
		{
			MeterTarget* HardTarget = MeterTarget::create("", id , kind , blood, velocity);
			if (HardTarget == nullptr)
				return nullptr;
			HardTarget->setSpriteFrame(SpriteFrameCache::getInstance()
				->getSpriteFrameByName("enemytexture/hardenemy/hardenemy_1.png"));
			auto animation = Animation::create();
			animation->addSpriteFrame(SpriteFrameCache::getInstance()
				->getSpriteFrameByName("enemytexture/hardenemy/hardenemy_1.png"));
			animation->addSpriteFrame(SpriteFrameCache::getInstance()
				->getSpriteFrameByName("enemytexture/hardenemy/hardenemy_2.png"));
			animation->setDelayPerUnit(1.0f / 24.0f);
			animation->setRestoreOriginalFrame(true);
			HardTarget->_runingAction = Animate::create(animation);
			HardTarget->runAction(RepeatForever::create(HardTarget->_runingAction));
			HardTarget->setHitScore(HardTarget->targetHitRule[3]);
			HardTarget->setHaveScore(HardTarget->targetKillRule[3]);
			HardTarget->setAnchorPoint(Vec2(0.5, 0.5));
			HardTarget->setPhysicsBody(createPcircle(HardTarget->getContentSize().height / 3));
			DataOfGame::getInstance()->targetsVector.pushBack(HardTarget);
			C_target = HardTarget;
		}
		break;
		case 3:
		{
			PropTarget* propTarget = PropTarget::create("", id, kind,blood,velocity);
			if (propTarget == nullptr)
				return  nullptr;
			propTarget->setHitScore(propTarget->targetHitRule[1]);
			propTarget->setHaveScore(propTarget->targetKillRule[1]);
			propTarget->setAnchorPoint(Vec2(0.5f, 0.5f));
			propTarget->setPhysicsBody(createPcircle(propTarget->getContentSize().height / 2));
			DataOfGame::getInstance()->targetsVector.pushBack(propTarget);
			C_target = propTarget;
		}
		break;
		case 4:
		{
			FreedomTarget* freedomTarget = FreedomTarget::create("", id, kind, blood, velocity);
			if (freedomTarget == nullptr)
				return  nullptr;
			freedomTarget->setHitScore(freedomTarget->targetHitRule[2]);
			freedomTarget->setHaveScore(freedomTarget->targetKillRule[2]);
			freedomTarget->setAnchorPoint(Vec2(0.5, 0.5));
			freedomTarget->setPhysicsBody(createPcircle(freedomTarget->getContentSize().height / 2));
			DataOfGame::getInstance()->targetsVector.pushBack(freedomTarget);
			C_target = freedomTarget;
		}
		break;
		case 5:
		{
			BombTarget*bombTarget = BombTarget::create("", id, kind, blood, velocity, 200);
			if (bombTarget == nullptr)
				return nullptr;
			bombTarget->setHitScore(bombTarget ->targetHitRule[5]);
			bombTarget->setHaveScore(bombTarget ->targetKillRule[5]);
			bombTarget->setAnchorPoint(Vec2(0.5f, 0.5f));
			bombTarget->setPhysicsBody(createPcircle(bombTarget->getContentSize().height / 2));
			DataOfGame::getInstance()->targetsVector.pushBack(bombTarget);
			C_target =bombTarget;
		}
		break;
		case 6:
		{
			TimidTarget* timidTarget = TimidTarget::create("", id, kind, blood, velocity);
			if (timidTarget == nullptr)
				return nullptr;
			timidTarget->setPhysicsBody(createPcircle(timidTarget->getContentSize().height/2));
			timidTarget->setHitScore(timidTarget->targetHitRule[5]);
			timidTarget->setHaveScore(timidTarget->targetKillRule[5]);
			DataOfGame::getInstance()->targetsVector.pushBack(timidTarget);
			C_target = timidTarget;
		}
		break;
		case 7:
		{
			SpyEnemy* spyEnemy = SpyEnemy::create();
			if (spyEnemy == nullptr)
			{
				return nullptr;
			}
			spyEnemy->setPhysicsBody(createPcircle(spyEnemy->getContentSize().height/2));
			DataOfGame::getInstance()->targetsVector.pushBack(spyEnemy);
			C_target = spyEnemy;
		}break;
		case 8:
		{
			RepairEnemy* repairEnemy = RepairEnemy::create();
			if (!repairEnemy)
				return nullptr;
			repairEnemy->setPhysicsBody(createPcircle(repairEnemy->getContentSize().height/2));
			DataOfGame::getInstance()->targetsVector.pushBack(repairEnemy);
			C_target = repairEnemy;
		}break;
		}

	return C_target;
}
Sprite * TargetMaker::loadenemyformainscene(int kind)
{
	if (!FileUtils::getInstance()->isFileExist("enemyvalue/enemyvalue.json"))
	{
		CCLOG("file is not exist!");
	}
	std::string jsonstring = FileUtils::getInstance()->getStringFromFile("enemyvalue/enemyvalue.json");
	int id = getEnemyAttribute(kind, "id", jsonstring);
	int tkind = kind;
	int blood = getEnemyAttribute(kind, "blood", jsonstring);
	float velocity = getEnemyAttribute(kind, "velocity", jsonstring);
	Sprite* _enemy = nullptr;
	switch (kind)
	{
	case 1:
	{
		_enemy = MeterTarget::create("", id, kind, blood, velocity);
	}
	break;
	case 2:
	{
		MeterTarget* HardTarget = MeterTarget::create("", id, kind, blood, velocity);
		if (HardTarget == nullptr)
			return nullptr;
		HardTarget->setSpriteFrame(SpriteFrameCache::getInstance()
			->getSpriteFrameByName("enemytexture/hardenemy/hardenemy_1.png"));
		auto animation = Animation::create();
		animation->addSpriteFrame(SpriteFrameCache::getInstance()
			->getSpriteFrameByName("enemytexture/hardenemy/hardenemy_1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()
			->getSpriteFrameByName("enemytexture/hardenemy/hardenemy_2.png"));
		animation->setDelayPerUnit(1.0f / 24.0f);
		animation->setRestoreOriginalFrame(true);
		HardTarget->_runingAction = Animate::create(animation);
		HardTarget->runAction(RepeatForever::create(HardTarget->_runingAction));
		_enemy = HardTarget;
	}
	break;
	case 3:
	{
		_enemy = PropTarget::create("", id, kind, blood, velocity);
	}
	break;
	case 4:
	{
		_enemy = FreedomTarget::create("", id, kind, blood, velocity);
	}
	break;
	case 5:
	{
		_enemy = BombTarget::create("", id, kind, blood, velocity, 200);
	}
	break;
	case 6:
	{
		_enemy = TimidTarget::create("", id, kind, blood, velocity);
	}
	break;
	case 7:
	{
		_enemy = SpyEnemy::create();
	}break;
	case 8:
	{
		_enemy = RepairEnemy::create();
	}break;
	}
	return _enemy;
}
ccBezierConfig* TargetMaker::Maker_bezier(Vec2 point[2], Vec2 endPoint)
{
	static ccBezierConfig br;//贝塞尔结构配置
	br.endPosition = endPoint;
	br.controlPoint_1 = point[0];
	br.controlPoint_2 = point[1];
	return &br;
}