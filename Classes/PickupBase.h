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
#define HELPPATH "myHelp.png"

typedef enum
{
	Gold,
	Bulletscatter,
	Bluebullet,
	Redbullet,
	Skill_Shield,
	ProBullet,

	Speedup,
	Addblood,


	Help0 = 20,
	Help1,
	Help2,
	Help3,
	Help4,
	Help5,
	Help6,
	Help7

}PickupTypes;

class PickupBase : public Sprite
{
	CC_SYNTHESIZE(PickupTypes, pickupType, PickupType);
public:
	static PickupBase * createWithImage(const char *);
	static PickupBase * createWithType(PickupTypes );
	virtual void isContact(OurTank *);
	void showHelp(int helpNum);
	void closeHelpLayerCallback(Ref* pSender);
};