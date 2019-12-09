#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class GameOverPopup : public Layer
{
public :
	int gameoverOption;
	static GameOverPopup* create(int option = -1);
	bool init() override;

	void onEnter() override;
	bool onTouchBegan(Touch *touch, Event* event);
	void RestartScene();
};