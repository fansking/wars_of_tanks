#include "SettingScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene *Setting::createScene()
{
	auto scene = Scene::create();
	auto layer = Setting::create();
	scene->addChild(layer);
	return scene;
}
bool Setting::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::create("menu/background.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);


	auto label1 = Label::createWithSystemFont("音乐", "Aeial", 60);
	label1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 50, origin.y + visibleSize.height / 2 - 10));
	this->addChild(label1, 1);
	auto label2 = Label::createWithSystemFont("音效", "Aeial", 60);
	label2->setPosition(Vec2(origin.x + visibleSize.width / 2 - 50, origin.y + visibleSize.height / 2 - 100));
	this->addChild(label2, 1);
	auto soundOnMenuItem = MenuItemImage::create("on.png", "on.png");
	auto soundOffMenuItem = MenuItemImage::create("off.png", "off.png");


	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(Setting::menuSoundToggleCallback, this), soundOnMenuItem, soundOffMenuItem, NULL);
	soundToggleMenuItem->setPosition(origin.x + visibleSize.width / 2+100, origin.y + visibleSize.height / 2-100);
	auto musicOnMenuItem = MenuItemImage::create("on.png", "on.png");
	auto musicOffMenuItem= MenuItemImage::create("off.png", "off.png");
	auto musicToggleItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(Setting::menuMusicToggleCallback, this), musicOnMenuItem, musicOffMenuItem, NULL);
	musicToggleItem->setPosition(origin.x + visibleSize.width / 2+100, origin.y + visibleSize.height/2-10 );

	auto okMenuItem = MenuItemImage::create(
		"ok.png", "ok.png", CC_CALLBACK_1(Setting::menuOkCallback, this));
	okMenuItem->setPosition(origin.x + visibleSize.width / 2, origin.y +100);
	Menu *mn = Menu::create(soundToggleMenuItem, musicToggleItem, okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);
	return true;
}
void Setting::menuOkCallback(Ref *pSender)
{
	Director::getInstance()->popScene();
}
void Setting::menuSoundToggleCallback(Ref *pSender)
{}
void Setting::menuMusicToggleCallback(Ref *pSender)
{}