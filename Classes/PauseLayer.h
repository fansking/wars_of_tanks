#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class PauseLayer : public Layer
{
public:
	CREATE_FUNC(PauseLayer);

	virtual bool init();

	void menuItemChooseStageCallback(Ref * pSender);
	void menuItemHomePageCallback(Ref * pSender);
	void menuItemRestartCallback(Ref * pSender);
};