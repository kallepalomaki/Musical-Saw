//
//  HelloWorldScene.cpp
//  drums
//
//  Created by Palomäki Kalle on 05/08/15.
//
//

#include "HelloWorldScene.h"
#include "TouchScene.h"
#include "MenuScene.h"
#include "AttributionScene.h"
#include <iostream>
//using namespace cocos2d::ui;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void HelloWorld::buttonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType) {
    if (cocos2d::ui::Widget::TouchEventType::BEGAN == eventType) {
        run_tutorial=true;
    }
}

void HelloWorld::menuButtonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType) {
    if (cocos2d::ui::Widget::TouchEventType::BEGAN == eventType) {
        transitionToMenuScene();
    }
}

void HelloWorld::attributionButtonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType) {
    if (cocos2d::ui::Widget::TouchEventType::BEGAN == eventType) {
        transitionToAttributionScene();
    }
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
    auto sprite2 = Sprite::create("saha_tekstit_otsikko.png");
    
    // position the sprite on the center of the screen
    sprite2->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite2->setScale(0.5);
    // add the sprite as a child to this layer
    this->addChild(sprite2, 0);
    auto scaleBy = Sequence::create(ScaleBy::create(0.6,2.4), ScaleBy::create(0.4,0.8), NULL);
    //auto scaleBy = ScaleBy::create(0.6,2.2);
    auto rotateBy2 = Sequence::create(RotateBy::create(0.2, -30.0),RotateBy::create(0.2, 30.0),NULL);
    sprite2->runAction(scaleBy);
    sprite2->runAction(rotateBy2);
    
    ui::Button* btn = ui::Button::create("saha_tutorial_button.png");
    auto hideShow = Sequence::create(Hide::create(), DelayTime::create(1), Show::create(),NULL);
    btn->runAction(hideShow);
    btn->setPosition(Vec2(4*visibleSize.width/5 + origin.x, visibleSize.height/4 + origin.y));
    btn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::buttonPressed, this) );
    btn->setScale(0.5);
    this->addChild(btn);
    
    ui::Button* btn2 = ui::Button::create("hammasratas.png");
    auto hideShow2 = Sequence::create(Hide::create(), DelayTime::create(1), Show::create(),NULL);
    btn2->runAction(hideShow2);
    btn2->setPosition(Vec2(4*visibleSize.width/5 + origin.x, 3*visibleSize.height/4 + origin.y));
    btn2->addTouchEventListener(CC_CALLBACK_2(HelloWorld::menuButtonPressed, this) );
    btn2->setScale(0.5);
    this->addChild(btn2);
    
    ui::Button* btn3 = ui::Button::create("hammasratas.jpg");
    auto hideShow3 = Sequence::create(Hide::create(), DelayTime::create(1), Show::create(),NULL);
    btn3->runAction(hideShow3);
    btn3->setPosition(Vec2(4*visibleSize.width/5 + origin.x, 2*visibleSize.height/4 + origin.y));
    btn3->addTouchEventListener(CC_CALLBACK_2(HelloWorld::attributionButtonPressed, this) );
    btn3->setScale(0.5);
    this->addChild(btn3);
    
    auto funcCallAction = CallFunc::create([=](){
        transitionToGameScene();
    });
    
    //auto manuCallAction = CallFunc::create([=](){
    //});
    
    auto action = Sequence::create(DelayTime::create(3), funcCallAction, NULL);

    this->runAction(action);
    //the code mean that the layer "HelloWorld" run an action which wait 2 second and then call the function "transitionToGameScene".
    return true;
}

void HelloWorld::transitionToGameScene() {
    auto director = Director::getInstance();
    
    auto scene2 = TouchScene::createScene(run_tutorial);
    // TouchScene::setRunTutorial();
    director->replaceScene(scene2);
}

void HelloWorld::transitionToMenuScene() {
    auto director = Director::getInstance();
    
    auto scene2 = MenuScene::createScene();
    // TouchScene::setRunTutorial();
    //director->replaceScene(scene2);
    director->pushScene(scene2);
}

void HelloWorld::transitionToAttributionScene() {
    auto director = Director::getInstance();
    
    auto scene2 = AttributionScene::createScene();
    // TouchScene::setRunTutorial();
    //director->replaceScene(scene2);
    director->pushScene(scene2);
}
