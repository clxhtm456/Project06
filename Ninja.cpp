#include "Ninja.h"

using namespace cocos2d;

bool Ninja::init()
{
	UnitObject::init();
	
	characterSprite = Sprite::create("Image/MainScene/Ninja_Character.png");
	characterSprite->setPosition(0,0);
	this->addChild(characterSprite);
	return true;
}

Ninja* Ninja::CreateUnit(int _recentHp,Vec2 _position)
{
	auto playerUnit = Ninja::create();
	playerUnit->setPosition(_position);
	playerUnit->SetHp(_recentHp);
	playerUnit->faction = 1;
	playerUnit->UnitActive(true);
	return playerUnit;
}
UnitObject* Ninja::CopyUnit(UnitObject* _target)
{
	UnitObject* newUnit = Ninja::CreateUnit(1,_target->getPosition());
	auto _delegate = _target->m_delegate;
	newUnit->UnitDeleteDelegate(_delegate);
	this->getParent()->addChild(newUnit);
	return newUnit;
}