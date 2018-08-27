#pragma once
#include "Bullet.h"

class Shield : public Sprite {
public:
	static Shield* createshield();
	void ShowWithTank(OurTank * tank);
	virtual void update(float dt);
};


