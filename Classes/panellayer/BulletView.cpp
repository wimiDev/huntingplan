#include"BulletView.h"

BulletView * BulletView::create(const char * path)
{
	BulletView* bulletview = new BulletView();
	bulletview->initWithFile(path);
	bulletview->_bulletnum = ui::Text::create("9999", "font/fangzhengzongyijianti.ttf", 48);
	bulletview->_bulletnum->setTextColor(Color4B::GREEN);
	bulletview->_bulletnum->setPosition(Vec2(104.13, 25.02));
	return bulletview;
}

BulletView * BulletView::create(Node * _rootnode)
{
	BulletView* _bulletview = new BulletView();
	_bulletview->init();
	_bulletview->_spritebg = static_cast<Sprite*>
	(DataOfGame::getInstance()->seekNodebyName(_rootnode,"sprite_bulletnumpanel"));
	_bulletview->_bulletnum = static_cast<ui::Text*>
		(DataOfGame::getInstance()->seekNodebyName(_rootnode, "text_bulletnum"));
	_bulletview->_slock= static_cast<Sprite*>
		(DataOfGame::getInstance()->seekNodebyName(_rootnode, "sprite_lock"));
	return _bulletview;
}

BulletView * BulletView::create(SpriteFrame * _spriteFrame)
{
	BulletView* _bulletview = new BulletView();
	_bulletview->initWithSpriteFrame(_spriteFrame);
	_bulletview->_bulletnum = ui::Text::create("9999", "font/fangzhengzongyijianti.ttf", 48);
	_bulletview->_bulletnum->setTextColor(Color4B::GREEN);
	_bulletview->_bulletnum->setPosition(Vec2(104.13, 25.02));
	_bulletview->addChild(_bulletview->_bulletnum);
	return _bulletview;
}

void BulletView::SetBulletNum(int num)
{
	if (_num == num)
	{
		return;
	}
	_num = num;
	_bulletnum->stopAllActions();
	ScaleTo* _scalebig = ScaleTo::create(0.3f, 1.2f);
	CCCallFuncN* _changenum = CCCallFuncN::create([=](Ref*sender) 
	{
		char _strnum[20];
		sprintf(_strnum, "%d", _num);
		_bulletnum->setString(_strnum);
	});
	ScaleTo* _scalenomal = ScaleTo::create(0.2f,1.0f);
	_bulletnum->runAction(Sequence::create(_changenum,_scalebig,_scalenomal,nullptr));
}

void BulletView::setlock(bool _islock)
{
	if (_islock)
	{
		_slock->setVisible(true);
	}
	else
	{
		_slock->setVisible(false);
	}
}
