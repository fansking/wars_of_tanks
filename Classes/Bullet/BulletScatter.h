#pragma once
#include"Bullet.h"

class BulletScatter :public Bullet {
	int rotation;
	int flag;
	int v_x;
	int v_y;
public:
	virtual void update(float dt);
	static BulletScatter * createWithImage(int flag);
	void shootBulletFromTank(OurTank * tank);

};

BulletScatter * BulletScatter::createWithImage(int flag)
{
	
	BulletScatter * bullet = new BulletScatter();
	bullet->flag = flag;
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


void BulletScatter::shootBulletFromTank(OurTank * tank)
{
	switch (tank->getDirection())
	{
	case 146:
		switch (flag) {
		case 1:
			rotation = -30;
			v_x = -288;
			v_y = 500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 2:
			rotation = 0;
			v_x = 0;
			v_y = 500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 3:
			rotation = 30;
			v_x = 288;
			v_y = 500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		}
		break;
	case 142:
		switch (flag) {
		case 1:
			rotation = 150;
			v_x = -288;
			v_y = -500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, -tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 2:
			rotation = 180;
			v_x = 0;
			v_y = -500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, -tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 3:
			rotation = 210;
			v_x = 288;
			v_y =-500;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(0, -tank->getContentSize().height / 2));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		}
		
		break;
	case 124:
		switch (flag) {
		case 1:
			rotation = 240;
			v_x = -500;
			v_y = 288;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(-tank->getContentSize().width / 2, 0));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 2:
			rotation = 270;
			v_x = -500;
			v_y = 0;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(-tank->getContentSize().width / 2, 0));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 3:
			rotation = 300;
			v_x = -500;
			v_y = -288;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(-tank->getContentSize().width / 2, 0));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		}
		break;
	case 127:
		switch (flag) {
		case 1:
			rotation = 60;
			v_x = 500;
			v_y = 288;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(tank->getContentSize().width / 2, 0));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 2:
			rotation = 90;
			v_x = 500;
			v_y = 0;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(tank->getContentSize().width / 2, 0));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		case 3:
			rotation = 120;
			v_x = 500;
			v_y = -288;
			this->setRotation(rotation);
			this->setPosition(tank->getPosition() + Vec2(tank->getContentSize().width / 2, 0));
			this->setVelocity(Vec2(v_x, v_y));
			break;
		}
		
		break;
	}
	this->setVisible(true);
	this->scheduleUpdate();
	this->scheduleUpdate();
}
void BulletScatter::update(float dt)
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
		this->setVisible(false);
		this->removeFromParent();
		return;
	}
	Sprite *mytile1 = _breakable1->getTileAt(Vec2(X, Y));
	if (mytile1 && mytile1->isVisible() && this->isVisible() && mycoll) {
		this->setVisible(false);
		this->removeFromParent();
		return;
	}
	Size screenSize = Size((Vec2(Game::_tileMap->getTileSize().width * Game::_tileMap->getMapSize().width,
		Game::_tileMap->getTileSize().height * Game::_tileMap->getMapSize().height)));
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
