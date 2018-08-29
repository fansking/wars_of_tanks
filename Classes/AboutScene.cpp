#include "AboutScene.h"
#include<vector>
#include<string>
USING_NS_CC;
#define ADJUST_ANIM_VELOCITY 3;
Scene *About::createScene()
{
	auto scene = Scene::create();
	auto layer = About::create();
	scene->addChild(layer);
	return scene;
}
const int nCount = 2;
bool About::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::create("menu/bg_new.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);

	//设置容器及精灵
	auto layer = Layer::create();
	for (int i = 0; i < nCount; i++) {
		auto sprite = Sprite::create("menu/About"+std::to_string(i+1)+".png");
		sprite->setPosition(Vec2(visibleSize.width / 2 + i * (sprite->getContentSize().width+10), visibleSize.height / 2));
		layer->addChild(sprite);
		spiritwidth = sprite->getContentSize().width;
	}
	layer->setContentSize(Size(visibleSize.width*nCount, visibleSize.height));
	scrollView = ScrollView::create(Size(visibleSize.width, visibleSize.height));
	scrollView->setContainer(layer);
	scrollView->setBounceable(true);
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollView->setDelegate(this);
	//scrollView->setContentOffsetInDuration(Vec2(-visibleSize.width, 0), 1.0);
	this->addChild(scrollView);


	//创建屏触摸监听事件
	auto listener = EventListenerTouchOneByOne::create();
	//设置可向下传递
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(About::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(About::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(About::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	auto listener2 = EventListenerMouse::create();
	listener2->onMouseUp = [](Event * event) {
		//log("mouse");
	};
	listener2->onMouseUp = CC_CALLBACK_1(About::onMouseUp, this);
	listener2->onMouseDown = CC_CALLBACK_1(About::onMouseDown, this);
	
	EventDispatcher * eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

	auto okMenuItem = MenuItemImage::create(
		"UI/closebt.png", "UI/closebt_h.png", CC_CALLBACK_1(About::menuOkCallback, this));
	okMenuItem->setPosition(origin.x + visibleSize.width -30, origin.y + visibleSize.height -30);
	okMenuItem->setScale(0.6);
	Menu *mn = Menu::create(okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

	return true;
}

void About::menuOkCallback(Ref *pSender)
{
	Director::getInstance()->popScene();
}



bool About::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}
void About::onTouchMoved(Touch* touch, Event* event)
{
	x = scrollView->getContentOffset().x;//x轴的偏移量
	CCLOG("%d", x);
}
void About::onTouchEnded(Touch* touch, Event* event)
{
	log("asdasdasda");
	// 关闭CCScrollView中的自调整
	scrollView->unscheduleAllSelectors();
	//矫正view的位置
	int offset = x % 200;
	int num = x / 200;
	Point adjustPos;
	float adjustAnimDelay;
	if (offset <= -100) {
		adjustPos = Point((num - 1) * 200, scrollView->getContentOffset().y);
		adjustAnimDelay = (offset*(-1) % 100) / 600;
	}

	if (offset <= 0 && offset>-100) {
		adjustPos = Point(num * 200, scrollView->getContentOffset().y);
		adjustAnimDelay = (offset*(-1) % 100) / 600;
	}

	if (offset>0) {
		adjustPos = Point(0, scrollView->getContentOffset().y);
		adjustAnimDelay = (offset*(1) % 100) / 600;
	}

	if (x <= -1400) {
		adjustPos = Point(-1400, scrollView->getContentOffset().y);
		adjustAnimDelay = (offset*(-1) % 100) / 600;
	}

	adjustAnimDelay = 0.7;
	scrollView->setContentOffsetInDuration(adjustPos, adjustAnimDelay);// 调整位置
}
void About::onMouseDown(Event* event) {
	x = scrollView->getContentOffset().x;
	log("%d", x);
}
void About::onMouseUp(Event * event) {
	adjustScrollView();
}
void About::adjustScrollView() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	scrollView->unscheduleAllSelectors();
	int layerx = scrollView->getContentOffset().x;
	int offset = (int)layerx % (int)visibleSize.width;
	Point adjustPos;
	float adjustAnimDelay;

	float Oldlayerx = -(page*visibleSize.width);

	if ((layerx-x)>=visibleSize.width/5){
		page--;
		if (page < 0)
			page = 0;

	}
	else if((x-layerx)>=visibleSize.width/5)
	{
		page++;
		if (page >= nCount) {
			page = nCount - 1;
		}
	}
	adjustPos = Vec2(-spiritwidth * page, 0);
	adjustAnimDelay = (float)abs(offset) / ADJUST_ANIM_VELOCITY;
	scrollView->setContentOffsetInDuration(adjustPos, 0.5);
}





