#pragma once
#include "Bullet.h";

class BulletFire : public Bullet {
public:
	virtual void update(float dt);
	static BulletFire * createWithImage();

};


BulletFire * BulletFire::createWithImage()
{
	BulletFire * bullet = new BulletFire();
	if (bullet && bullet->initWithFile("bullet13.png"))
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

void BulletFire::update(float dt)
{
	//coordinate transformation
	Vec2 pos = this->getPosition();
	int X = pos.x / 32;
	int Y = ((20 * 32) - pos.y) / 32;
	Sprite *mytile = walklay->getTileAt(Vec2(X, Y));
	Sprite *mycoll = coll->getTileAt(Vec2(X, Y));
	if (mytile != nullptr && mytile->isVisible() && this->isVisible() && mycoll) {
		mytile->setVisible(false);
		mycoll->removeFromParent();
		return;
	}
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
