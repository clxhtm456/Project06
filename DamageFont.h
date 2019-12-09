#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class DamageFont : public Layer
{
private :
	float damageValue;
	Vec2 pos;
	Color4B color;
public:
	static DamageFont* create(float value,Vec2 pos, Color4B color = Color4B::RED);
	bool init();
	~DamageFont();
};