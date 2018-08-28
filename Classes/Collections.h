#pragma once
#include<cocos2d.h>
#include"cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace cocos2d::extension;
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;

class Collections :public cocos2d::Layer, public ScrollViewDelegate
{
public:
	static cocos2d::Scene * createScene();
	bool init();
	int numOfCollections;
	static void addCollections(int n);

private:
	Layer *layer;
	ScrollView * scrollView;
	int x, page = 0, spiritwidth;
	virtual void scrollViewDidScroll(ScrollView * view) {};
	virtual void scrollViewDidZoom(ScrollView * view) {};
	void adjustScrollView();
	void onMouseUp(Event * event);
	void onMouseDown(Event *event);
	void menuOkCallback(Ref *pSender);
	void showCollections();
	//public:
	CREATE_FUNC(Collections);

};
