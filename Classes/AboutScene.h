#pragma once
#include<cocos2d.h>
#include"cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace cocos2d::extension;
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;

class About :public cocos2d::Layer,public ScrollViewDelegate
{
public:
	static cocos2d::Scene * createScene();
	bool init();

private:
	ScrollView * scrollView;
	int x, page = 0, spiritwidth;
	virtual void scrollViewDidScroll(ScrollView * view) {};
	virtual void scrollViewDidZoom(ScrollView * view) {};
	bool onTouchBegan(Touch* touch, Event* event);//触摸开始方法
	void onTouchMoved(Touch* touch, Event* event);//触摸移动方法
	void onTouchEnded(Touch* touch, Event* event);//触摸结束方法
	void adjustScrollView();
	void onMouseUp(Event * event);
	void onMouseDown(Event *event);
	void menuOkCallback(Ref *pSender);
//public:
	CREATE_FUNC(About);

};
