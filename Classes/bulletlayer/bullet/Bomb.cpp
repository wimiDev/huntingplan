#include"Bomb.h"
void Bomb::BeginBomb(float radius, bool isAddCombo,Node*bombBody, Node*enemylayer)
{
	Vec2 bombPoint = bombBody->getPosition();//���ñ�ը��
	bool _hit = false;
	for (int i = 0; i <DataOfGame::getInstance()->targetsVector.size(); ++i)
	{
		target* v_target = static_cast<target*>(DataOfGame::getInstance()->targetsVector.at(i));
		if (v_target == bombBody)
		{
			continue;
		}
		Vec2 targetPoint = v_target->getPosition();//��ȡ��Ļ�ϵ��˵�����
		float targetRadius = v_target->getContentSize().width / 2;//��ȡ�������˵���ײ�뾶
		float c_circle = sqrt(pow(abs(targetPoint.x - bombPoint.x), 2) + pow(abs(targetPoint.y - bombPoint.y), 2));//Բ�ľ�
		if (c_circle < (radius + targetRadius))//������ײ
		{
			//TODO:����ըӰ�쵽�ĵ��˵Ĵ���
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