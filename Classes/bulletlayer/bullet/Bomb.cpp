#include"Bomb.h"
void Bomb::BeginBomb(float radius, bool isAddCombo,Node*bombBody, Node*enemylayer)
{
	Vec2 bombPoint = bombBody->getPosition();//设置爆炸点
	bool _hit = false;
	for (int i = 0; i <DataOfGame::getInstance()->targetsVector.size(); ++i)
	{
		target* v_target = static_cast<target*>(DataOfGame::getInstance()->targetsVector.at(i));
		if (v_target == bombBody)
		{
			continue;
		}
		Vec2 targetPoint = v_target->getPosition();//获取屏幕上敌人的坐标
		float targetRadius = v_target->getContentSize().width / 2;//获取其他敌人的碰撞半径
		float c_circle = sqrt(pow(abs(targetPoint.x - bombPoint.x), 2) + pow(abs(targetPoint.y - bombPoint.y), 2));//圆心距
		if (c_circle < (radius + targetRadius))//发生碰撞
		{
			//TODO:被爆炸影响到的敌人的处理
			if (v_target->getBlood() <= 0)
			{ 
				//v_target->setBlood(0, isAddCombo);
				continue;
			}
			else
			{ 
				v_target->setBlood(0,isAddCombo);
				_hit = true;
			//if(isAddCombo)
			//DataOfGame::combo++;
			}
		}
	}
	if (_hit)
	{
		PanelLayer* panelLayer =static_cast<PanelLayer*>(enemylayer->getParent()->getChildByName("panelLayer"));
		panelLayer->showtextmessage(GameStringValue::getStringByKey("olddriver")->c_str());
	}
}