#include "SelectScene.h"
#include "MainGameScene.h"
#include "Player.h"
#include "Enemy.h"

Scene* SelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectScene::create();

	scene->addChild(layer);
	return scene;
}
bool SelectScene::init()
{
	if(!Layer::init())
		return false;
	StageSceneLoading();
	auto Winsize = Director::getInstance()->getWinSize();

	
	auto bgSprite = Sprite::create("Image/LevelSelectScene/SelectBG.png");
	bgSprite->setAnchorPoint(Vec2(0,0));
	this->addChild(bgSprite,0);

	auto selectLabel = Sprite::create("Image/LevelSelectScene/LevelSelect_text.png");
	selectLabel->setAnchorPoint(Vec2(0,1));
	selectLabel->setPosition(+60,Winsize.height-60);
	this->addChild(selectLabel,0);

	MenuItemImage* startItem[10];
	Menu* menu = Menu::create();
	bool temp = UserDefault::getInstance()->getBoolForKey("stage1");
	for(int i = 0; i < 10; i++)
	{
		std::string stageData;
		stageData = StringUtils::format("stage%d",i+1);
		std::string stageButton;
		if(UserDefault::getInstance()->getBoolForKey(stageData.c_str()))//클리어상태
			stageButton = StringUtils::format("Image/LevelSelectScene/StageButton%d_Clear.png",i+1);
		else
			stageButton = StringUtils::format("Image/LevelSelectScene/StageButton%d.png",i+1);
		std::string stageButtonPressed;
		stageButtonPressed = StringUtils::format("Image/LevelSelectScene/StageButton%d_pressed.png",i+1);
		startItem[i] = MenuItemImage::create(
			stageButton,
			stageButtonPressed,
			CC_CALLBACK_0(SelectScene::StartMainSceneButton,this,i));

		startItem[i]->setPosition(100+200*((i+2)%6),570-200*(i<4?0:1));
		menu->addChild(startItem[i]);
	}

	auto menuItem = MenuItemImage::create(
		"Image/LevelSelectScene/MenuButton_Pressed.png",
		"Image/LevelSelectScene/MenuButton.png",
		CC_CALLBACK_0(SelectScene::MenuButton,this));
	menuItem->setAnchorPoint(Vec2(0,0));
	menuItem->setPosition(20,20);
	menu->addChild(menuItem);

    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	
	auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(SelectScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}
void SelectScene::StartMainSceneButton(int _num)
{
	if(_num < 0)
		_num = 0;
	auto mainGame = MainGameScene::createScene(this,_num);
	Director::getInstance()->replaceScene(mainGame);
}
void SelectScene::MenuButton()
{
	Director::getInstance()->popScene();
}
void SelectScene::StageSceneLoading()
{
}

void SelectScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK)
    {
        // IMPLEMENT YOUR BACK BUTTON LOGIN HERE
		Director::getInstance()->end();
    }
}