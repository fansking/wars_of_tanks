#include"Enemy.h"



Enemy::Enemy(EnemyTypes enemyType) {
	this->enemyType = enemyType;
	this->initialHitPoints = 1;
	this->velocity = Vec2::ZERO;
}

Enemy *Enemy::createWithEnemyTypes(EnemyTypes enemyType) {
	Enemy *enemy = new Enemy(enemyType);
	const char * enemyFrameName = Enemy_1;
	switch (enemyType) {
	case EnemyTypeEnemy1:
		enemyFrameName = Enemy_1;
		enemy->initialHitPoints = 3;
		break;
	case EnemyTypeEnemy2:
		enemyFrameName = Enemy_2;
		enemy->initialHitPoints = 5;
		break;
	}
	if (enemy && enemy->initWithSpriteFrameName(enemyFrameName)) {  //check if enemy is created
		enemy->autorelease();
		auto body = PhysicsBody::create();
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0x01);

		enemy->setPhysicsBody(body);
		enemy->setVisible(false);
		enemy->spawn();
		enemy->unscheduleUpdate();
		enemy->scheduleUpdate();

		return enemy;
		
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

void Enemy::update(float dt) {
	Vec2 moveLen = velocity;
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
	hitPoints = initialHitPoints;
	this->setVisible(true);
}

void Enemy::shoot() {
	
}