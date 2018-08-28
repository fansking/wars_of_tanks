#pragma once
#include<cocos2d.h>
#include <SimpleAudioEngine.h>
#include "OurTank.h"
#include"Enemy.h"
#include "Bullet.h"
#include "MyUtility.h"
#include "PickupBase.h"
#include "AboutScene.h"
#include "PauseLayer.h"
#include "HelloWorldScene.h"
#include "EnemyAI.h"
#include "GameoverLayer.h"
#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

using namespace cocos2d;

class Game :public Layer
{
	
	
	TMXLayer *_collidable;
	/*Enemy *_enemy_1;
	Enemy *_enemy_2;*/
	
	static bool bVictory;
	
public:
	static Sprite * portal_1;
	static Sprite * portal_2;
	static OurTank *_player;
	static OurTank *_player2;
	static Enemy * enemy[10] ;
	static int nPickup;
	static EnemyAI * enemyAIs[10];
	static TMXTiledMap *_tileMap;
	static int mapSizeHeight;
	static int mapSizeWidth;
	static int tileSize;
	static int levelNum ;

	static Size _mapSize;
	static Size _tileSize;

	static int nEnemy;
	static Scene * createScene();
	void setPlayerPosition(Vec2 position);
	Vec2 tileCoordFromPosition(Vec2 position);
	virtual bool init();
	
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event *);
	void keepMoving(float dt);
	void keepMoving2(float dt);
	//static void RestartCallback(Ref * pSender);
	virtual void update(float dt);

	void menuItemCallbackPause(Ref * pSender);

	static Label *lifeTTF ;
	static Label *gradeTTF;
	static void changeLifeTTF(int lifeNum);
	void playBoomAnimation(Vec2 position);
	static Layer * menuLayer;

	static void controllerForPlayer2(EventKeyboard::KeyCode, Event *);
	static void controllerUnschedule(EventKeyboard::KeyCode keyCode, Event * event);

private:
	
	int tileX, tileY, mapX, mapY;
	Vec2 viewPoint;

	void setViewpointCenter(Point position);
	bool isMoveable(Vec2 position);
	CREATE_FUNC(Game);

};
#endif