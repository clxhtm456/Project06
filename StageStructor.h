#pragma once

#include "cocos2d.h"

using namespace cocos2d;
struct StageUnit
{
	StageUnit(int typeVar, int hpVar,Vec2 posVar)
	{
		type = typeVar;
		hp = hpVar;
		pos = posVar;
	}
	int type;
	int hp;
	Vec2 pos;
};
struct Stage
{
	Stage(StageUnit* list,...)
	{
		unitList.push_back(list);
		va_list ap;
		va_start(ap,list);
		StageUnit* temp;
		while(1)
		{
			auto temp =  va_arg(ap,StageUnit*);
			if(temp == nullptr)
				break;
			unitList.push_back(temp);
		}
		va_end(ap);
	}
	std::vector<StageUnit*> unitList;
};
class StageStructor : public Layer
{
private:

public :
	std::vector<Stage*> stageVector;
	CREATE_FUNC(StageStructor);
	bool init();
};

Stage* stageList[10] = 
{
	new Stage(
	new StageUnit(0,200,Vec2(300,360)),
	new StageUnit(1,200,Vec2(1000,360)),
	nullptr
	),
	new Stage(
	new StageUnit(0,200,Vec2(300,360)),
	new StageUnit(1,120,Vec2(1000,200)),
	new StageUnit(1,120,Vec2(1000,500)),
	nullptr
	),
	new Stage(
	new StageUnit(0,50,Vec2(200,520)),
	new StageUnit(0,50,Vec2(200,200)),
	new StageUnit(1,50,Vec2(1080,520)),
	new StageUnit(1,50,Vec2(1080,200)),
	nullptr
	),new Stage(
	new StageUnit(0,120,Vec2(400,200)),
	new StageUnit(0,120,Vec2(1000,200)),
	new StageUnit(1,120,Vec2(1100,520)),
	new StageUnit(1,120,Vec2(200,520)),
	new StageUnit(1,80,Vec2(700,400)),
	nullptr
	),
	new Stage(
	new StageUnit(0,200,Vec2(640,360)),
	new StageUnit(1,100,Vec2(200,520)),
	new StageUnit(1,100,Vec2(200,200)),
	new StageUnit(1,100,Vec2(1080,520)),
	new StageUnit(1,100,Vec2(1080,200)),
	nullptr
	),new Stage(
	new StageUnit(0,100,Vec2(400,200)),
	new StageUnit(0,100,Vec2(1000,200)),
	new StageUnit(3,200,Vec2(640,360)),
	new StageUnit(1,80,Vec2(200,520)),
	new StageUnit(1,80,Vec2(1080,520)),
	new StageUnit(1,80,Vec2(1080,400)),
	nullptr
	),new Stage(
	new StageUnit(0,30,Vec2(400,200)),
	new StageUnit(0,30,Vec2(1000,200)),
	new StageUnit(1,30,Vec2(640,360)),
	new StageUnit(1,30,Vec2(200,520)),
	new StageUnit(1,30,Vec2(1080,520)),
	new StageUnit(1,30,Vec2(1080,400)),
	nullptr
	),new Stage(
	new StageUnit(1,200,Vec2(640,360)),
	new StageUnit(0,30,Vec2(200,520)),
	new StageUnit(0,30,Vec2(200,200)),
	new StageUnit(0,30,Vec2(1080,520)),
	new StageUnit(0,30,Vec2(1080,200)),
	nullptr
	),new Stage(
	new StageUnit(0,30,Vec2(300,160)),
	new StageUnit(0,30,Vec2(300,560)),
	new StageUnit(3,50,Vec2(640,360)),
	new StageUnit(1,30,Vec2(1000,50)),
	new StageUnit(1,30,Vec2(1000,230)),
	new StageUnit(1,30,Vec2(1000,410)),
	new StageUnit(1,30,Vec2(1000,590)),
	nullptr
	),new Stage(
	new StageUnit(3,200,Vec2(640,360)),
	new StageUnit(0,30,Vec2(200,520)),
	new StageUnit(0,30,Vec2(200,200)),
	new StageUnit(2,50,Vec2(1080,520)),
	new StageUnit(2,50,Vec2(1080,200)),
	nullptr
	)
};