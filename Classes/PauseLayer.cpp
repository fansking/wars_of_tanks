#include "PauseLayer.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include "ChoseLevel.h"

bool PauseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Sprite * bgPause = Sprite::create("UI/numBg.png");
	bgPause->setAnchorPoint(Vec2(0.5, 0.5));
	
	this->addChild(bgPause);

	auto itemRestart = MenuItemImage::create("UI/restart.png", "UI/restartPressed.png", 
		CC_CALLBACK_1(PauseLayer::menuItemRestartCallback, this));
	auto itemChooseStage = MenuItemImage::create("UI/chooseStage.png", "UI/chooseStagePressed.png", 
		CC_CALLBACK_1(PauseLayer::menuItemChooseStageCallback, this));
	auto itemHomePage = MenuItemImage::create("UI/homePage.png", "UI/homePagePressed.png", 
		CC_CALLBACK_1(PauseLayer::menuItemHomePageCallback, this));
	auto menuPause = Menu::create(itemRestart, itemChooseStage, itemHomePage, NULL);
	menuPause->alignItemsVertically();
	menuPause->setPosition(this->getPosition());

	this->addChild(menuPause);
}

void PauseLayer::menuItemRestartCallback(Ref * pSender)
{
	log("Restart");
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(Game::createScene());
}
void PauseLayer::menuItemChooseStageCallback(Ref * pSender)
{
	log("ChooseStage");
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(ChoseLevel::createScene());
}
void PauseLayer::menuItemHomePageCallback(Ref * pSender)
{
	log("HomePage");
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}