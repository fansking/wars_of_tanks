#pragma once
#include "cocos2d.h"
#include "OurTank.h"

using namespace cocos2d;

#define GOLDPATH "BulletPro.png"
#define BULLETSCATTERPATH "bulletscatter.png"
#define BLUEBULLETPATH "Bluebullet.png"
#define REDBULLETPATH "Redbullet.png"
#define SHIELDPATH "BeatlessTank.png"
#define SPEEDUPPATH "map/Speedup.png"
#define ADDBLOODPATH "map/blood.png"

typedef enum
{
	Gold,
	Bulletscatter,
	Bluebullet,
	Redbullet,
	Skill_Shield,
	ProBullet,
	Speedup,
	Addblood
}PickupTypes;

class PickupBase : public Sprite
{
	CC_SYNTHESIZE(PickupTypes, pickupType, PickupType);
public:
	static PickupBase * createWithImage(const char *);
	static PickupBase * createWithType(PickupTypes );
	virtual void isContact(OurTank *);
};