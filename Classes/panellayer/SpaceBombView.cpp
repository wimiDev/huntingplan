#include"SpaceBombView.h"

SpaceBombView* SpaceBombView::createSpaceBombView()
{
	SpaceBombView* bombbulletview = new SpaceBombView();
	bombbulletview->BulletViewNode = CSLoader::createNode("bulletselect/bombbullet.csb");
	bombbulletview->sprite_SpaceBombView = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(bombbulletview->BulletViewNode,
		std::string("sprite_bombbulletbg")));
	bombbulletview->button_bombBullet = static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(bombbulletview->BulletViewNode,
		std::string("button_bombbullet")));
	bombbulletview->button_bombBullet->addTouchEventListener(CC_CALLBACK_2(SpaceBombView::selectCallback,bombbulletview));
	bombbulletview->ta_bulletNum= static_cast<ui::TextAtlas*>(DataOfGame::getInstance()->seekNodebyName(bombbulletview->BulletViewNode,
		std::string("AtlasLabel_bulletnum")));
	auto rotate = RotateBy::create(2.5f, 90);
	bombbulletview->sprite_SpaceBombView->runAction(RepeatForever::create(rotate));

	return bombbulletview;
}
void SpaceBombView::selectCallback(Ref*sender,ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{ 
		Size visiableSize = Director::getInstance()->getVisibleSize();
		PanelLayer* panelLayer = static_cast<PanelLayer*>(BulletViewNode->getParent());
		panelLayer->resetCombo();
		sprite_SpaceBombView->setScale(1.0f);
		for (int i = 0; i < DataOfGame::getInstance()->targetsVector.size(); ++i)
		{
			FireBomb* fireBomb = FireBomb::create();
			fireBomb->setPhysicsBody(fireBomb->createRect(fireBomb->getContentSize()));
			float p_X = 0;
			p_X = random(-(int)(visiableSize.width/2),(int)(visiableSize.width/5));
			fireBomb->setPosition(p_X,-303);
			this->BulletViewNode->getParent()->addChild(fireBomb,5);
		}
		
	}
}
void SpaceBombView::setBulletNum(int num)
{
	if (this->ta_bulletNum)
	{
		char str_num[20];
		sprintf(str_num,"%d",num);
		ta_bulletNum->setString(str_num);
	}
}

void SpaceBombView::setIsRotate(bool isRotate)
{
	if (isRotate)
	{
		auto rotate = RotateBy::create(1.0f,90);
		ScaleTo* scaleBig = ScaleTo::create(0.3f,1.3f);
		ScaleTo*scaleNomal = ScaleTo::create(0.2f,1.0f);
		if(sprite_SpaceBombView)
		sprite_SpaceBombView->runAction(RepeatForever::create(Spawn::create(rotate,Sequence::create(scaleBig,scaleNomal,nullptr),nullptr)));
		button_bombBullet->setEnabled(true);
	}
	else
	{
		if (sprite_SpaceBombView)
			sprite_SpaceBombView->stopAllActions();
		button_bombBullet->setEnabled(false);
	}
}
