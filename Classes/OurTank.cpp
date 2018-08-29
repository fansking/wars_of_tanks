#include "OurTank.h"
#include "GameScene.h"
#include "Bullet.h"
#include "bullet/BulletFire.h"
#include "bullet/BulletPlus.h"
#include "bullet/BulletScatter.h"
#include "Bullet/BulletPro.h"
#include <SimpleAudioEngine.h>
#include "Boss.h"

using namespace CocosDenshion;

OurTank::OurTank(int initialHP)
{
	nVel = 200;

	this->nHP = initialHP;
	this->weaponType = WEAPON_0;
	this->setVel(Vec2(0, nVel));
	this->setDirection(146);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto body = PhysicsBody::createBox(Size(Vec2(50, 50)),
		PHYSICSBODY_MATERIAL_DEFAULT, Vec2(25, 25));
	body->setCategoryBitmask(0x07);
	body->setContactTestBitmask(0x0A);
	body->setCollisionBitmask(0xFF);
	body->getShape(0)->setDensity(0.0f);
	body->getShape(0)->setRestitution(0.0f);
	body->getShape(0)->setFriction(0.0f);
	body->setDynamic(false);
	body->setGravityEnable(false);

	//this->setPhysicsBody(body);
	this->setPhysicsBody(body);
	
}

OurTank * OurTank::createWithImage(int initialHP)
{
	OurTank * player = new OurTank(initialHP);
	if (player && player->initWithFile("map/ninja.png"))
	{
		player->autorelease();
	}
	player->mydt = 1;
	player->setTag(1);

	player->setSkillType(SKILL_0);

	return player;
}

void OurTank::openFire(bool isFriendly)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/sfx_fire1.mp3");
	if (weaponType == WEAPON_0) {
		Bullet * bullet = Bullet::createWithImage(isFriendly);
		if (Game::mode == MULTI)
		{
			if (this == Game::_player)
			{
				bullet->getPhysicsBody()->setCategoryBitmask(0x04);
				bullet->getPhysicsBody()->setContactTestBitmask(0x08);
			}
			else
			{
				bullet->getPhysicsBody()->setCategoryBitmask(0x08);
				bullet->getPhysicsBody()->setContactTestBitmask(0x04);
			}
		}
		this->getParent()->addChild(bullet, 5);
		bullet->shootBulletFromTank(this);
	}
	else if(weaponType == WEAPON_1){
		BulletPlus * bullet = BulletPlus::createWithImage(isFriendly);
		this->getParent()->addChild(bullet);
		bullet->shootBulletFromTank(this);
	}
	else if (weaponType == WEAPON_2) {
		BulletFire * bullet = BulletFire::createWithImage(isFriendly);
		this->getParent()->addChild(bullet);
		bullet->shootBulletFromTank(this);
	}else if(weaponType == WEAPON_3) {
		BulletScatter * bullet1 = BulletScatter::createWithImage(1, isFriendly);
		BulletScatter * bullet2 = BulletScatter::createWithImage(2, isFriendly);
		BulletScatter * bullet3 = BulletScatter::createWithImage(3, isFriendly);
		this->getParent()->addChild(bullet1, 2);
		bullet1->shootBulletFromTank(this);
		this->getParent()->addChild(bullet2, 2);
		bullet2->shootBulletFromTank(this);
		this->getParent()->addChild(bullet3, 2);
		bullet3->shootBulletFromTank(this);
	}
	else if (weaponType == WEAPON_4) {
		BulletPro * bullet = BulletPro::createWithImage(isFriendly);
		this->getParent()->addChild(bullet);
		bullet->shootBulletFromTank(this);
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
	static int x = 0;

	TMXObjectGroup *group = Game::_tileMap->getObjectGroup("objects");
	ValueMap spawnPoint_0 = group->getObject("playerA");
	while (spawnPoint_0 != ValueMap()) {
		char enemyname[10] = "enemy";
		char str[10];
		sprintf(str, "%d", x);
		strcat(enemyname, str);
		
		++x;
		//log("%s", enemyname);
		spawnPoint_0 = group->getObject(enemyname);
		if (spawnPoint_0 == ValueMap()) { break; }

		
		/*int  x0 = spawnPoint_0["x"].asInt();
		int  y0 = spawnPoint_0["y"].asInt();
		auto _enemy_1 = Enemy::createWithEnemyTypes(EnemyTypeEnemy1);
		_enemy_1->setPosition(Vec2(x0, y0));
		this->getParent()->addChild(_enemy_1, 2, 200);*/
	}
	for (int i = 0; i < x-1; i++) {
		char enemyname[10] = "enemy";
		char str[10];
		sprintf(str, "%d", i);
		strcat(enemyname, str);
		//log("%s", enemyname);
		spawnPoint_0 = group->getObject(enemyname);
		if (spawnPoint_0 == ValueMap()) { break; }
		int  x0 = spawnPoint_0["x"].asInt();
		int  y0 = spawnPoint_0["y"].asInt();
		Game::enemy[i] = Enemy::createWithEnemyTypes(EnemyTypeEnemy1);
		Game::enemy[i]->setPosition(Vec2(x0, y0));
		this->getParent()->addChild(Game::enemy[i], 3);
		Game::enemyAIs[i] = EnemyAI::createWithEnemy(Game::enemy[i]);
	}
}

void OurTank::addpickup() {
	static int x = 0;
	TMXObjectGroup *group = Game::_tileMap->getObjectGroup("objects");
	ValueMap spawnPoint_0 = group->getObject("playerA");
	
	while (spawnPoint_0 != ValueMap()) {
		char pickupname[10] = "pickup";
		char str[10];
		sprintf(str, "%d",x);
		strcat(pickupname, str);
		++x;
		
		//log("%s", pickupname);
		spawnPoint_0 = group->getObject(pickupname);
		if (spawnPoint_0 == ValueMap()) { break; }
		++Game::nPickup;
		int  x0 = spawnPoint_0["x"].asInt();
		int  y0 = spawnPoint_0["y"].asInt();
		int tooltype = spawnPoint_0["ToolType"].asInt();
		Game::pickup[x-1] = PickupBase::createWithType((PickupTypes)tooltype);
		Game::pickup[x - 1]->setAnchorPoint(Vec2(0.5, 0.5f));
		Game::pickup[x - 1]->setPosition(Vec2(x0, y0));
		Game::pickup[x - 1]->setVisible(false);
		this->getParent()->addChild(Game::pickup[x - 1], 2);
	}
	//for (int i = 0; i < x-1; i++) {
	//	char pickupname[10] = "pickup";
	//	char str[10];
	//	sprintf(str, "%d", i);
	//	strcat(pickupname, str);
	//	spawnPoint_0 = group->getObject(pickupname);
	//	if (spawnPoint_0 == ValueMap()) { break; }
	//	int  x0 = spawnPoint_0["x"].asInt();
	//	int  y0 = spawnPoint_0["y"].asInt();
	//	int tooltype = spawnPoint_0["ToolType"].asInt();
	//	Game::pickup[i] = PickupBase::createWithType((PickupTypes)tooltype);
	//	Game::pickup[i]->setAnchorPoint(Vec2(0.5,0.5f));
	//	Game::pickup[i]->setPosition(Vec2(x0, y0));
	//	Game::pickup[i]->setVisible(false);
	//	this->getParent()->addChild(Game::pickup[i], 2);
	//}


}
void OurTank::addpickupV() {
	static int x = 0;
	x = 0;
	TMXObjectGroup *group = Game::_tileMap->getObjectGroup("objects");
	ValueMap spawnPoint_0 = group->getObject("playerA");
	PickupBase * pickupV[20] = { NULL };


	while (spawnPoint_0 != ValueMap()) {
		char pickupname[10] = "pickupV";
		char str[10];
		sprintf(str, "%d", x);
		strcat(pickupname, str);
		++x;

		//log("%s", pickupname);
		spawnPoint_0 = group->getObject(pickupname);
		if (spawnPoint_0 == ValueMap()) { break; }
		++Game::nPickupV;
	}
	for (int i = 0; i < x - 1; i++) {
		char pickupname[10] = "pickupV";
		char str[10];
		sprintf(str, "%d", i);
		strcat(pickupname, str);
		spawnPoint_0 = group->getObject(pickupname);
		if (spawnPoint_0 == ValueMap()) { break; }
		int  x0 = spawnPoint_0["x"].asInt();
		int  y0 = spawnPoint_0["y"].asInt();
		int tooltype = spawnPoint_0["ToolType"].asInt();
		pickupV[i] = PickupBase::createWithType((PickupTypes)tooltype);
		pickupV[i]->setAnchorPoint(Vec2(0.5, 0.5f));
		pickupV[i]->setPosition(Vec2(x0, y0));
		this->getParent()->addChild(pickupV[i], 2);
	}
	x--;
	TMXObjectGroup *group1 = Game::_tileMap->getObjectGroup("helps");
	if (group1!=nullptr) {
		ValueMap spawnPoint_0 = group1->getObject("help0");
		int xx = 0;
		while (spawnPoint_0 != ValueMap()) {
			x++;
			int  x0 = spawnPoint_0["x"].asInt();
			int  y0 = spawnPoint_0["y"].asInt();
			int HelpNum = spawnPoint_0["HelpNum"].asInt();
			pickupV[x - 1] = PickupBase::createWithType((PickupTypes)HelpNum);
			pickupV[x - 1]->setAnchorPoint(Vec2(0.5, 0.5f));
			pickupV[x - 1]->setPosition(Vec2(x0, y0));
			this->getParent()->addChild(pickupV[x - 1], 2);
			xx++;
			char pickupname[10] = "help";
			char str[10];
			sprintf(str, "%d", xx);
			strcat(pickupname, str);
			spawnPoint_0 = group1->getObject(pickupname);
		}
	}

}

void OurTank::useSkill()
{
	switch (this->getSkillType())
	{
	case NOSKILL:
		break;
	case SKILL_0:
		for (int i = 0; i < Game::nEnemy; ++i)
		{
			//Game::enemyAIs[i]->isFrozen = true;
			Game::enemy[i]->mydt = 5;
			Game::enemy[i]->setColor(Color3B::GRAY);
		}
		this->setSkillType(NOSKILL);
		break;
	case SKILL_1:
		break;
	case SKILL_2:
		break;
	}
	return;
}

void OurTank::addboss()
{
	static int x = 0;
	x = 0;
	TMXObjectGroup *group = Game::_tileMap->getObjectGroup("objects");
	ValueMap spawnPoint_0 = group->getObject("playerA");
	//Boss* boss_spawn[10] = {};
	Boss* boss[10] = { NULL };
	while (spawnPoint_0 != ValueMap()) {
		char bossname[10] = "boss";
		char str[10];
		sprintf(str, "%d", x);
		strcat(bossname, str);
		++x;

		//log("%s", pickupname);
		spawnPoint_0 = group->getObject(bossname);
		if (spawnPoint_0 == ValueMap()) { break; }
	}
	for (int i = 0; i < x - 1; i++) {
		char bossname[10] = "boss";
		char str[10];
		sprintf(str, "%d", i);
		strcat(bossname, str);
		spawnPoint_0 = group->getObject(bossname);
		//if (spawnPoint_0 == ValueMap()) { break; }
		int  x0 = spawnPoint_0["x"].asInt();
		int  y0 = spawnPoint_0["y"].asInt();
		boss[i] = Boss::create();
		boss[i]->setPosition(Vec2(x0, y0));
		this->getParent()->addChild(boss[i], 2);
	}
	if (x > 1)
	{
		log("There are some boss!!!!!!!!!!!!!!!!!!!!!");
		boss[0]->setRotation(180);
		auto enemy0 = Enemy::createWithEnemyTypes(EnemyTypeEnemy1);
		enemy0->isFrozen = true;
		//enemy0->setVisible(false);
		enemy0->setDirection(142);
		enemy0->setWeaponType(WEAPON_3);
		enemy0->setPosition(boss[0]->getPosition() + Vec2(-180, -30));
		this->getParent()->addChild(enemy0);
		Game::enemy[0] = enemy0;
		Game::enemyAIs[0] = EnemyAI::createWithEnemy(enemy0);

		boss[0]->setRotation(180);
		auto enemy1 = Enemy::createWithEnemyTypes(EnemyTypeEnemy1);
		enemy1->isFrozen = true;
		//enemy0->setVisible(false);
		enemy1->setDirection(142);
		enemy1->setWeaponType(WEAPON_3);
		enemy1->setPosition(boss[0]->getPosition() + Vec2(180, -30));
		this->getParent()->addChild(enemy1);
		Game::enemy[1] = enemy1;
		Game::enemyAIs[1] = EnemyAI::createWithEnemy(enemy1);

		boss[0]->setRotation(180);
		auto enemy2 = Enemy::createWithEnemyTypes(EnemyTypeEnemy1);
		enemy2->isFrozen = true;
		//enemy0->setVisible(false);
		enemy2->setDirection(142);
		enemy2->setWeaponType(WEAPON_3);
		enemy2->setPosition(boss[0]->getPosition() + Vec2(100, -60));
		this->getParent()->addChild(enemy2, 0);
		Game::enemy[2] = enemy2;
		Game::enemyAIs[2] = EnemyAI::createWithEnemy(enemy2);

		boss[0]->setRotation(180);
		auto enemy3 = Enemy::createWithEnemyTypes(EnemyTypeEnemy1);
		enemy3->isFrozen = true;
		//enemy0->setVisible(false);
		enemy3->setDirection(142);
		enemy3->setWeaponType(WEAPON_3);
		enemy3->setPosition(boss[0]->getPosition() + Vec2(-100, -60));
		this->getParent()->addChild(enemy3);
		Game::enemy[3] = enemy3;
		Game::enemyAIs[3] = EnemyAI::createWithEnemy(enemy3);

	}
};