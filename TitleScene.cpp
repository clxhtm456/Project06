#include "TitleScene.h"
#include "SelectScene.h"

Scene* TitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TitleScene::create();

	scene->addChild(layer);
	return scene;
}
bool TitleScene::init()
{
	if(!Layer::init())
		return false;

	auto Winsize = Director::getInstance()->getWinSize();

	
	auto bgSprite = Sprite::create("Image/TitleScene/TitleBG.png");
	bgSprite->setAnchorPoint(Vec2(0,0));
	this->addChild(bgSprite,0);

	auto startItem = MenuItemImage::create(
                                        "Image/Common/PlayButton.png",
                                        "Image/Common/PlayButtonPressed.png",
                                        CC_CALLBACK_0(TitleScene::StartSelectSceneButton,this));
	startItem->setPosition(970,500);
	
	auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(TitleScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto menu = Menu::create(startItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	return true;
}
void TitleScene::StartSelectSceneButton()
{
	Director::getInstance()->pushScene(SelectScene::createScene());
}
void TitleScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK)
    {
        // IMPLEMENT YOUR BACK BUTTON LOGIN HERE
		StartSelectSceneButton();
    }
}