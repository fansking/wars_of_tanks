#include "ChoseLevel.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;

int ChoseLevel::_PlayerModel = 0;
Scene *ChoseLevel::createScene()
{
	auto scene = Scene::create();
	auto layer = ChoseLevel::create();
	scene->addChild(layer);
	return scene;
}

bool ChoseLevel::init() {
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::create("menu/Chapter_1.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);

	auto item1 = MenuItemImage::create("UI/Single2.png", "UI/Single.png", CC_CALLBACK_1(ChoseLevel::menuSingleCallback, this));
	item1->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+60));

	auto item2 = MenuItemImage::create("UI/double2.png", "UI/double.png", CC_CALLBACK_1(ChoseLevel::menuDoubleCallback, this));
	item2->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2-60));

	auto menu = Menu::create( item1,item2,NULL);
	menu->setTag(1);
	menu->setPosition(Vec2(0, 0));
	this->addChild(menu);

}

int myPosition[20][2] = { {178,408},{340,284},{544,403},{727,565},{855,425},{737,271},{818,108},{1056,226} };
int num = 8, now = 5;
void ChoseLevel::init2() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto item1 = MenuItemImage::create("UI/ReturBig.png", "UI/ReturnSmall.png", CC_CALLBACK_1(ChoseLevel::menuCloseCallback, this));
	item1->setScale(0.6);
	item1->setAnchorPoint(Vec2(0, 1));
	item1->setPosition(Vec2(5,visibleSize.height-5));
	auto menu = Menu::create(item1,NULL);
	for (int i = 0; i < now; i++) {
		auto item = MenuItemImage::create("UI/stageGoldBig.png", "UI/stageGoldSmall.png", CC_CALLBACK_1(ChoseLevel::menuEnterGameCallback, this));
		item->setPosition(Vec2(myPosition[i][0], myPosition[i][1]));
		item->setTag(i);
		menu->addChild(item);
	}
	auto item = MenuItemImage::create("UI/stageUnlockBig.png", "UI/stageUnlockSmall.png", CC_CALLBACK_1(ChoseLevel::menuEnterGameCallback, this));
	item->setPosition(Vec2(myPosition[now][0], myPosition[now][1]));
	menu->addChild(item);
	item->setTag(now);

	for (int i = now + 1; i < num; i++) {
		auto item = MenuItemImage::create("UI/stageUnattachBig.png", "UI/stageUnattachSmall.png", CC_CALLBACK_1(ChoseLevel::menuEnterGameCallback, this));
		item->setPosition(Vec2(myPosition[i][0], myPosition[i][1]));
		item->setTag(i);
		menu->addChild(item);
	}
	
	menu->setPosition(Vec2(0, 0));
	this->addChild(menu);
}

void ChoseLevel::menuCloseCallback(cocos2d::Ref* pSender) {
	Director::getInstance()->popScene();
}

void ChoseLevel::menuSingleCallback(cocos2d::Ref* pSender) {
	_PlayerModel = 1;
	this->removeChildByTag(1);
	init2();
}

void ChoseLevel::menuDoubleCallback(cocos2d::Ref* pSender) {
	_PlayerModel = 2;
	this->removeChildByTag(1);
	init2();
}

void ChoseLevel::menuEnterGameCallback(cocos2d::Ref* pSender) {
	MenuItem* nmitem = (MenuItem*)pSender;
	if (nmitem->getTag() <= now) {
		Game::levelNum = nmitem->getTag();
		auto sc = Game::createScene();
		auto transition = TransitionFade::create(1, sc);
		Director::getInstance()->pushScene(transition);
	}
}

