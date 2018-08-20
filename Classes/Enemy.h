#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#define Enemy_1 "map/enmy_1.png"
#define Enemy_2 "map/enmy_2.png"
typedef enum {
	EnemyTypeEnemy1,
	EnemyTypeEnemy2
}EnemyTypes;
class Enemy :public cocos2d::Sprite {
	CC_SYNTHESIZE(EnemyTypes, enemyType, EnemyType);//EnemyType
	CC_SYNTHESIZE(int, initialHitPoints, InitialHitPoints);//Initial HP
	CC_SYNTHESIZE(int, hitPoints, HitPoints);//HP
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);//speed
public:
	Enemy(EnemyTypes enemyType);

	void spawn();//make enemy
	void shoot();
	virtual void update(float dt);
	static Enemy * createWithEnemyTypes(EnemyTypes enemyType);

};