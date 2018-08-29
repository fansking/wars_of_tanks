#include "Bullet.h"
#include "GameScene.h"
#include <vector>
int Bullet::score = 0;
TMXLayer *Bullet::_breakable0 = nullptr;
TMXLayer *Bullet::coll = nullptr;
TMXLayer *Bullet::_breakable1 = nullptr;
Bullet * Bullet::createWithImage(bool isFriendly)
{
	Bullet * bullet = new Bullet();
	bullet->isFriendly = isFriendly;
	if (bullet && bullet->initWithFile("bullet7.png"))
	{
		bullet->autorelease();
		bullet->setVisible(false);

		auto body = PhysicsBody::createEdgeBox(Size(16, 16), 
			PHYSICSBODY_MATERIAL_DEFAULT, 2.0f, Vec2(0, 0));
		if (bullet->isFriendly)
		{
			body->setCategoryBitmask(0x04);
			body->setContactTestBitmask(0x08);
		}
		else
		{
			body->setCategoryBitmask(0x02);
			body->setContactTestBitmask(0x01);
			bullet->setColor(Color3B::GREEN);
		}
		body->setCollisionBitmask(0x00);
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
	case 28:
		this->setRotation(0);
		this->setPosition(tank->getPosition() + Vec2(0, tank->getContentSize().height / 2));
		this->setVel(Vec2(0,500));
		break;
	case 142:
	case 29:
		this->setRotation(180);
		this->setPosition(tank->getPosition() + Vec2(0, -tank->getContentSize().height / 2));
		this->setVel(Vec2(0,-500));
		break;
	case 124:
	case 26:
		this->setRotation(270);
		this->setPosition(tank->getPosition() - Vec2(tank->getContentSize().width / 2, 0));
		this->setVel(Vec2(-500,0));
		break;
	case 127:
	case 27:
		this->setRotation(90);
		this->setPosition(tank->getPosition() + Vec2(tank->getContentSize().width / 2, 0));
		this->setVel(Vec2(500,0));
		break;
	}
	this->setVisible(true);
	this->scheduleUpdate();
}

void Bullet::update(float dt)
{
	//coordinate transformation
	Vec2 pos = this->getPosition();
	int X = pos.x / Game::_tileMap->getTileSize().width;
	int Y = ((Game::_tileMap->getMapSize().height * Game::_tileMap->getTileSize().height) - pos.y)
		/ Game::_tileMap->getTileSize().width;
	Sprite *mytile0 = _breakable0->getTileAt(Vec2(X, Y));
	
	Sprite *mycoll = coll->getTileAt(Vec2(X, Y));
	 if (mytile0 != nullptr && mytile0->isVisible()&& this->isVisible() && mycoll) {
		 if (this->isFriendly)
		 {
			 mytile0->setVisible(false);
			//log("%f,%f,>>>>>>>>", mytile0->getPosition().x, mytile0->getPosition().y);
			 
			 for (int i = 0; i < Game::nPickup; i++) {
				 //log("%f,%f,>>>>>>>>>", Game::pickup[i]->getPosition().x, Game::pickup[i]->getPosition().y);
				 if (Game::pickup[i]) {

					 if (abs(Game::pickup[i]->getPosition().x - mytile0->getPosition().x) == 30 && abs(Game::pickup[i]->getPosition().y - mytile0->getPosition().y) == 30) {
						 Game::pickup[i]->setVisible(true);
					 }
				 }
			 }
		 
			 mycoll->removeFromParent();
	}
		 
		 score++;
		 //log("%d", score);
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
	this->setPosition(this->getPosition() + vel * dt);
	int y = this->getPosition().y;
	int x = this->getPosition().x;
	if (y >= Game::_tileMap->getTileSize().height * Game::_tileMap->getMapSize().height|| y <= 0 || 
		x >= Game::_tileMap->getTileSize().width * Game::_tileMap->getMapSize().width || x <= 0)
	{
		this->setVisible(false);
		this->unscheduleUpdate();
		this->removeFromParent();
	}
}





