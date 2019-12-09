#pragma once

#include "UnitObject.h"
#include "cocos2d.h"

class Enemy : public UnitObject
{
public:
	CREATE_FUNC(Enemy);
	virtual bool init() override;
	static Enemy* CreateUnit(int _recentHp,Vec2 _position);
	virtual UnitObject* CopyUnit(UnitObject* _target) override;
	virtual float getDamage() override
	{
		return recentHp*0.09f;
	}
};
