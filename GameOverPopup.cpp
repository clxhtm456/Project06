#include "GameOverPopup.h"
#include "MainGameScene.h"

GameOverPopup* GameOverPopup::create(int option)
{ 
    GameOverPopup *pRet = new(std::nothrow) GameOverPopup(); 
	if(option != -1)
		pRet->gameoverOption = option;
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

bool GameOverPopup::init()
{
    auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	auto fadeBack = LayerColor::create(Color4B(0, 0, 0, 0), winSize.width, winSize.height);

    this->addChild(fadeBack);

    fadeBack->runAction(FadeTo::create(0.5f, 200));
	Sprite* gameover;
	if(gameoverOption%2 == 0)
		gameover = Sprite::create("Image/MainScene/Gameover_text1.png");//oops
	else
		gameover = Sprite::create("Image/MainScene/Gameover_text2.png");//tryagain

    gameover->setPosition(Point(winSize.width / 2, winSize.height / 2+200));

    this->addChild(gameover);

	auto retryButton = MenuItemImage::create(
                                        "Image/MainScene/Retrybutton.png",
                                        "Image/MainScene/Retrybutton_Pressed.png",
										CC_CALLBACK_0(GameOverPopup::RestartScene,this));
	retryButton->setPosition(Vec2(winSize.width / 2, winSize.height / 2-100));

	auto menu = Menu::create(retryButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	if(Director::getInstance()->getRunningScene())
		Director::getInstance()->getRunningScene()->addChild(this);

    return true;
}

 

void GameOverPopup::onEnter()
{
    Layer::onEnter();
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
}

bool GameOverPopup::onTouchBegan(Touch* touch, Event* event)
{
	RestartScene();
    return true;
}
void GameOverPopup::RestartScene()
{
	auto scene = MainGameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}