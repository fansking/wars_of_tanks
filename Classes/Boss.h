#pragma once
#include "cocos2d.h"
#include "Bullet.h"

using namespace cocos2d;

class Boss : public Sprite
{
public:
	CC_SYNTHESIZE(int, HP, HP);

	float cd_0;
	float cd_1;

	Boss(int);
	static Boss * create();
};