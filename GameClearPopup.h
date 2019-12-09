#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class GameClearPopup : public Layer
{
public :
	CREATE_FUNC(GameClearPopup);
	bool init() override;

	void onEnter() override;
	bool onTouchBegan(Touch *touch, Event* event);
	void GoSelectScene();
};