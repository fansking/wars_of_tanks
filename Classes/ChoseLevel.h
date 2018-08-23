#pragma once
#include<cocos2d.h>
#include"cocos-ext.h"
USING_NS_CC_EXT;
using namespace cocos2d::extension;
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
class ChoseLevel :public cocos2d::Layer
{
public:
	static int _PlayerModel;
	static cocos2d::Scene * createScene();
	bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuSingleCallback(cocos2d::Ref* pSender);
	void menuDoubleCallback(cocos2d::Ref* pSender);
	void menuEnterGameCallback(cocos2d::Ref* pSender);
private:
	void init2();

	CREATE_FUNC(ChoseLevel);

};