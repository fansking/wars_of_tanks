#pragma once
#include<cocos2d.h>
#include"cocos-ext.h"
USING_NS_CC_EXT;
using namespace cocos2d::extension;
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;

class About :public cocos2d::Layer,public ScrollViewDelegate
{
public:
	ScrollView * scrollView;
	static cocos2d::Scene * createScene();
	bool init();
	void menuSoundToggleCallback(Ref *pSender);
	void menuMusicToggleCallback(Ref *pSender);
	void menuOkCallback(Ref *pSender);
	void musicChanged(Ref *sender, Control::EventType);
	void soundChanged(Ref *sender, Control::EventType);

	virtual void scrollViewDidScroll(ScrollView * view) {};
	virtual void scrollViewDidZoom(ScrollView * view) {};


	CREATE_FUNC(About);

};
