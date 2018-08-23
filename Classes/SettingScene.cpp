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

	Sprite *bg = Sprite::create("menu/bg_new.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);

	Sprite *backGround2 = Sprite::create("UI/numBg.png");
	backGround2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(backGround2);

	auto label1 = Label::createWithSystemFont("音乐", "Aeial", 50);
	label1->setPosition(Vec2(origin.x + visibleSize.width / 2 , origin.y + visibleSize.height / 2 + 120));
	this->addChild(label1, 1);
	auto label2 = Label::createWithSystemFont("音效", "Aeial", 50);
	label2->setPosition(Vec2(origin.x + visibleSize.width / 2 , origin.y + visibleSize.height / 2 +10));
	this->addChild(label2, 1);


	auto musicSlider = ControlSlider::create("UI/sound1.tga", "UI/sound2.tga", "UI/sound3.tga");
	musicSlider->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2+70));
	musicSlider->setMinimumValue(0);
	musicSlider->setMaximumValue(100);
	musicSlider->setValue(SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()*100);
	musicSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(Setting::musicChanged), Control::EventType::VALUE_CHANGED);
	this->addChild(musicSlider,1);

	auto soundSlider = ControlSlider::create("UI/sound1.tga", "UI/sound2.tga", "UI/sound3.tga");
	soundSlider->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2-50));
	soundSlider->setMinimumValue(0);
	soundSlider->setMaximumValue(100);
	soundSlider->setValue(50);
	soundSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(Setting::soundChanged), Control::EventType::VALUE_CHANGED);
	this->addChild(soundSlider, 1);


	auto okMenuItem = MenuItemImage::create(
		"UI/closebt.png", "UI/closebt_h.png", CC_CALLBACK_1(Setting::menuOkCallback, this));
	okMenuItem->setPosition(origin.x + visibleSize.width / 2, origin.y +visibleSize.height/2 - 130);
	okMenuItem->setScale(0.8);
	Menu *mn = Menu::create(okMenuItem, NULL);
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
void Setting::musicChanged(Ref *sender, Control::EventType)
{
	ControlSlider *slider = (ControlSlider*)sender;
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(slider->getValue()/100);
	log("%d",(int)slider->getValue());
}

void Setting::soundChanged(Ref *sender, Control::EventType) 
{
	ControlSlider *slider = (ControlSlider*)sender;
}
