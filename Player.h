#pragma once

#include "UnitObject.h"
#include "cocos2d.h"

class Player : public UnitObject
{
public:
	CREATE_FUNC(Player);
	~Player();
	bool init() override;
	static Player* CreateUnit(int _recentHp,Vec2 _position);
	virtual UnitObject* CopyUnit(UnitObject* _target) override;
	virtual float getDamage() override 
	{
		return recentHp*0.08f;
	};
	bool eating;
	
	void EatEvent(bool _var);
	void EatingUpdate(float delta);
	void StartEating(bool var);
	RepeatForever* repeatEatAction;
	virtual void update(float) override;
	virtual void KnockBack(UnitObject* _target) override;
	virtual void DealDamage(UnitObject* _target) override;

};
