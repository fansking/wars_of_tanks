#include"Enemy.h"

Enemy::Enemy(EnemyTypes enemyType) : OurTank(2){
	this->enemyType = enemyType;
}

Enemy *Enemy::createWithEnemyTypes(EnemyTypes enemyType) {
	Enemy *enemy = new Enemy(enemyType);
	auto body = PhysicsBody::createEdgeBox(Size(32, 32), PHYSICSBODY_MATERIAL_DEFAULT, 3.0f, Vec2(16, 16));
	body->setCategoryBitmask(0x02);
	body->setContactTestBitmask(0x02);
	enemy->setPhysicsBody(body);
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
		auto body = PhysicsBody::create();
		/*
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0x01);

		enemy->setPhysicsBody(body);
		*/
		enemy->setVisible(false);
		enemy->spawn();
		enemy->unscheduleUpdate();
		enemy->scheduleUpdate();
		enemy->setTag(2);

		return enemy;
		
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

void Enemy::update(float dt) {
	Vec2 moveLen = Vec2(0, -50)*dt;
	this->setPosition(this->getPosition() + moveLen);
	if (this->getPosition().y + this->getContentSize().height / 2 < 0) {
		this->spawn();
	}
	shoot();//now it is null
}
//spawn() is used to reset position
void Enemy::spawn() {
	Size screenSize = Director::getInstance()->getVisibleSize();
	float yPos = screenSize.height + this->getContentSize().height / 2;
	float xPos = CCRANDOM_0_1()*(screenSize.width - this->getContentSize().width)
		+ this->getContentSize().width / 2;
	this->setPosition(Vec2(xPos, yPos));
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->setVisible(true);
}

void Enemy::shoot() {
	
}