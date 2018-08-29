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

	default:
		path = HELPPATH;

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
	else {
		
		showHelp((int)this->getPickupType());
		this->removeFromParent();
	}
}

void PickupBase::showHelp(int helpNum) {
	helpNum -= 20;
	auto layer = Layer::create();
	layer->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 2));
	string str = "map/helpmenu/help" + to_string(helpNum) + ".png";
	auto sp = Sprite::create(str);
	layer->addChild(sp);
	layer->setTag(14);
	Game::menuLayer->addChild(layer, 0);

	auto visiblesize = Director::getInstance()->getVisibleSize();
	auto closeItem = MenuItemImage::create("UI/unvisible.png", "UI/unvisible.png", CC_CALLBACK_1(PickupBase::closeHelpLayerCallback, this));
	closeItem->setPosition(Vec2(visiblesize.width/2 , visiblesize.height/2));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	menu->setTag(15);
	Game::menuLayer->addChild(menu,20);

	Director::getInstance()->pause();

}

void PickupBase::closeHelpLayerCallback(Ref* pSender) {
	Game::menuLayer->removeChildByTag(14);
	Game::menuLayer->removeChildByTag(15);
	Game::menuLayer->removeChildByTag(14);
	Game::menuLayer->removeChildByTag(15);
	Director::getInstance()->resume();
}





