#include "GameManager.h"
#include "GameOverPopup.h"
#include "GameClearPopup.h"

using namespace cocos2d;


bool GameManager::init()
{
	if(!Layer::init())
		return false;
	unitList.clear();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	this->scheduleUpdate();
	return true;
}

void GameManager::update(float delta)
{
	if(click)
	{
		//커서안에 속한 플레이어의 eating 을 true로
		for(auto itor = unitList.begin();itor!=unitList.end();++itor)
		{
			if((*itor)->faction == UNIT_TYPE_PLAYER)
			{
				auto interval = (*itor)->getPosition().distance(tempMouseCursor);
				auto rad = (*itor)->getRadius();
				lastSelectPlayer = dynamic_cast<Player*>((*itor));
				if(interval <= rad)
				{
					lastSelectPlayer->StartEating(true);
				}else 
				{
					lastSelectPlayer->StartEating(false);
				}
			}
		}
	}

	for(auto itor = unitList.begin();itor!=unitList.end();++itor)
	{
		auto itor2 = itor;
		for(++itor2;itor2!=unitList.end();++itor2)
		{
			if((*itor)->CheckCollision((*itor2)))
			{
				//충돌시
				(*itor)->KnockBack((*itor2));
				(*itor2)->KnockBack((*itor));
			}
		}
	}

}
void GameManager::UnitAllPaused(bool _var)
{
	for(auto itor = unitList.begin();itor!=unitList.end();++itor)
	{
		(*itor)->UnitActive(!_var);
	}
}
void GameManager::DelegateMethod1(UnitObject* target)
{
	auto playerCount= 0;
	auto nativeUnitCount = 0;
	for(auto itor = unitList.begin();itor!=unitList.end();++itor)
	{
		if((*itor) == target)
			continue;
		switch((*itor)->faction)
		{
		case UNIT_TYPE_PLAYER:
			playerCount++;
			break;
		case UNIT_TYPE_MONK:
			nativeUnitCount++;
			break;
		default:
			break;
		}
	}
	if(unitList.size()-1 - nativeUnitCount == playerCount)
	{
		//승리
		GameClearPopup::create();
		log("victory");
	}else if(playerCount <= 0)
	{
		//패배
		if(lastSelectPlayer!=NULL)
			GameOverPopup::create(0);
		else
			GameOverPopup::create(1);
		
		log("defeat");
	}
	this->EraseUnitList(target);
}
void GameManager::DelegateMethod2(UnitObject* target)
{
	this->AddUnitList(target);
}
void GameManager::AddUnitList(UnitObject* unit)
{
	this->unitList.push_back(unit);
}
bool GameManager::EraseUnitList(UnitObject* unit)
{
	for(auto itor = unitList.begin();itor!=unitList.end();++itor)
	{
		if((*itor) == unit)
		{
			unitList.erase(itor);
			log("deleteUnit");
			return true;
		}
	}
	return false;
}
bool GameManager::onTouchBegan(Touch* touch, Event* event)
{
	click = true;
	tempMouseCursor = touch->getLocation();
	
	//커서안에 속한 플레이어의 eating 을 true로
	for(auto itor = unitList.begin();itor!=unitList.end();++itor)
	{
		if((*itor)->faction == UNIT_TYPE_PLAYER)
		{
			auto interval = (*itor)->getPosition().distance(tempMouseCursor);
			auto rad = (*itor)->getRadius();
			if(interval <= rad)
			{
				try
				{
					lastSelectPlayer = dynamic_cast<Player*>((*itor));
					lastSelectPlayer->StartEating(true);
				}catch(std::exception& e)
				{
					return false;
				}
				break;
			}
		}
	}
	return true;
}

void GameManager::onTouchEnded(Touch* touch, Event* event)
{
	click = false;
	lastSelectPlayer = NULL;
	for(auto itor = unitList.begin();itor!=unitList.end();++itor)
	{
		if((*itor)->faction == UNIT_TYPE_PLAYER)
		{
			auto player = dynamic_cast<Player*>((*itor));
			if(player)
				player->StartEating(false);
		}
	}
}
void GameManager::onTouchMoved(Touch* touch, Event* event)
{
	tempMouseCursor = touch->getLocation();
}
bool GameManager::ReplaceUnitList(UnitObject* erase,UnitObject* add)
{
	for(auto itor = unitList.begin();itor!=unitList.end();++itor)
	{
		if((*itor) == erase)
		{
			unitList.erase(itor);
			AddUnitList(add);
			log("replaceUnit");
			return true;
		}
	}
	return false;
}
GameManager::~GameManager()
{
	removeAllChildren();
	log("~GameManager");
}