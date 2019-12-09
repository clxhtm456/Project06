#pragma once

#include "UnitObject.h"
#include "cocos2d.h"

class Monk : public UnitObject
{
public:
	CREATE_FUNC(Monk);
	bool init() override;
	static Monk* CreateUnit(int _recentHp,Vec2 _position);
	virtual UnitObject* CopyUnit(UnitObject* _target) override;
	~Monk();
	virtual float getDamage() override
	{
		return recentHp*0.15f;
	}

	bool TakeDamage(float _damage);
	virtual void KnockBack(UnitObject* _target) override;
	
};
