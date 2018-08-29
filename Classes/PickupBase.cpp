#include "PickupBase.h"
#include "GameScene.h"
#include "Skill.h"
#include <cstring>

PickupBase * PickupBase::createWithType(PickupTypes type)
{
	++Game::nPickup;
	auto item = new PickupBase();
	std::string path;
	item->setPickupType(type);
	switch (type)
	{
	case Gold:
		path = GOLDPATH;
		break;
	case Skill_Shield:
		path = SHIELDPATH;
		break;
	case Bulletscatter:
		path = BULLETSCATTERPATH;
		break;
	case Bluebullet:
		path = BLUEBULLETPATH;
		break;
	case Redbullet:
		path = REDBULLETPATH;
		break;
	case Addblood:
		path = ADDBLOODPATH;
		break;
	case Speedup:
		path = SPEEDUPPATH;
		break;
	}
	if (item && item->initWithFile(path))
	{
		item->autorelease();
	}
	auto body = PhysicsBody::createEdgeBox(item->getContentSize());
	body->setCategoryBitmask(0x02);
	body->setContactTestBitmask(0x01);
	body->setCollisionBitmask(0x00);
	item->setPhysicsBody(body);
	item->setTag(6);
	return item;
}

PickupBase * PickupBase::createWithImage(const char * path)
{
	auto item = new PickupBase();
	if (item && item->initWithFile(path))
	{
		item->autorelease();
	}
	auto body = PhysicsBody::createEdgeBox(item->getContentSize());
	body->setCategoryBitmask(0x02);
	body->setContactTestBitmask(0x01);
	item->setPhysicsBody(body);
	item->setTag(6);
	return item;
}

void PickupBase::isContact(OurTank * player)
{
	log("pick up");
	
	if (this->getPickupType() == Skill_Shield) {
		Shield * shield = Shield::createshield();
		shield->ShowWithTank(player);
		this->removeFromParent();
	}else if (this->getPickupType() == Gold) {
		player->setWeaponType(WEAPON_4);
		this->removeFromParent();
	}
	else if (this->getPickupType() == Bulletscatter) {
		player->setWeaponType(WEAPON_3);
		this->removeFromParent();
	}
	else if (this->getPickupType() == Bluebullet) {
		player->setWeaponType(WEAPON_1);
		this->removeFromParent();
	}
	else if (this->getPickupType() == Redbullet) {
		player->setWeaponType(WEAPON_2);
		this->removeFromParent();
	}
	else if (this->getPickupType() == Addblood) {
		player->setHP(player->getHP() + 1);
		Game::lifeTTF->setString(to_string(player->getHP()));
		this->removeFromParent();
	}
	else if (this->getPickupType() == Speedup) {
		player->setVel(player->getVel() * 2);
		this->removeFromParent();
	}
}