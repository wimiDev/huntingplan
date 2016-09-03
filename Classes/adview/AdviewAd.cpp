#include "AdviewAd.h"

AdviewAd::AdviewAd() {
	// TODO Auto-generated constructor stub
}

AdviewAd::~AdviewAd() {
	// TODO Auto-generated destructor stub
}
void AdviewAd::showBanner() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo showBanner;
	//第二个参数 "org/cocos2dx/cpp/AdViewCocos2dx"表示引入的类名
	//第三个参数 "showBannerStatic"表示该类下需要执行的方法
	//第四个参数 "()V" 表示"showBannerStatic"不需要传入参数并且返回值类型void类型
	bool isHave = JniHelper::getStaticMethodInfo(showBanner,"org/cocos2dx/cpp/AppActivity","showBannerStatic","()V");
	if (!isHave) {
		CCLog("jni:showBannerStatic false");
	} else {
		showBanner.env->CallStaticVoidMethod(showBanner.classID, showBanner.methodID);
	}
#endif
}
void AdviewAd::showBanner2() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo showBanner2;
	bool isHave = JniHelper::getStaticMethodInfo(showBanner2,"org/cocos2dx/cpp/AppActivity","showBanner2Static","()V");
	if (!isHave) {
		CCLog("jni:showBannerStatic false");
	} else {
		showBanner2.env->CallStaticVoidMethod(showBanner2.classID, showBanner2.methodID);
	}
#endif
}
void AdviewAd::close() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo close;
	bool isHave = JniHelper::getStaticMethodInfo(close,"org/cocos2dx/cpp/AppActivity","close","()V");
	if (!isHave) {
		CCLog("jni:hideBannerStatic false");
	} else {
		CCLog("jni:hideBannerStatic true");

		close.env->CallStaticVoidMethod(close.classID, close.methodID);
	}
#endif
}

void AdviewAd::requestInstl() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo close;
	bool isHave = JniHelper::getStaticMethodInfo(close,"org/cocos2dx/cpp/AppActivity","requestInstlStatic","()V");
	if (!isHave) {
		CCLog("jni:requestInstlStatic false");
	} else {
		CCLog("jni:requestInstlStatic true");

		close.env->CallStaticVoidMethod(close.classID, close.methodID);
	}
#endif
}

void AdviewAd::showInstl() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo close;
	bool isHave = JniHelper::getStaticMethodInfo(close,"org/cocos2dx/cpp/AppActivity","showInstlStatic","()V");
	if (!isHave) {
		CCLog("jni:showInstlStatic false");
	} else {
		CCLog("jni:showInstlStatic true");

		close.env->CallStaticVoidMethod(close.classID, close.methodID);
	}
#endif
}

void AdviewAd::requestSpread() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo close;
	bool isHave = JniHelper::getStaticMethodInfo(close,"org/cocos2dx/cpp/AppActivity","requestSpreadStatic","()V");
	if (!isHave) {
		CCLog("jni:showInstlStatic false");
	} else {
		CCLog("jni:showInstlStatic true");

		close.env->CallStaticVoidMethod(close.classID, close.methodID);
	}
#endif
}

