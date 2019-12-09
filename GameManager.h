#pragma once

#include "cocos2d.h"
#include "UnitObject.h"
#include "Player.h"

using namespace cocos2d;

class GameManager : public Layer, public MyDelegate
{
public:
	virtual bool init();
	virtual void update(float delta);
	virtual void DelegateMethod1(UnitObject* target) override;
	virtual void DelegateMethod2(UnitObject* target) override;
	int HpCheck();

	void AddUnitList(UnitObject* unit);
	void UnitAllPaused(bool _var);
	bool EraseUnitList(UnitObject* unit);
	bool ReplaceUnitList(UnitObject* erase,UnitObject* add);

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	CREATE_FUNC(GameManager);
	~GameManager();
private :
	Player* lastSelectPlayer;
	std::list<UnitObject*> unitList;
	Vec2 tempMouseCursor;
	bool click;
};

