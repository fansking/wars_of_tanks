#include "Collections.h"
#include <iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<string>
#include"MyUtility.h"
USING_NS_CC;
#define ADJUST_ANIM_VELOCITY 3;
Scene *Collections::createScene()
{
	auto scene = Scene::create();
	auto layer = Collections::create();
	scene->addChild(layer);
	return scene;
}
const int nCount = 3;
bool Collections::init()
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
	layer = Layer::create();
	for (int i = 0; i < nCount; i++) {
		auto sprite = Sprite::create("menu/pause_bg2.png");
		sprite->setPosition(Vec2(visibleSize.width / 2 + i * (sprite->getContentSize().width + 10), visibleSize.height / 2));
		//layer->addChild(sprite);
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


	auto listener2 = EventListenerMouse::create();
	listener2->onMouseUp = [](Event * event) {
		//log("mouse");
	};
	listener2->onMouseUp = CC_CALLBACK_1(Collections::onMouseUp, this);
	listener2->onMouseDown = CC_CALLBACK_1(Collections::onMouseDown, this);

	EventDispatcher * eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

	auto okMenuItem = MenuItemImage::create(
		"UI/closebt.png", "UI/closebt_h.png", CC_CALLBACK_1(Collections::menuOkCallback, this));
	okMenuItem->setPosition(origin.x + visibleSize.width - 30, origin.y + visibleSize.height - 30);
	okMenuItem->setScale(0.6);
	Menu *mn = Menu::create(okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);
	
	//读取并显示成就
	CCSpriteFrameCache * cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("UI/UI_achievement.plist");
	cache->addSpriteFramesWithFile("UI/UI_gameover.plist");
	showCollections();
	return true;
}

void Collections::menuOkCallback(Ref *pSender)
{
	Director::getInstance()->popScene();
}
void Collections::onMouseDown(Event* event) {
	x = scrollView->getContentOffset().x;
	log("%d", x);
}
void Collections::onMouseUp(Event * event) {
	adjustScrollView();
}
void Collections::adjustScrollView() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	scrollView->unscheduleAllSelectors();
	int layerx = scrollView->getContentOffset().x;
	int offset = (int)layerx % (int)visibleSize.width;
	Point adjustPos;
	float adjustAnimDelay;

	float Oldlayerx = -(page*visibleSize.width);

	if ((layerx - x) >= visibleSize.width / 5) {
		page--;
		if (page < 0)
			page = 0;

	}
	else if ((x - layerx) >= visibleSize.width / 5)
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

int mylocation[4] = { 225,75,-75,-225 };
void Collections::showCollections() {
	auto visiblesize = Director::getInstance()->getVisibleSize();
	std::ifstream readName("CollectionNames.txt");
	std::ifstream readData("CollectionData.txt");
	readName >> numOfCollections;
	readData >> numOfCollections;
	std::string tmp;
	std::getline(readName, tmp);
	int mynum = 0;
	for (int i = 0; i < (numOfCollections-1) / 4+1; i++) {
		for (int j = 0; j < 4; j++) {
			Sprite* sp = Sprite::createWithSpriteFrameName("background_box1.png");
			sp->setScale(1.3);
			sp->setPosition(Vec2(visiblesize.width / 2+ i * spiritwidth, visiblesize.height / 2+mylocation[j]));
			layer->addChild(sp);
			std::getline(readName, tmp);
			auto text1 = Label::createWithTTF(MyUtility::gbk_2_utf8(tmp), "fonts/minijtj.ttf", 35);
			text1->setPosition(Vec2(visiblesize.width / 2 + i * spiritwidth, visiblesize.height / 2 + mylocation[j]));
			text1->setColor(Color3B(255, 255, 255));
			layer->addChild(text1);
			bool hasDone;
			readData >> hasDone;
			if (hasDone) {
				Sprite* sp = Sprite::createWithSpriteFrameName("stamp_wancheng.png");
				sp->setPosition(Vec2(visiblesize.width / 2 + i * spiritwidth+350, visiblesize.height / 2 + mylocation[j]));
				layer->addChild(sp);
			}
			else {
				Sprite* sp = Sprite::createWithSpriteFrameName("stamp_weiwancheng.png");
				sp->setPosition(Vec2(visiblesize.width / 2 + i * spiritwidth + 350, visiblesize.height / 2 + mylocation[j]));
				layer->addChild(sp);
			}
			mynum++;
			if (mynum == numOfCollections) return;
		}
	}
}

void Collections::addCollections(int x) {
	int n, m[10];
	std::ifstream readData("CollectionData.txt");
	readData >> n;
	for (int i = 0; i < n; i++) readData >> m[i];
	m[x - 1] = 1;
	std::fstream outData("CollectionData.txt", ios::out | ios::trunc);
	outData << n << endl;
	for (int i = 0; i < n; i++) {
		outData << m[i] << " ";
	}
}




