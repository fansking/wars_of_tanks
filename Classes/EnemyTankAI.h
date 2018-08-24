#pragma once
#include "cocos2d.h"
#include "Enemy.h"

static const char* enemyTankType[] =
{
	"normalU.png", "speedU.png", "armor1U.png"
};

class EnemyAI
{
public:
	EnemyAI();
	~EnemyAI();
	static EnemyAI* createEnemyAIWithTank(Enemy * tank);
	void initEnemyAIWithTank(Enemy * tank);
	void update(float delta);

private:
	void addTank(float delta);
	void tankAction(float delta);

private:
	CCArray* mEnemyTanks;
	Enemy * mTank;
	TMXMapInfo * mTileMapInfo;
	//出现地点
	CCPoint bornPoint[3];
};
