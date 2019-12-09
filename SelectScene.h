#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class SelectScene : public Layer
{
public:
	bool init() override;
	CREATE_FUNC(SelectScene);
	static Scene* createScene();
	void StartMainSceneButton(int _num);
	void MenuButton();
	void StageSceneLoading();
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};