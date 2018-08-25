#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"

using namespace cocos2d;

class EnemyAI
{
public:
	EnemyAI();
	~EnemyAI();

	static EnemyAI * createWithEnemy(Enemy *);
	Vec2 tileCoordFromPosition(Vec2 pos);
	virtual void update(float dt);
	static TMXLayer * layer;

private:
	bool isCollidable(Vec2 target);
	Enemy * obj;
	Vec2 vel;
};

