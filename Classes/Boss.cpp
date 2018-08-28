#include "Boss.h"

Boss::Boss(int initialHP)
{
	setHP(initialHP);
	cd_0 = 0.5;
	cd_1 = 2;

	auto body = PhysicsBody::createCircle(240,
		PHYSICSBODY_MATERIAL_DEFAULT,
		Vec2(250, 10));
	body->setCategoryBitmask(0x08);
	body->setContactTestBitmask(0x04);
	body->setCollisionBitmask(0x00);
	body->getShape(0)->setDensity(0.0f);
	body->getShape(0)->setRestitution(0.0f);
	body->getShape(0)->setFriction(0.0f);
	body->setDynamic(false);
	body->setGravityEnable(false);

	//this->setPhysicsBody(body);
	this->setPhysicsBody(body);
}

Boss * Boss::create()
{
	Boss * boss = new Boss(10);
	if (boss && boss->initWithFile("map/boss/boss.png"))
	{
		log("BOSSSSSSSSSSSSSSSSSSSSSSSSS");
		boss->autorelease();
	}
	boss->setTag(38);


	return boss;
}