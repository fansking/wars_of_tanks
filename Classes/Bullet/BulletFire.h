#pragma once
#include "Bullet.h";
#include "GameScene.h"
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
		body->setCategoryBitmask(0x04);
		body->setContactTestBitmask(0x08);
		body->setCollisionBitmask(0x00);
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
	int X = pos.x / Game::_tileMap->getTileSize().width;
	int Y = ((Game::_tileMap->getMapSize().height * Game::_tileMap->getTileSize().height) - pos.y)
		/ Game::_tileMap->getTileSize().width;
	Sprite *mytile0 = _breakable0->getTileAt(Vec2(X, Y));
	Sprite *mycoll = coll->getTileAt(Vec2(X, Y));
	if (mytile0 != nullptr && mytile0->isVisible() && this->isVisible() && mycoll) {
		mytile0->setVisible(false);
		mycoll->removeFromParent();
		return;
	}
	Sprite *mytile1 = _breakable1->getTileAt(Vec2(X, Y));
	if (mytile1 && mytile1->isVisible() && this->isVisible() && mycoll) {
		mytile1->setVisible(false);
		mycoll->removeFromParent();
		this->setVisible(false);
		this->removeFromParent();
		return;
	}
	Size screenSize = Size((Vec2(Game::_tileMap->getTileSize().width * Game::_tileMap->getMapSize().width,
		Game::_tileMap->getTileSize().height * Game::_tileMap->getMapSize().height)));
	this->setPosition(this->getPosition() + vel * dt);
	int y = this->getPosition().y;
	int x = this->getPosition().x;
	if (y >= Game::_tileMap->getTileSize().height * Game::_tileMap->getMapSize().height || y <= 0 ||
		x >= Game::_tileMap->getTileSize().width * Game::_tileMap->getMapSize().width || x <= 0)
	{
		this->setVisible(false);
		this->unscheduleUpdate();
		this->removeFromParent();
	}
}
