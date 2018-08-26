#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class GameoverLayer : public Layer
{
public:
	CREATE_FUNC(GameoverLayer);

	virtual bool init();

	void menuItemChooseStageCallback(Ref * pSender);
	void menuItemHomePageCallback(Ref * pSender);
	void menuItemRestartCallback(Ref * pSender);
};