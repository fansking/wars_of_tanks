#include "OurTank.h"
#include "Bullet.h"
#include <SimpleAudioEngine.h>

using namespace CocosDenshion;

OurTank::OurTank(int initialHP)
{
	this->nHP = initialHP;
	this->weaponType = WEAPON_0;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto body = PhysicsBody::createEdgeBox(Size(60, 60),
		PHYSICSBODY_MATERIAL_DEFAULT, 3.0f, Vec2(16, 16));
	body->setCategoryBitmask(0x01);
	body->setContactTestBitmask(0x01);
	this->setPhysicsBody(body);
}

OurTank * OurTank::createWithImage(int initialHP)
{
	OurTank * player = new OurTank(initialHP);
	if (player && player->initWithFile("map/ninja.png"))
	{
		player->autorelease();
	}
	//player->setTag(1);
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