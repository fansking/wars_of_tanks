#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class VictoryLayer : public Layer
{
public:
	CREATE_FUNC(VictoryLayer);

	virtual bool init();

	void menuItemChooseStageCallback(Ref * pSender);
	void menuItemHomePageCallback(Ref * pSender);
	void menuItemRestartCallback(Ref * pSender);
	void menuItemNextLevelCallback(Ref * pSender);
};