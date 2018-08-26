#include"Enemy.h"
#include "GameScene.h"
Enemy::Enemy(EnemyTypes enemyType) : OurTank(2){
	this->enemyType = enemyType;
}

Enemy *Enemy::createWithEnemyTypes(EnemyTypes enemyType) {
	++Game::nEnemy;
	Enemy *enemy = new Enemy(enemyType);
	enemy->nHP = 3;
	enemy->weaponType = WEAPON_0;

	const char * enemyFrameName = Enemy_1;
	switch (enemyType) {
	case EnemyTypeEnemy1:
		enemyFrameName = Enemy_1;
		enemy->nHP = 3;
		break;
	case EnemyTypeEnemy2:
		enemyFrameName = Enemy_2;
		enemy->nHP = 5;
		break;
	}
	if (enemy && enemy->initWithFile(Enemy_1)) {  //check if enemy is created
		enemy->autorelease();
		auto body = PhysicsBody::createEdgeBox(enemy->getContentSize(),
			PHYSICSBODY_MATERIAL_DEFAULT, 3.0f);
		
		body->setCategoryBitmask(0x08);
		body->setContactTestBitmask(0x04);

		enemy->setPhysicsBody(body);

		enemy->setTag(3);

		return enemy;
		
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

void Enemy::update(float dt) {
	/*static float t = 0;
	t += dt;
	if (t > 1) {
		Bullet * bullet = Bullet::createWithImage();
		this->getParent()->addChild(bullet);
		bullet->shootBulletFromTank(this);
	}*/
}

void Enemy::shoot() {
	openFire(true);
}

