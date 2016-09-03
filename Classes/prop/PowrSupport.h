
#ifndef __POWERSUPPORT_H_
#define __POWERSUPPORT_H_
#include"cocos2d.h"
#include"prop/Prop.h"
#include"DataOfGame.h"
#include"gameui/GameUi.h"
#include"panellayer/gameinfotext.h"
#include"panellayer/PanelLayer.h"

class PowerSupport
	: public Prop
{
public:
	PowerSupport();
	~PowerSupport();
	CC_SYNTHESIZE(int, _supportTime, supportTime);
	static PowerSupport* getinstance();
	void startSupport(Node*Scene);
	void endSupport();
	void showSupportTime(int _time,Node*scene);
	void removeSupportTime(Ref* sender);
};
#endif