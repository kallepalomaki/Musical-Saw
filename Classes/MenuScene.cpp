//
//  MenuScene.cpp
//  saw
//
//  Created by Kalle Palomäki on 28.5.2020.
//

#include "MenuScene.h"
#include "TouchScene.h"
#include <CCUserDefault.h>
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
        transitionToGameScene();
    }
}

void MenuScene::soundButtonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType) {
    if (cocos2d::ui::Widget::TouchEventType::BEGAN == eventType) {
        auto userdefaults = cocos2d::UserDefault::getInstance();
        
        auto bg_music_off=userdefaults->getBoolForKey("bg_music_off");
        
        if (bg_music_off){ userdefaults->setBoolForKey("bg_music_off",false);
            on_sprite->setTexture("On.png");
        }
        else {
            userdefaults->setBoolForKey("bg_music_off",true);
            on_sprite->setTexture("Off.png");
        }
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
    
    ui::Button* btn2= ui::Button::create("hammasratas.jpg");
    //auto hideShow = Sequence::create(Hide::create(), DelayTime::create(1), Show::create(),NULL);
    //btn2->runAction(hideShow);
    btn2->setPosition(Vec2(4*visibleSize.width/5 + origin.x, 3*visibleSize.height/4 + origin.y));
    btn2->addTouchEventListener(CC_CALLBACK_2(MenuScene::soundButtonPressed, this) );
    btn2->setScale(0.5);
    this->addChild(btn2);
    
    auto funcCallAction = CallFunc::create([=](){
        transitionToGameScene();
    });
    
    //auto action = Sequence::create(DelayTime::create(3), funcCallAction, NULL);

    //this->runAction(action);
    //the code mean that the layer "HelloWorld" run an action which wait 2 second and then call the function "transitionToGameScene".
    
    // add "HelloWorld" splash screen"
    on_sprite = Sprite::create("On.png");
    
    // position the sprite on the center of the screen
    on_sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    on_sprite->setScale(1.0);
    // add the sprite as a child to this layer
    this->addChild(on_sprite, 0);
    
    return true;
}

void MenuScene::transitionToGameScene() {
    auto director = Director::getInstance();
    
    auto scene2 = TouchScene::createScene(false);
    // TouchScene::setRunTutorial();
    director->replaceScene(scene2);
}
