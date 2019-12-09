#include "DamageFont.h"

using namespace cocos2d;

DamageFont* DamageFont::create(float value, Vec2 pos,Color4B color)
{ 
    DamageFont *pRet = new(std::nothrow) DamageFont(); 
	pRet->damageValue = value;
	pRet->pos = pos;
	pRet->color = color;
    if (pRet && pRet->init()) 
    { 
        pRet->autorelease(); 
        return pRet; 
    } 
    else 
    { 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    } 
}
DamageFont::~DamageFont()
{
	log("FontDelete");
}
bool DamageFont::init()
{
	if(!Layer::init())
		return false;
	if(damageValue < 1)
		damageValue = 1;

	std::string damageFont;
	damageFont = StringUtils::format("-%.0f",damageValue);
	auto damageLabel = Label::create(damageFont.c_str(),"",32);
	damageLabel->setTextColor(color);
	damageLabel->setPosition(Vec2(pos.x,pos.y+100));
	this->addChild(damageLabel);

	Vector<FiniteTimeAction*> actions;
	actions.pushBack(FadeTo::create(1,0));
	actions.pushBack(DelayTime::create(1.0f));
	actions.pushBack(CallFunc::create([=]()->void
	{
		this->removeFromParent();
	}
	));
	auto sequence = Sequence::create(actions);
	damageLabel->runAction(sequence);

	return true;
}