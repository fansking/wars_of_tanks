#include "EnemyAI.h"
#include <time.h>
#include <stdlib.h>

EnemyAI::EnemyAI()
{
}

EnemyAI * EnemyAI::createWithEnemy(Enemy * obj)
{
	srand(time(NULL));
	auto enemyAI = new EnemyAI();
	enemyAI->obj = obj;
	enemyAI->vel = Vec2(0, 100);

	return enemyAI;
}

Vec2 EnemyAI::tileCoordFromPosition(Vec2 pos) {
	int x = pos.x / tileSize;
	int y = ((mapSize * tileSize) - pos.y) / tileSize;
	return Vec2(x, y);
}

void EnemyAI::update(float dt)
{
	//obj->runAction(MoveBy::create(0.2, Vec2(0, 5) * dt));

	Vec2 target = obj->getPosition() + vel * dt;
	Size screenSize = Director::getInstance()->getVisibleSize();
	if (target.y + 16 >= screenSize.height || target.y - 16 <= 0 || 
		target.x + 16 >= screenSize.width || target.x - 16 <= 0)
	{
		int nDirection = rand() % 4;
		log("%d", nDirection);
		switch (nDirection)
		{
		case 0:
			obj->runAction(RotateTo::create(0, 0));
			vel = Vec2(0, 100); break;
		case 1:
			obj->runAction(RotateTo::create(0, 180));
			vel = Vec2(0, -100); break;
		case 2:
			obj->runAction(RotateTo::create(0, 90));
			vel = Vec2(100, 0); break;
		case 3:
			obj->runAction(RotateTo::create(0, 270));
			vel = Vec2(-100, 0); break;
		}
		return;
	}
	Vec2 coordTarget = tileCoordFromPosition(target + Vec2(vel.x / 100 * 16,
		vel.y / 100 * 16));
	int tileGid = layer->getTileGIDAt(coordTarget);
	if (tileGid > 0) {
		Value prop = tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["collidable"].asString();
		if (collision == "true") {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.mp3");
			srand(time(NULL));
			int nDirection = rand() % 4;
			switch (nDirection)
			{
			case 0:
				obj->runAction(RotateTo::create(0.2, 0));
				vel = Vec2(0, 100); break;
			case 1:
				obj->runAction(RotateTo::create(0.2, 180));
				vel = Vec2(0, -100); break;
			case 2:
				obj->runAction(RotateTo::create(0.2, 90));
				vel = Vec2(100, 0); break;
			case 3:
				obj->runAction(RotateTo::create(0.2, 270));
				vel = Vec2(-100, 0); break;
			}
			return;
		}
	}
	obj->runAction(MoveTo::create(0, target));
}