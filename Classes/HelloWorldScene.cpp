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
#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "GameScene.h"
#include "AboutScene.h"
#include "ChoseLevel.h"
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

int Game::levelNum = 0;
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void HelloWorld::menuItem2Callback(Ref *pSender)
{
	//MenuItem *item = (MenuItem*)pSender;
	//log("Touch Help Menu Item %p", item);
	auto sc = About::createScene();
	auto transition = TransitionCrossFade::create(1, sc);
	Director::getInstance()->pushScene(transition);
}
void HelloWorld::menuItemSettingCallback(Ref *pSender)
{
	auto sc = Setting::createScene();
	Director::getInstance()->pushScene(sc);

}
void HelloWorld::menuItemStartCallback(cocos2d::Ref *pSender)
{
	//auto sc = Game::createScene();
	//auto transition = TransitionFade::create(1, sc);
	//Director::getInstance()->pushScene(transition);
	auto sc = ChoseLevel::createScene();
	auto transition = TransitionFade::create(1, sc);
	Director::getInstance()->pushScene(transition);
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/background.mp3");
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);

	Director::getInstance()->setDisplayStats(false);


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "UI/closebt.png",
                                           "UI/closebt_h.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setScale(0.5);
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width  - 30;
        float y = origin.y + visibleSize.height  - 30;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	Sprite *bg = Sprite::create("menu/bg_new.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
	auto item1 = MenuItemImage::create("UI/gameStart.png", "UI/gameStart1.png", CC_CALLBACK_1(HelloWorld::menuItemStartCallback, this));
	item1->setScale(0.7);
	item1->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	auto item2 = MenuItemImage::create("UI/about.png", "UI/about1.png", CC_CALLBACK_1(HelloWorld::menuItem2Callback, this));
	item2->setScale(0.5);
	item2->setPosition(Vec2( 80, visibleSize.height - 30));
	auto item3 = MenuItemImage::create("UI/setting.png", "UI/setting1.png", CC_CALLBACK_1(HelloWorld::menuItemSettingCallback, this));
	item3->setScale(0.5);
	item3->setPosition(Vec2(30, visibleSize.height - 30));
	auto item4 = MenuItemImage::create("UI/collections.png", "UI/collections1.png", CC_CALLBACK_1(HelloWorld::menuTtemCollections, this));
	item4->setPosition(Vec2(120, 120));

	Menu *mn = Menu::create(item1, item2,item3,item4, NULL);
	mn->setPosition(Vec2(0, 0 ));
	//mn->setAnchorPoint(Vec2(0, 0));
	this->addChild(mn);
	Director::getInstance()->setDisplayStats(false);
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
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

void HelloWorld::menuTtemCollections(cocos2d::Ref *pSender){

}
