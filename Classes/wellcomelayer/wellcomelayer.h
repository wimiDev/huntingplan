#ifndef __WELLCOMELAYER_WELLCOMELAYER_H_
#define __WELLCOMELAYER_WELLCOMELAYER_H_

#include"cocos2d.h"
using namespace cocos2d;
#include"cocostudio/CocoStudio.h"
#include"cocostudio/CocoLoader.h"
#include"ui/UIButton.h"
#include"ui/UIText.h"
#include"ui/UIPageView.h"
#include"DataOfGame.h"
#include"gameui/GameUi.h"
#include"playscene/PlayScene.h"
#include"panellayer/PanelLayer.h"

class WellComeLayer
	:public Layer
{
public:
	virtual bool init();
	static WellComeLayer* create(int _module);
	//�ļ����������Ҫչʾ������
	//*_module��Ϸģʽ
	//*_pageչʾ�ĵڼ�ҳ
	//*_attributeҪ��õ����ԣ�1--imgpath,2--text,3--end
	std::string getatt(int _module,int _page,int _attribute);
	//�ļ����������Ҫչʾ������
	std::string getcoursetext(int _module,int _page);
	//װ��pageview������
	void loadpagedata();
public:
	int* _gamestate;
private:
	void buttonskipcallback(Ref*sender, ui::Widget::TouchEventType type);
private:
	ui::PageView* _pageview;
	ui::Button* _buttonskip;
	ui::Text _newcourse;
	ui::Text _coursetext;
	Sprite* _bg;
	Sprite* _shade;
	Sprite _img;
	int _module;
	int _page;
};

#endif // !__WELLCOMELAYER_WELLCOMELAYER_H_
