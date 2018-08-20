#include "OurTank.h"
#include "Bullet.h"
#include <SimpleAudioEngine.h>

using namespace CocosDenshion;

OurTank::OurTank(int initialHP)
{
	this->nHP = initialHP;
	this->weaponType = WEAPON_0;
}

OurTank * OurTank::createWithImage(int initialHP)
{
	OurTank * player = new OurTank(initialHP);
	if (player && player->initWithFile("map/ninja.png"))
	{
		player->autorelease();
	}
	return player;
}

void OurTank::openFire()
{
	switch (weaponType)
	{
	case WEAPON_0:
		SimpleAudioEngine::getInstance()->playEffect("sound/sfx_fire1.mp3");
		Bullet * bullet = Bullet::createWithImage();
		this->getParent()->addChild(bullet);
		bullet->shootBulletFromTank(this);
		break;
	}
}