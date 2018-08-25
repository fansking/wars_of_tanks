#pragma once

#include "cocos2d.h"

using namespace cocos2d;

typedef enum
{
	WEAPON_0 = 0,
	WEAPON_1,
	WEAPON_2,
	WEAPON_3
}WeaponType;

class OurTank : public Sprite
{
	CC_SYNTHESIZE(int, nHP, HP);
	CC_SYNTHESIZE(int, nDirection, Direction);
	CC_SYNTHESIZE(WeaponType, weaponType, WeaponType);
	CC_SYNTHESIZE(Vec2, vel, Vel);

public:
	OurTank(int);
	static OurTank * createWithImage(int);
	void openFire();
	void addenemy();
	void addpickup();
	float mydt;

};