#pragma once

#include "OurTank.h"

#define Enemy_1 "map/enmy_1.png"
#define Enemy_2 "map/enmy_2.png"
typedef enum {
	EnemyTypeEnemy1,
	EnemyTypeEnemy2
}EnemyTypes;
class Enemy :public OurTank {
	CC_SYNTHESIZE(EnemyTypes, enemyType, EnemyType);//EnemyType

public:
	Enemy(EnemyTypes enemyType);

	void shoot();
	virtual void update(float dt);
	static Enemy * createWithEnemyTypes(EnemyTypes enemyType);

};