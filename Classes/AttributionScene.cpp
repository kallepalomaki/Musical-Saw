//
//  AttributionScene.cpp
//  saw
//
//  Created by Kalle Palomäki on 31.5.2020.
//

#include <stdio.h>
#include <iostream>
#include "AttributionScene.h"
#include "MenuScene.h"
#include "TouchScene.h"

USING_NS_CC;
// prev_scene 0 StartScene, 1 TouchScene, 2 MenuScene, 3 Attribution Scene
int AttributionScene::m_prev_scene = 3;

Scene* AttributionScene::createScene(int prev_scene)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    m_prev_scene=prev_scene;
    // 'layer' is an autorelease object
    auto layer = AttributionScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void AttributionScene::buttonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType) {
    if (cocos2d::ui::Widget::TouchEventType::BEGAN == eventType) {
        if (m_prev_scene==0)
            transitionToGameScene();
        else
            transitionToMenuScene();
    }
}

// on "init" you need to initialize your instance
bool AttributionScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    ui::Button* btn;
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    
    auto sprite = Sprite::create("blue_background_only.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale(1.0);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    auto sprite2 = Sprite::create("attribution.png");
      
    // position the sprite on the center of the screen
    sprite2->setPosition(Vec2(2*visibleSize.width/5 + origin.x, visibleSize.height/2 + origin.y));
    sprite2->setScale(0.95);
    // add the sprite as a child to this layer
    this->addChild(sprite2, 0);

    if (m_prev_scene==0)
        btn = ui::Button::create("saha_go.png");
    else
        btn = ui::Button::create("saha_back.png");

    btn->setPosition(Vec2(4*visibleSize.width/5 + origin.x, visibleSize.height/4 + origin.y));
    btn->addTouchEventListener(CC_CALLBACK_2(AttributionScene::buttonPressed, this) );
    btn->setScale(0.5);
    this->addChild(btn);
    
    return true;
}

void AttributionScene::transitionToMenuScene() {
    auto director = Director::getInstance();
    // prev_scene 0 StartScene, 1 TouchScene, 2 MenuScene, 3 Attribution Scene
    int prev_scene=3;
    auto scene2 = MenuScene::createScene(prev_scene);
    director->replaceScene(scene2);
}

void AttributionScene::transitionToGameScene() {
    auto director = Director::getInstance();
    // prev_scene 0 StartScene, 1 TouchScene, 2 MenuScene, 3 Attribution Scene
    int prev_scene=3;
    run_tutorial=false;
    auto scene2 = TouchScene::createScene(run_tutorial, prev_scene);
    director->replaceScene(scene2);
}
