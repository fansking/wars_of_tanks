#include "OurTank.h"
#include "GameScene.h"
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
		PHYSICSBODY_MATERIAL_DEFAULT, 3.0f, Vec2(30, 30));
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

void OurTank::addenemy() {
	TMXObjectGroup *group = Game::_tileMap->getObjectGroup("objects");
	ValueMap spawnPoint_0 = group->getObject("playerA");
	ValueMap enemy_spawn[10] = {};
	Enemy * enemy[10] = {NULL};
	static int x = 0;
	while (spawnPoint_0 != ValueMap()) {
		
		char enemyname[10] = "enemy";
		char str[10];
		sprintf(str, "%d", x);
		strcat(enemyname, str);
		++x;
		log("%s", enemyname);
		spawnPoint_0 = group->getObject(enemyname);
		if (spawnPoint_0 == ValueMap()) { break; }
		/*int  x0 = spawnPoint_0["x"].asInt();
		int  y0 = spawnPoint_0["y"].asInt();
		auto _enemy_1 = Enemy::createWithEnemyTypes(EnemyTypeEnemy1);
		_enemy_1->setPosition(Vec2(x0, y0));
		this->getParent()->addChild(_enemy_1, 2, 200);*/
	}
	for (int i = 0; i <= x; i++) {
		char enemyname[10] = "enemy";
		char str[10];
		sprintf(str, "%d", i);
		strcat(enemyname, str);
		log("%s", enemyname);
		spawnPoint_0 = group->getObject(enemyname);
		if (spawnPoint_0 == ValueMap()) { break; }
		int  x0 = spawnPoint_0["x"].asInt();
		int  y0 = spawnPoint_0["y"].asInt();
		enemy[i] = Enemy::createWithEnemyTypes(EnemyTypeEnemy1);
		enemy[i]->setPosition(Vec2(x0, y0));
		this->getParent()->addChild(enemy[i], 2, 200);
	}
}