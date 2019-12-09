#include "GameClearPopup.h"
#include "MainGameScene.h"
#include "SelectScene.h"

bool GameClearPopup::init()
{
    auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	auto fadeBack = LayerColor::create(Color4B(0, 0, 0, 0), winSize.width, winSize.height);

    this->addChild(fadeBack);
	 
    fadeBack->runAction(FadeTo::create(0.5f, 150));
	std::stringstream ss;
	ss<<"GAME CLEAR";
	auto gameClear = Label::create(ss.str().c_str(),"",50);

    gameClear->setPosition(Point(winSize.width / 2, winSize.height / 2));

    this->addChild(gameClear);

	if(Director::getInstance()->getRunningScene())
		Director::getInstance()->getRunningScene()->addChild(this);

    return true;
}

 

void GameClearPopup::onEnter()
{
    Layer::onEnter();
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
}

bool GameClearPopup::onTouchBegan(Touch* touch, Event* event)
{
	std::string stageData;
	stageData = StringUtils::format("stage%d",MainGameScene::GetStageCount()+1);
	UserDefault::getInstance()->setBoolForKey(stageData.c_str(),true);//클리어상태
	GoSelectScene();
    return true;
}
void GameClearPopup::GoSelectScene()
{
	auto nextscene = MainGameScene::createScene(MainGameScene::GetSelectStageScene(),MainGameScene::GetStageCount()+1);
	Director::getInstance()->replaceScene(nextscene);
}