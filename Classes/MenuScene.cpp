//
//  MenuScene.cpp
//  saw
//
//  Created by Kalle Palomäki on 28.5.2020.
//

#include "MenuScene.h"
#include "TouchScene.h"
#include <iostream>

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void MenuScene::buttonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType) {
    if (cocos2d::ui::Widget::TouchEventType::BEGAN == eventType) {
        run_tutorial=true;
    }
}

void MenuScene::menuButtonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType) {
    if (cocos2d::ui::Widget::TouchEventType::BEGAN == eventType) {
        run_tutorial=true;
    }
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
        
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("green_background_only.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale(1.0);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    
    ui::Button* btn = ui::Button::create("saha_tutorial_button.png");
    auto hideShow = Sequence::create(Hide::create(), DelayTime::create(1), Show::create(),NULL);
    btn->runAction(hideShow);
    btn->setPosition(Vec2(4*visibleSize.width/5 + origin.x, visibleSize.height/4 + origin.y));
    btn->addTouchEventListener(CC_CALLBACK_2(MenuScene::buttonPressed, this) );
    btn->setScale(0.5);
    this->addChild(btn);
    
    auto funcCallAction = CallFunc::create([=](){
        transitionToGameScene();
    });
    
    auto action = Sequence::create(DelayTime::create(3), funcCallAction, NULL);

    this->runAction(action);
    //the code mean that the layer "HelloWorld" run an action which wait 2 second and then call the function "transitionToGameScene".
    return true;
}

void MenuScene::transitionToGameScene() {
    auto director = Director::getInstance();
    
    auto scene2 = TouchScene::createScene(run_tutorial);
    // TouchScene::setRunTutorial();
    director->replaceScene(scene2);
}
