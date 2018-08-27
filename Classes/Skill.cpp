#include "Bullet.h"
#include "OurTank.h"
#include"Skill.h"
#include "GameScene.h"

Shield * Shield::createshield() {
	Shield * shield = new Shield();
	if (shield &&shield->initWithFile("bullet5.png"))
	{
		shield->autorelease();
		shield->setVisible(false);

		auto body = PhysicsBody::createBox(shield->getContentSize()*1.1);

		/* There are some temp value */
	//	body->setCategoryBitmask(0);

	//	body->setContactTestBitmask(0);

		shield->setPhysicsBody(body);
			/*PHYSICSBODY_MATERIAL_DEFAULT, 2.0f, Vec2(0, 0));*/
		body->setCategoryBitmask(0x01);
		body->setContactTestBitmask(0x02);
		body->setCollisionBitmask(0x0);
		body->setGravityEnable(false);
		shield->setPhysicsBody(body);
		shield->setTag(200);
		return shield;
	}
	CC_SAFE_DELETE(shield);
	return nullptr;
}
void Shield::ShowWithTank(OurTank *tank) {
	this->mydt = 5;
	switch (tank->getDirection())
	{
	case 146:
		this->setRotation(0);
		this->setPosition(tank->getPosition() );

		break;
	case 142:
		this->setRotation(180);
		this->setPosition(tank->getPosition() );

		break;
	case 124:
		this->setRotation(270);
		this->setPosition(tank->getPosition() );

		break;
	case 127:
		this->setRotation(90);
		this->setPosition(tank->getPosition());

		break;
	}
	this->setVisible(true);
	tank->getParent()->addChild(this);
	this->setOpacity(200);
	this->scheduleUpdate();
}
void Shield::update(float dt) {
	mydt -= dt;
	switch (Game::_player ->getDirection())
	{
	case 146:
		this->setRotation(0);
		this->setPosition(Game::_player->getPosition());

		break;
	case 142:
		this->setRotation(180);
		this->setPosition(Game::_player->getPosition());

		break;
	case 124:
		this->setRotation(270);
		this->setPosition(Game::_player->getPosition());

		break;
	case 127:
		this->setRotation(90);
		this->setPosition(Game::_player->getPosition());

		break;
	}
	if (mydt < 0) {
		this->removeFromParent();
	}
}