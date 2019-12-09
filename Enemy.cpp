#include "Enemy.h"

using namespace cocos2d;

bool Enemy::init()
{
	UnitObject::init();
	
	characterSprite = Sprite::create("Image/MainScene/Enemy_Character.png");
	characterSprite->setPosition(0,0);
	this->addChild(characterSprite);
	return true;
}

Enemy* Enemy::CreateUnit(int _recentHp,Vec2 _position)
{
	auto playerUnit = Enemy::create();
	playerUnit->setPosition(_position);
	playerUnit->SetHp(_recentHp);
	playerUnit->faction = 1;
	playerUnit->UnitActive(true);
	return playerUnit;
}
UnitObject* Enemy::CopyUnit(UnitObject* _target)
{
	UnitObject* newUnit = Enemy::CreateUnit(1,_target->getPosition());
	auto _delegate = _target->m_delegate;
	newUnit->UnitDeleteDelegate(_delegate);
	this->getParent()->addChild(newUnit);
	return newUnit;
}