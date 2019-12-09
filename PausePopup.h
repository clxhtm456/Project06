#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class PausePopup :public Layer
{
private:
	Node* _listener;
	SEL_CallFunc _selector;
public :
	static PausePopup* create(Node* listener = nullptr, SEL_CallFunc selector = NULL);
	bool init() override;

	void onEnter() override;
	bool onTouchBegan(Touch *touch, Event* event);
};