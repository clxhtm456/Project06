#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class TitleScene : public Layer
{
public:
	bool init() override;
	CREATE_FUNC(TitleScene);
	static Scene* createScene();
	void StartSelectSceneButton();
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};