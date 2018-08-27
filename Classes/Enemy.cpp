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
		auto body = PhysicsBody::createCircle(enemy->getContentSize().width / 2);
		
		body->setCategoryBitmask(0x0C);
		body->setContactTestBitmask(0x0C);
		body->setCollisionBitmask(0xFF);
		body->getShape(0)->setRestitution(.0f);
		body->getShape(0)->setFriction(0.0f);
		body->getShape(0)->setDensity(0.0f);
		body->setDynamic(true);
		body->setGravityEnable(false);

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

