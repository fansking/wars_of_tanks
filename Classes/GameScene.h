#pragma once
#include<cocos2d.h>
#include <SimpleAudioEngine.h>
#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

class Game :public cocos2d::Layer
{
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::Sprite *_player;
	cocos2d::TMXLayer *_collidable;
public:
	static cocos2d::Scene * createScene();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event * event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event * event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event * event);
	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	virtual bool init();
	
	CREATE_FUNC(Game);

};
#endif