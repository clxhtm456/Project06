#pragma once

#include "cocos2d.h"
#include "UnitObject.h"
#include "GameManager.h"

using namespace cocos2d;

class MainGameScene : public Layer
{
private :
	static Node* _selectStageScene;
	static int _stageCount;
protected :
	bool gamePaused;
	EventListenerMouse* listener;
	Menu* menu;
	LayerColor* fadeBack;
	GameManager* gameManager;
public:
	static Node* GetSelectStageScene()
	{
		return _selectStageScene;
	}
	static int GetStageCount()
	{
		return _stageCount;
	}
	CREATE_FUNC(MainGameScene);
	bool init() override;
	static Scene* createScene(Node* selectStageScene ,int stageCount);
	static Scene* createScene();
	void RetryScene();
	void ReturnHomeScene();
	void GamePaused(bool _var);
	void GameSetting();
	void StageBuilding();
	void onEnter() override;
	bool onTouchBegan(Touch *touch, Event* event);
	void GameOver();
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};