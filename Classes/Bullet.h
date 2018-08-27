#pragma once
#include "cocos2d.h"
#include "OurTank.h"
#define bullet_1 "bullet7.png"
#define bullet_2 "bullet17.png"

using namespace cocos2d;

class Bullet : public Sprite
{
	
	CC_SYNTHESIZE(Vec2, vel, Velocity);
	CC_SYNTHESIZE(int, akt, AKT);

public:
	static int score;
	static TMXLayer   *_breakable0;
	static TMXLayer   *coll;
	static TMXLayer * _breakable1;
	static Bullet * createWithImage(bool );
	void shootBulletFromTank(OurTank * tank);
	virtual void update(float dt);

	bool isFriendly;
};








