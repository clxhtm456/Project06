#include "PausePopup.h"

PausePopup* PausePopup::create(Node* listener, SEL_CallFunc selector)
{ 
	
    PausePopup *pRet = new(std::nothrow) PausePopup();
	if(listener != nullptr && selector != NULL)
	{
		pRet->_listener = listener;
		pRet->_selector = selector;
	}
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

bool PausePopup::init()
{
    auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	auto fadeBack = LayerColor::create(Color4B(0, 0, 0, 0), winSize.width, winSize.height);

    this->addChild(fadeBack);

    fadeBack->runAction(FadeTo::create(0.5f, 150));
	auto pauseText = Sprite::create("Image/MainScene/Pausetext.png");//oops

    pauseText->setPosition(Point(winSize.width / 2, winSize.height / 2));

    this->addChild(pauseText);

	if(Director::getInstance()->getRunningScene())
		Director::getInstance()->getRunningScene()->addChild(this);

    return true;
}

 

void PausePopup::onEnter()
{
    Layer::onEnter();
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
}

bool PausePopup::onTouchBegan(Touch* touch, Event* event)
{
	/*if (_listener != nullptr && _selector != NULL)
		(_listener->*_selector)();*/
	this->removeFromParent();
    return true;
}