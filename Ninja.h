#pragma once

#include "UnitObject.h"
#include "cocos2d.h"

class Ninja : public UnitObject
{
public:
	CREATE_FUNC(Ninja);
	bool init() override;
	static Ninja* CreateUnit(int _recentHp,Vec2 _position);
	virtual UnitObject* CopyUnit(UnitObject* _target) override;

	virtual float getDamage() override
	{
		return recentHp*0.15f;
	}
	
};
