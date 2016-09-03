#ifndef __BULLETLAYER_BULLETLAYER_H_
#define __BULLETLAYER_BULLETLAYER_H_
#include"cocos2d.h"
#include"bullet/MeterBullet.h"
#include"panellayer/PanelLayer.h"
#include"particle/bombparticle.h"

using namespace cocos2d;
/*
*这个类是炮弹层
*包含炮弹层创建初始化
*create by wimidev
*/
class BulletLayer
	:public Layer
{
public:
	//*创建炮弹层
	static BulletLayer*create();
	//*炮弹层初始化
	bool init();
	//*添加炮弹
	void addBullet();
	//*准备发射
	void readyShoot(Vec2 point);
	//0，0坐标转化成十字坐标
	Vec2 ConverPoint(float x, float y);
private:
	//*炮塔旋转到位
	void turretRotateFinish(Ref*sender);
	//*添加触摸特效
	void addAimCircle(Vec2 point);
};

#endif
