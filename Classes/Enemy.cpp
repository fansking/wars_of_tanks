#include"Enemy.h"

Enemy::Enemy(EnemyTypes enemyType) : OurTank(2){
	this->enemyType = enemyType;
}

Enemy *Enemy::createWithEnemyTypes(EnemyTypes enemyType) {
	Enemy *enemy = new Enemy(enemyType);
	//auto body = PhysicsBody::createEdgeBox(Size(32, 32), PHYSICSBODY_MATERIAL_DEFAULT, 3.0f, Vec2(16, 16));
	//body->setCategoryBitmask(0x02);
	//body->setContactTestBitmask(0x02);
	//enemy->setPhysicsBody(body);
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
		auto body = PhysicsBody::createEdgeBox(Size(32, 32),
			PHYSICSBODY_MATERIAL_DEFAULT, 3.0f);
		
		body->setCategoryBitmask(0x04);
		//body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0x0F);

		enemy->setPhysicsBody(body);
		
		//enemy->setVisible(false);
		//enemy->spawn();
		//enemy->unscheduleUpdate();
		//enemy->scheduleUpdate();
		enemy->setTag(3);

		return enemy;
		
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

void Enemy::update(float dt) {
	
}

void Enemy::shoot() {
	
}