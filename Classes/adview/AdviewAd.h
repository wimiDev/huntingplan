#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include <jni.h>
//#include "platform/android/jni/JniHelper.h"
//#include <android/log.h>
#include "cocos2d.h"
#endif
#ifndef ADVIEWAD_H_
#define ADVIEWAD_H_
using namespace cocos2d;
class AdviewAd {
public:
	AdviewAd();
	virtual ~AdviewAd();
	static void showBanner();
	static void showBanner2();
	static void requestInstl();
	static void showInstl();
	static void requestSpread();
	static void close();
};

#endif /* ADVIEWAD_H_ */
