#include "Monk.h"

using namespace cocos2d;

bool Monk::init()
{
	UnitObject::init();
	
	characterSprite = Sprite::create("Image/MainScene/Monk_Character.png");
	characterSprite->setPosition(0,0);
	this->addChild(characterSprite);
	return true;
}

Monk* Monk::CreateUnit(int _recentHp,Vec2 _position)
{
	auto playerUnit = Monk::create();
	playerUnit->setPosition(_position);
	playerUnit->SetHp(_recentHp);
	playerUnit->faction = 3;
	playerUnit->UnitActive(true);
	return playerUnit;
}
UnitObject* Monk::CopyUnit(UnitObject* _target)
{
	UnitObject* newUnit = Monk::CreateUnit(1,_target->getPosition());
	auto _delegate = _target->m_delegate;
	newUnit->UnitDeleteDelegate(_delegate);
	this->getParent()->addChild(newUnit);
	return newUnit;
}
bool Monk::TakeDamage(float _damage)
{
	return false;
}
Monk::~Monk()
{
}
void Monk::KnockBack(UnitObject* _target)
{
	auto depth =  getRadius()+_target->getRadius() - getPosition().distance((_target->getPosition()));
	float tempAngle = atan2(this->getPosition().y - _target->getPosition().y,this->getPosition().x - _target->getPosition().x);//�Ի簢
		auto xValue = depth*0.5f*cos(tempAngle);
		auto yValue = depth*0.5f*sin(tempAngle);
		if(this->getPosition().x > _target->getPosition().x && xValue < 0)
			xValue *= -1;
		if(this->getPosition().y > _target->getPosition().y && yValue < 0)
			yValue *= -1;
		this->setPosition(
		this->getPosition().x+xValue,
		this->getPosition().y+yValue
		);

		angle = PI-(angle)+ (2*tempAngle);
}