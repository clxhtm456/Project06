#include "MainGameScene.h"
#include "Player.h"
#include "UnitObject.h"
#include "Enemy.h"
#include "StageStructor.h"
#include "GameOverPopup.h"
#include "PausePopup.h"
#include "SelectScene.h"
#include "GameManager.h"

using namespace cocos2d;

Node* MainGameScene::_selectStageScene = 0;
int MainGameScene::_stageCount = 0;

Scene* MainGameScene::createScene(Node* selectStageScene ,int stageCount)
{
	_selectStageScene = selectStageScene;
	_stageCount = stageCount;
	if(_stageCount >= MAXLEVEL)
		_stageCount = MAXLEVEL-1;

	auto scene = Scene::create();
	auto layer = MainGameScene::create();

	scene->addChild(layer);
	return scene;
}
Scene* MainGameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainGameScene::create();

	scene->addChild(layer);
	return scene;
}
bool MainGameScene::init()
{
	if(!Layer::init())
		return false;
	gameManager = GameManager::create();
	this->addChild(gameManager,1);
	GameSetting();
	StageBuilding();
	GamePaused(true);
	return true;
}
void MainGameScene::GameSetting()
{
	auto Winsize = Director::getInstance()->getWinSize();
	fadeBack = LayerColor::create(Color4B(0, 0, 0, 0), Winsize.width, Winsize.height);

    this->addChild(fadeBack,3);

	fadeBack->setOpacity(150);
	auto ready = Sprite::create("Image/MainScene/Ready_text.png");

    ready->setPosition(Point(Winsize.width / 2, Winsize.height / 2));
	fadeBack->addChild(ready);

	auto bgSprite = Sprite::create("Image/Common/GameBG.png");
	bgSprite->setAnchorPoint(Vec2(0,0));
	this->addChild(bgSprite,0);


	auto startItem = MenuItemImage::create(
                                        "Image/MainScene/Backbutton.png",
                                        "Image/MainScene/BackbuttonPressed.png",
                                        CC_CALLBACK_0(MainGameScene::RetryScene,this));
	startItem->setAnchorPoint(Vec2(1,1));
	startItem->setPosition(Vec2(Winsize.width-120,Winsize.height-20));

	auto homeItem = MenuItemImage::create(
                                        "Image/MainScene/Homebutton.png",
                                        "Image/MainScene/HomebuttonPressed.png",
                                        CC_CALLBACK_0(MainGameScene::ReturnHomeScene,this));
	homeItem->setAnchorPoint(Vec2(1,1));
	homeItem->setPosition(Vec2(Winsize.width-20,Winsize.height-20));

	auto pauseItem = MenuItemImage::create(
                                        "Image/MainScene/Pausebutton.png",
                                        "Image/MainScene/PausebuttonPressed.png",
										[=](cocos2d::Ref *pSender)->void
	{
		MainGameScene::GamePaused(true);
		PausePopup::create();
	});
	pauseItem->setAnchorPoint(Vec2(0,1));
	pauseItem->setPosition(Vec2(20,Winsize.height-20));

	

	menu = Menu::create(startItem,homeItem,pauseItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);

	std::stringstream ss;
	ss<<"LEVEL "<<_stageCount+1;
	auto levelLabel = Label::create(ss.str().c_str(),"",30);
	levelLabel->setAnchorPoint(Point(0,1));
	levelLabel->setPosition(Vec2(120,Winsize.height-20));
	this -> addChild(levelLabel,2);
	
	auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(MainGameScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
void MainGameScene::StageBuilding()
{
	Stage* stage = nullptr;
	stage = stageList[_stageCount];
	int size = stage->unitList.size();
	for(int i = 0; i < size;i++)
	{
		auto unit = UnitObject::CreateUnitWithType(
			stage->unitList[i]->type,
			stage->unitList[i]->hp,
			stage->unitList[i]->pos);

		gameManager->addChild(unit);
		unit->UnitDeleteDelegate(gameManager);
	}
}
void MainGameScene::GameOver()
{
	this->addChild(GameOverPopup::create());
}
void MainGameScene::onEnter()
{
    Layer::onEnter();
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
}
bool MainGameScene::onTouchBegan(Touch* touch, Event* event)
{
	if(fadeBack!= nullptr)
	{
		fadeBack->removeFromParent();
		fadeBack= nullptr;
	}
	GamePaused(false);
    return true;
}
void MainGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK)
    {
        // IMPLEMENT YOUR BACK BUTTON LOGIN HERE
		ReturnHomeScene();
    }
}

void MainGameScene::RetryScene()
{
	auto scene = MainGameScene::createScene(_selectStageScene,_stageCount);
	Director::getInstance()->replaceScene(scene);
}
void MainGameScene::ReturnHomeScene()
{
	auto selectScene = SelectScene::createScene();
	Director::getInstance()->replaceScene(selectScene);
}
void MainGameScene::GamePaused(bool _var)
{
	gameManager->UnitAllPaused(_var);
	gamePaused = _var;
	if(_var)
	{
		menu->setEnabled(false);
	}else
	{
		menu->setEnabled(true);
	}
}

