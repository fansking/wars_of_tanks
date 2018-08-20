#pragma once
#include<cocos2d.h>
#include <SimpleAudioEngine.h>
#include "OurTank.h"

#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

using namespace cocos2d;

class Game :public Layer
{
	TMXTiledMap *_tileMap;
	OurTank *_player;
	TMXLayer *_collidable;

public:
	static Scene * createScene();
	virtual bool onTouchBegan(Touch* touch, Event * event);
	virtual void onTouchMoved(Touch* touch, Event * event);
	virtual void onTouchEnded(Touch* touch, Event * event);
	void setPlayerPosition(Vec2 position);
	Vec2 tileCoordFromPosition(Vec2 position);
	virtual bool init();

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event *);
	void keepMoving(float dt);
	
	CREATE_FUNC(Game);

};
#endif