#include "UnitObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Math.h"
#include "DamageFont.h"
#include "Ninja.h"
#include "Monk.h"

using namespace cocos2d;

void UnitObject::update(float delta)
{
	UnitMove(delta);

	
	KnockBackCheck();
	HpCheck();
}
void UnitObject::UnitMove(float delta)
{
	this->setPosition(
		this->getPosition().x+getAccelx()*delta,
		this->getPosition().y+getAccely()*delta
		);
}
void UnitObject::RemoveUnit()
{
	this->removeFromParent();
}
void UnitObject::HpCheck()
{
	if(!this->lastAttackedUnit)
		return;
	if(this->getRecentHp() <= 0)
	{
		auto unit = lastAttackedUnit->CopyUnit(this);
		this->RemoveUnit();
		unit->FlareEffect();
	}
}
UnitObject::~UnitObject()
{
	UnitActive(false);
	if(m_delegate && recentHp <= 0 )
		m_delegate->DelegateMethod1(this);
	log("~UnitObject");
}
bool UnitObject::init()
{
	if(!Layer::init())
		return false;

	m_delegate = nullptr;

	shader = new GLProgram();
	shader->initWithFilenames("Shader/white.vsh", "Shader/white.fsh");
	shader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	shader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION,GLProgram::VERTEX_ATTRIB_POSITION );
	shader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);

    shader->link();
	shader->updateUniforms();


	lastAttackedUnit = nullptr;
	characterSprite = nullptr;

	maxHp = UNITMAXHP;
	recentHp = maxHp;
	ModuleSize();
	
	auto random = rand()%4;
	if(random == 0)
		angle = PI/4;
	else if(random == 1)
		angle = -PI/4;
	else if(random == 2)
		angle = PI*3/4;
	else
		angle = -(PI*3/4);
	log("unitCreate");
	return true;
}
void UnitObject::UnitActive(bool _var)
{
	if(_var)
		this->scheduleUpdate();
	else
		this->unscheduleUpdate();
}
void UnitObject::ModuleSize()
{
	if(!characterSprite)
		return;
	
	characterSprite->setScale(getImageSize());
}
bool UnitObject::CheckCollision(UnitObject* _target)
{
	if(_target == nullptr)
		return false;
	auto depth =  getRadius()+_target->getRadius() - getPosition().distance(_target->getPosition());
	if(depth >= 0 )//충돌시
	{
		return true;
	}
	return false;
}
void UnitObject::SetHp(float _value)
{
	if(_value > maxHp)
		_value = maxHp;
	recentHp = _value;
	ModuleSize();
}
void UnitObject::DealDamage(UnitObject* _target)
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
	
		auto damageFont = DamageFont::create(damage,Vec2(xValue,yValue));
		this->getParent()->addChild(damageFont);
	}
}
bool UnitObject::TakeDamage(float _damage)
{
	FlareEffect();
	SetHp(recentHp-_damage);
	return true;
}
void UnitObject::KnockBackHori()
{
	angle = PI-angle;
}
void UnitObject::KnockBackVert()
{
	angle = -1*angle;
}
void UnitObject::KnockBackCheck()
{
	CheckWallHori();
	CheckWallVert();
}
void UnitObject::FlareEffect()
{
	Vector<FiniteTimeAction*> actions;
	actions.pushBack(CallFunc::create([=]()->void
	{
		characterSprite->setGLProgram(shader);
	}
	));
	actions.pushBack(DelayTime::create(0.02f));
	actions.pushBack(CallFunc::create([=]()->void
	{
		characterSprite->setGLProgram(GLProgramCache::getInstance()->getGLProgram( GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
	}
	));
	actions.pushBack(DelayTime::create(0.02f));
	actions.pushBack(CallFunc::create([=]()->void
	{
		characterSprite->setGLProgram(shader);
	}
	));
	actions.pushBack(DelayTime::create(0.02f));
	actions.pushBack(CallFunc::create([=]()->void
	{
		characterSprite->setGLProgram(GLProgramCache::getInstance()->getGLProgram( GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
	}
	));
	actions.pushBack(DelayTime::create(0.02f));
	auto sequence = Sequence::create(actions);
	characterSprite->runAction(sequence);
}

bool UnitObject::CheckWallHori()
{
	auto WinSize = Director::getInstance()->getWinSize();
	auto size = getRadius();
	if(this->getPosition().x -size < 0)
	{
		this->setPositionX(size);
		KnockBackHori();
		return true;
	}
	else if(this->getPosition().x +size > WinSize.width)
	{
		this->setPositionX(WinSize.width-size);
		KnockBackHori();
		return true;
	}
	return false;
}
bool UnitObject::CheckWallVert()
{
	auto WinSize = Director::getInstance()->getWinSize();
	auto size = getRadius();
	if(this->getPosition().y -size < 0)
	{
		this->setPositionY(size);
		KnockBackVert();
		return true;
	}
	else if(this->getPosition().y +size > WinSize.height)
	{
		this->setPositionY(WinSize.height-size);
		KnockBackVert();
		return true;
	}
	return false;
}
void UnitObject::KnockBack(UnitObject* _target)
{
	auto depth =  getRadius()+_target->getRadius() - getPosition().distance(_target->getPosition());
	float tempAngle = atan2(this->getPosition().y - _target->getPosition().y,this->getPosition().x - _target->getPosition().x);//입사각
	auto xValue = depth*0.5f*cos(tempAngle);
	auto yValue = depth*0.5f*sin(tempAngle);
	if(this->getPosition().x > _target->getPosition().x && xValue < 0)
		xValue *= -1;
	if(this->getPosition().y > _target->getPosition().y && yValue < 0)
		yValue *= -1;
	this->setPosition
	(
		this->getPosition().x+xValue,
		this->getPosition().y+yValue
	);
	angle = PI-(angle)+ (2*tempAngle);

	if(this->faction !=_target->faction)
	{
		lastAttackedUnit = _target;
		this->DealDamage(_target);
	}
}
void UnitObject::UnitDeleteDelegate(MyDelegate* _delegate)
{
	m_delegate = _delegate;
	m_delegate->DelegateMethod2(this);
}

UnitObject* UnitObject::CreateUnitWithType(int _type,float _hp, Vec2 _pos)
{
	switch(_type)
	{
	case UNIT_TYPE_PLAYER:
		return Player::CreateUnit(_hp,_pos);
	case UNIT_TYPE_ENEMY:
		return Enemy::CreateUnit(_hp,_pos);
	case UNIT_TYPE_NINJA:
		return Ninja::CreateUnit(_hp,_pos);
	case UNIT_TYPE_MONK:
		return Monk::CreateUnit(_hp,_pos);
	default :
		return NULL;
	}
}