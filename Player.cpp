#include "Player.h"
#include "DamageFont.h"

using namespace cocos2d;


bool Player::init()
{
	UnitObject::init();
	eating = false;
	characterSprite = Sprite::create("Image/MainScene/Player_Character.png");
	characterSprite->setPosition(0,0);
	this->addChild(characterSprite);


	return true;
}
void Player::EatEvent(bool _var)
{
	if(_var)
		this->runAction(repeatEatAction);
	else
		this->stopAction(repeatEatAction);
}

Player* Player::CreateUnit(int _recentHp,Vec2 _position)
{
	auto playerUnit = Player::create();
	playerUnit->setPosition(_position);
	playerUnit->SetHp(_recentHp);
	playerUnit->faction = 0;
	playerUnit->UnitActive(true);
	return playerUnit;
}
Player::~Player()
{
	this -> unscheduleAllSelectors();
}

UnitObject* Player::CopyUnit(UnitObject* _target)
{
	//_target->setOpacity(0);
	UnitObject* newUnit = Player::CreateUnit(1,_target->getPosition());
	auto _delegate = _target->m_delegate;
	newUnit->UnitDeleteDelegate(_delegate);
	this->getParent()->addChild(newUnit);
	return newUnit;
}
void Player::update(float delta)
{
	UnitObject::update(delta);
}

void Player::EatingUpdate(float delta)
{
	if(recentHp > 0)
		this->SetHp(this->getRecentHp()+HPREGEN*delta);
}
void Player::StartEating(bool var)
{
	if(eating != var)
	{
		if(var)
		{
			this -> schedule(schedule_selector(Player::EatingUpdate));
		}else
		{
			this -> unschedule(schedule_selector(Player::EatingUpdate));
		}
	}
	eating = var;
}

void Player::DealDamage(UnitObject* _target)
{
	if(!_target)
		return;
	if(_target->getRecentHp() <= 0)
		return;
	auto damage = this->getDamage();

	if(_target->TakeDamage(damage))
	{
		auto depth =  -_target->getRadius();
		float tempAngle = atan2(this->getPosition().y - _target->getPosition().y,this->getPosition().x - _target->getPosition().x);//입사각
	
		auto xValue = this->getPosition().x+depth*1.5f*cos(tempAngle);
		auto yValue = this->getPosition().y+depth*1.5f*sin(tempAngle);
	
		auto damageFont = DamageFont::create(damage,Vec2(xValue,yValue),Color4B::BLUE);
		this->getParent()->addChild(damageFont);
	}
}



void Player::KnockBack(UnitObject* _target)
{
	auto depth =  getRadius()+_target->getRadius() - getPosition().distance(_target->getPosition());
	float tempAngle = atan2(this->getPosition().y - _target->getPosition().y,this->getPosition().x - _target->getPosition().x);//입사각
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

		if(this->faction !=_target->faction)
		{
			lastAttackedUnit = _target;
			if(eating)
			{
				SetHp(0);
				return;
			}
			this->DealDamage(_target);
		}
}