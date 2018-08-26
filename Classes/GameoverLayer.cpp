#include "GameoverLayer.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include "ChoseLevel.h"

bool GameoverLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Sprite * bgPause = Sprite::create("UI/gameover/result_bg1.png");
	bgPause->setAnchorPoint(Vec2(0.5, 0.5));
	
	this->addChild(bgPause);

	auto itemRestart = MenuItemImage::create("UI/gameover/button_restart_0.png", 
		"UI/gameover/button_restart_1.png", 
		CC_CALLBACK_1(GameoverLayer::menuItemRestartCallback, this));
	auto itemChooseStage = MenuItemImage::create("UI/gameover/button_level_0.png", 
		"UI/gameover/button_level_1.png", 
		CC_CALLBACK_1(GameoverLayer::menuItemChooseStageCallback, this));
	auto itemHomePage = MenuItemImage::create("UI/gameover/button_menu_0.png", 
		"UI/gameover/button_menu_1.png", 
		CC_CALLBACK_1(GameoverLayer::menuItemHomePageCallback, this));

	auto menuPause = Menu::create(itemRestart, itemChooseStage, itemHomePage, NULL);
	menuPause->alignItemsHorizontally();
	menuPause->setPosition(Vec2(this->getPosition().x, 
		this->getPosition().y - bgPause->getContentSize().height / 4));

	this->addChild(menuPause);
}

void GameoverLayer::menuItemRestartCallback(Ref * pSender)
{
	Director::getInstance()->resume();
	log("Restart");
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(Game::createScene());
}
void GameoverLayer::menuItemChooseStageCallback(Ref * pSender)
{
	Director::getInstance()->resume();
	log("ChooseStage");
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(ChoseLevel::createScene());
}
void GameoverLayer::menuItemHomePageCallback(Ref * pSender)
{
	Director::getInstance()->resume();
	log("HomePage");
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
