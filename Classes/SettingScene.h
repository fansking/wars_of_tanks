#pragma once
#include<cocos2d.h>
#ifndef _SETTING_SCENE_H_
#define _SETTING_SCENE_H_

class Setting :public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	bool init();
	void menuSoundToggleCallback(Ref *pSender);
	void menuMusicToggleCallback(Ref *pSender);
	void menuOkCallback(Ref *pSender);
	CREATE_FUNC(Setting);

};
#endif