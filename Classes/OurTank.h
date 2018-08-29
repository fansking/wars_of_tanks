#pragma once

#include "cocos2d.h"

using namespace cocos2d;

typedef enum
{
	WEAPON_0 = 0,
	WEAPON_1,
	WEAPON_2,
	WEAPON_3,
	WEAPON_4
}WeaponType;

typedef enum
{
	NOSKILL = 0,
	SKILL_0,
	SKILL_1,
	SKILL_2
}SkillType;

class OurTank : public Sprite
{
	CC_SYNTHESIZE(int, nHP, HP);
	CC_SYNTHESIZE(int, nDirection, Direction);
	CC_SYNTHESIZE(WeaponType, weaponType, WeaponType);
	CC_SYNTHESIZE(Vec2, vel, Vel);
	CC_SYNTHESIZE(SkillType, skillType, SkillType);

public:
	OurTank(int);
	static OurTank * createWithImage(int);
	void openFire(bool);
	void addenemy();
	void addpickup();
	void addpickupV();
	void useSkill();
	float mydt;

	int nVel;

};