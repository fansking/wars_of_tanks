#include "EnemyAI.h"
#include <time.h>
#include <stdlib.h>
#include <exception>
#include "Bullet.h"
#include "GameScene.h"
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
	int x = pos.x / Game::tileSize;
	int y = ((Game::mapSizeHeight * Game::tileSize) - pos.y) / Game::tileSize;
	return Vec2(x, y);
}

bool EnemyAI::isCollidable(Vec2 target) {
	Vec2 coordTarget = tileCoordFromPosition(target + Vec2(vel.x / 100 * 16,
		vel.y / 100 * 16));
	int tileGid = layer->getTileGIDAt(coordTarget);
	if (tileGid > 0) {
		Value prop = Game::_tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();
		std::string collision = propValueMap["collidable"].asString();
		if (collision == "true")
			return true;
	}
	return false;
}
int nposition[4][3] = { {0,0,100},{180,0,-100},{90,100,0},{270,-100 ,0} };
void EnemyAI::update(float dt)
{
	//obj->runAction(MoveBy::create(0.2, Vec2(0, 5) * dt));

	Vec2 target = Vec2::ZERO;
	try
	{
		target = obj->getPosition() + vel * dt;
	}
	catch (std::exception & e)
	{
		return;
	}

	target = obj->getPosition() + vel * dt;
	Size screenSize = Size((Vec2(Game::mapSizeWidth * Game::tileSize,
		Game:: mapSizeHeight * Game::tileSize)));
	if (target.y + 16 >= screenSize.height || target.y - 16 <= 0 || 
		target.x + 16 >= screenSize.width || target.x - 16 <= 0)
	{
		int nDirection = rand() % 4;
		obj->setDirection(nDirection);

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
		Value prop = Game::_tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["collidable"].asString();
		if (collision == "true") {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.mp3");
			//srand(time(NULL));
			int nDirection = rand() % 4;
			for (int i = 0; i < 4; i++) {
				vel = Vec2(nposition[nDirection][1], nposition[nDirection][2]);
				if (!isCollidable(target)) {
					obj->runAction(RotateTo::create(0.2, nposition[nDirection][0]));
					return;
				}
				if (nDirection == 3) nDirection = -1;
				nDirection++;
			}
			/*switch (nDirection)
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
			}*/
			//return;
		}
	}
	if (obj->mydt < 0) {
		//obj->openFire();
		obj->mydt = 1;
	}
	obj->mydt -= dt;
	obj->runAction(MoveTo::create(0, target));
}