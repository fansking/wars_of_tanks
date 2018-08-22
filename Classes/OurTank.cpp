#include "OurTank.h"
#include "Bullet.h"
#include "bullet/BulletFire.h"
#include "bullet/BulletPlus.h"
#include "bullet/BulletScatter.h"
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
	body->setContactTestBitmask(0x02);
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
	SimpleAudioEngine::getInstance()->playEffect("sound/sfx_fire1.mp3");
	if (weaponType == WEAPON_0) {
		Bullet * bullet = Bullet::createWithImage();
		this->getParent()->addChild(bullet);
		bullet->shootBulletFromTank(this);
	}
	else if(weaponType == WEAPON_1){
		BulletPlus * bullet = BulletPlus::createWithImage();
		this->getParent()->addChild(bullet);
		bullet->shootBulletFromTank(this);
		
	}
	else if (weaponType == WEAPON_2) {
		BulletFire * bullet = BulletFire::createWithImage();
		this->getParent()->addChild(bullet);
		bullet->shootBulletFromTank(this);
	}else if(weaponType == WEAPON_3) {
		BulletScatter * bullet1 = BulletScatter::createWithImage(1);
		BulletScatter * bullet2 = BulletScatter::createWithImage(2);
		BulletScatter * bullet3 = BulletScatter::createWithImage(3);
		this->getParent()->addChild(bullet1);
		bullet1->shootBulletFromTank(this);
		this->getParent()->addChild(bullet2);
		bullet2->shootBulletFromTank(this);
		this->getParent()->addChild(bullet3);
		bullet3->shootBulletFromTank(this);
	}
	/*switch (weaponType)
	{
	case WEAPON_0:
		
		Bullet * bullet = Bullet::createWithImage();
		this->getParent()->addChild(bullet);
		bullet->shootBulletFromTank(this);
		break;
	case WEAPON_1:
		BulletPlus * bullet1 = BulletPlus::createWithImage();
		this->getParent()->addChild(bullet1);
		bullet1->shootBulletFromTank(this);
		break;

	}*/
}