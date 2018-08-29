/****************************************************************************
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "HelloWorldScene.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
#define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif
USING_NS_CC;

Scene* Loading::createScene()
{
	return Loading::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Loading::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"UI/closebt.png",
		"UI/closebt_h.png",
		CC_CALLBACK_1(Loading::menuCloseCallback, this));
	closeItem->setScale(0.5);
	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - 30;
		float y = origin.y + visibleSize.height - 30;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	Sprite *bg = Sprite::create("menu/bg_new.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);
	/*		----	Loading	----		*/
	auto load = Sprite::create("empty.png");
	load->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(load);

	auto frames = new std::vector<SpriteFrame*>();
	for (int j = 0; j < 4; j++)
	{
		frames->push_back(SpriteFrame::create("Loading_001.png", Rect(0, 0, 437, 97)));
		frames->push_back(SpriteFrame::create("Loading_002.png", Rect(0, 0, 437, 97)));
		frames->push_back(SpriteFrame::create("Loading_003.png", Rect(0, 0, 437, 97)));
		frames->push_back(SpriteFrame::create("Loading_004.png", Rect(0, 0, 437, 97)));
	}
	auto animation = Animation::create();
	for (int i = 0; i < 16; i++)
	{
		animation->addSpriteFrame(frames->at(i));
	}
	animation->setLoops(1);
	animation->setDelayPerUnit(0.01);
	Animate *loade = Animate::create(animation);

	//info的内容将会在触发事件时作为参数传入
	ValueMap info;
	info["FrameId"] = Value("Frame4");
	//获取animation指定帧，并设置UserInfo,只有设置了UserInfo才会触发帧事件
	animation->getFrames().at(15)->setUserInfo(info);
	load->runAction(Animate::create(animation));
	//预加载
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/background.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/empty.mp3");


	//监听ActionFrameDisplayedNotification事件
	auto _frameDisplayedListener = EventListenerCustom::create(AnimationFrameDisplayedNotification, [](EventCustom * event)
	{//指定帧出发的事件
	 //事件传入DisplayedEventInfo指针，包含播放动画的对象及动画的自定义信息
		auto userdata = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());
		//log("target %p with data %s", userdata->target, Value(userdata->userInfo).getDescription().c_str());
		auto sc = HelloWorld::createScene();
		auto transition = TransitionCrossFade::create(1, sc);
		Director::getInstance()->pushScene(transition);
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_frameDisplayedListener, -1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	
	return true;
}

void Loading::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}