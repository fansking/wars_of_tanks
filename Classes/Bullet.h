#pragma once
#include "cocos2d.h"
#include "OurTank.h"
#define bullet_1 "bullet7.png"
#define bullet_2 "bullet17.png"

using namespace cocos2d;

class Bullet : public Sprite
{
	
	CC_SYNTHESIZE(Vec2, velocity, Velocity);
	CC_SYNTHESIZE(int, akt, AKT);

public:
	static TMXLayer   *walklay;
	static TMXLayer   *coll;
	static Bullet * createWithImage();
	void shootBulletFromTank(OurTank * tank);
	virtual void update(float dt);
};








