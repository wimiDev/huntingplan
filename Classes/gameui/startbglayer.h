#ifndef __GAMEUI_SRARTBGLAYER_H_
#define __GAMEUI_SRARTBGLAYER_H_
#include"cocos2d.h"
using namespace cocos2d;
//*������
class StartBgLayer
	:public Layer
{
public:
	StartBgLayer();
	~StartBgLayer();
	bool init();
	static StartBgLayer* create();
	//������ǵ�����
	void fullStartToLayer(int _num);
public:
	int _startIndex;
private:
	Vector<Sprite*>* _startvector;
};
#endif