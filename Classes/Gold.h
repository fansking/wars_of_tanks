#pragma once
#include "cocos2d.h"
#include "PickupBase.h"

using namespace cocos2d;

class Gold : public PickupBase
{

public:

	virtual void isContact();
};