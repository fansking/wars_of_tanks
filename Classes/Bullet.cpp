#include "Bullet.h"

Bullet * Bullet::createWithImage()
{
	Bullet * bullet = new Bullet();
	if (bullet && bullet->initWithFile("bullet7.png"))
	{
		bullet->autorelease();
		bullet->setVisible(false);

		//auto body = PhysicsBody::createBox(bullet->getContentSize());

		/* There are some temp value */
		//body->setCategoryBitmask(0);
		//body->setCollisionBitmask(0);
		//body->setContactTestBitmask(0);

		//bullet->setPhysicsBody(body);
		auto body = PhysicsBody::createEdgeBox(Size(16, 16), 
			PHYSICSBODY_MATERIAL_DEFAULT, 2.0f, Vec2(0, 0));
		body->setCategoryBitmask(0x02);
		body->setContactTestBitmask(0x02);
		bullet->setPhysicsBody(body);
		bullet->setTag(2);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void Bullet::shootBulletFromTank(OurTank * tank)
{
	switch (tank->getDirection())
	{
	case 146:
		this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
		this->setVelocity(Vec2(0,500));
		break;
	case 142:
		this->setPosition(tank->getPosition() + Vec2(0, -tank->getContentSize().height / 2));
		this->setVelocity(Vec2(0,-500));
		break;
	case 124:
		this->setPosition(tank->getPosition() - Vec2(tank->getContentSize().width / 2, 0));
		this->setVelocity(Vec2(-500,0));
		break;
	case 127:
		this->setPosition(tank->getPosition() + Vec2(tank->getContentSize().width / 2, 0));
		this->setVelocity(Vec2(500,0));
		break;
	}
	this->setVisible(true);
	this->scheduleUpdate();
	this->scheduleUpdate();
}

void Bullet::update(float dt)
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	this->setPosition(this->getPosition() + velocity * dt);
	int y = this->getPosition().y;
	int x = this->getPosition().x;
	if (y >= screenSize.height || y <= 0 || x >= screenSize.width || x <= 0)
	{
		this->setVisible(false);
		this->unscheduleUpdate();
		this->removeFromParent();
	}
}