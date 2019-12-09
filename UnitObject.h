#pragma once

#include "cocos2d.h"
#include "DefineVariable.h"
 
using namespace cocos2d;

class MyDelegate;
class UnitObject : public Layer
{
public:
	static UnitObject* CreateUnitWithType(int _type,float _hp, Vec2 _pos);
	
	virtual float getDamage() = 0;
	virtual void update(float);
	virtual bool init();
	virtual void DealDamage(UnitObject* _target);
	virtual bool TakeDamage(float _damage);
	virtual void KnockBack(UnitObject* _target);
	virtual UnitObject* CopyUnit(UnitObject* _target) = 0;

	void RemoveUnit();
	void UnitDeleteDelegate(MyDelegate* _delegate);
	void ModuleSize();
	void UnitMove(float);
	void FlareEffect();
	void SetHp(float _value);
	void KnockBackHori();
	void KnockBackVert();
	void KnockBackCheck();
	void HpCheck();
	void UnitActive(bool _var);
	bool CheckCollision(UnitObject* _target);
	bool CheckWallHori();
	bool CheckWallVert();
	
	float getRecentHp()
	{
		return recentHp;
	}
	float getRadius()
	{
		if(characterSprite == nullptr)
			return 0;
		return getImageSize()*characterSprite->getContentSize().width/2;
	}
	float getAccelx()
	{
		//return accelx*UNITSPEED;
		return cos(angle)*UNITSPEED;
	}
	float getAccely()
	{
		//return accely*UNITSPEED;
		return sin(angle)*UNITSPEED;
	}
	float getImageSize()
	{
		if(maxHp == 0)
			return 0;
		float size = (recentHp/maxHp)  * 0.8f + 0.2f;
		return size;
	}
	~UnitObject();
	int faction;
	/*float accelx;
	float accely;*/
	float angle;
	MyDelegate* m_delegate;
	UnitObject* lastAttackedUnit;
protected:
	float maxHp;
	float recentHp;
	Sprite* characterSprite;
	GLProgram * shader;
};

class MyDelegate
{
public:
	virtual void DelegateMethod1(UnitObject* target) = 0;
	virtual void DelegateMethod2(UnitObject* target) = 0;
};