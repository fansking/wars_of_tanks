#pragma once
#include "cocos2d.h"
#include "OurTank.h"

using namespace cocos2d;

class Bullet : public Sprite
{
	CC_SYNTHESIZE(Vec2, velocity, Velocity);
public:
	static Bullet * createWithImage();
	void shootBulletFromTank(OurTank * tank);
	virtual void update(float dt);
};