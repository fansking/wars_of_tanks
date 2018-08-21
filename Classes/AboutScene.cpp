#include "AboutScene.h"
USING_NS_CC;

Scene *About::createScene()
{
	auto scene = Scene::create();
	auto layer = About::create();
	scene->addChild(layer);
	return scene;
}

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

	const int nCount = 3;
	auto layer = Layer::create();
	for (int i = 0; i < nCount; i++) {
		auto sprite = Sprite::create("menu/pause_bg1.png");
		sprite->setPosition(Vec2(visibleSize.width / 2 + i * visibleSize.width, visibleSize.height / 2));
		layer->addChild(sprite);
	}
	layer->setContentSize(Size(visibleSize.width*nCount, visibleSize.height));
	scrollView = ScrollView::create(Size(visibleSize.width, visibleSize.height));
	scrollView->setContainer(layer);
	scrollView->setBounceable(false);
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollView->setDelegate(this);

	this->addChild(scrollView);


	return true;
}






