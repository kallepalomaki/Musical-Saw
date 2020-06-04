//
//  MenuScene.cpp
//  saw
//
//  Created by Kalle Palomäki on 28.5.2020.
//

#include "MenuScene.h"
#include "AttributionScene.h"
#include "TouchScene.h"
#include <CCUserDefault.h>
#include <iostream>

USING_NS_CC;
bool run_tutorial = false;
int MenuScene::m_prev_scene = 1;

Scene* MenuScene::createScene(int prev_scene)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();
    
    m_prev_scene=prev_scene;
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

void MenuScene::soundButtonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType, ui::Button* btn2) {
    if (cocos2d::ui::Widget::TouchEventType::BEGAN == eventType) {
        auto userdefaults = cocos2d::UserDefault::getInstance();
        
        auto bg_music_off=userdefaults->getBoolForKey("bg_music_off");
        
        if (bg_music_off){ userdefaults->setBoolForKey("bg_music_off",false);
            btn2->loadTextureNormal("mustarastas.png");
        }
        else {
            userdefaults->setBoolForKey("bg_music_off",true);
            auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
            if (audio->isBackgroundMusicPlaying()) {
                printf("trying to stop background\n");
                audio->stopBackgroundMusic();
                //delete audio;
            }
            btn2->loadTextureNormal("mustarastas_nokka_kiinni.png");
        }
    }
}

void MenuScene::attributionButtonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType) {
    if (cocos2d::ui::Widget::TouchEventType::BEGAN == eventType) {
        transitionToAttributionScene();
    }
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    ui::Button* btn2;
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
        
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("green_background_only.png");
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale(1.0);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    
    ui::Button* btn = ui::Button::create("saha_go.png");
    btn->setPosition(Vec2(4*visibleSize.width/5 + origin.x, visibleSize.height/4 + origin.y));
    btn->addTouchEventListener(CC_CALLBACK_2(MenuScene::buttonPressed, this) );
    btn->setScale(0.5);
    this->addChild(btn);
  
    auto userdefaults = cocos2d::UserDefault::getInstance();

    auto bg_music=not(userdefaults->getBoolForKey("bg_music_off"));
    if (bg_music)
        btn2 = ui::Button::create("mustarastas.png");
    else
        btn2 = ui::Button::create("mustarastas_nokka_kiinni.png");
    
    btn2->setPosition(Vec2(4*visibleSize.width/5 + origin.x, 3*visibleSize.height/4 + origin.y));
    btn2->addTouchEventListener(CC_CALLBACK_2(MenuScene::soundButtonPressed, this, btn2) );
    btn2->setScale(0.25);
    this->addChild(btn2);

    ui::Button* btn3= ui::Button::create("saha_attribution_button.png");
    btn3->setPosition(Vec2(4*visibleSize.width/5 + origin.x, 2*visibleSize.height/4 + origin.y));
    btn3->addTouchEventListener(CC_CALLBACK_2(MenuScene::attributionButtonPressed, this) );
    btn3->setScale(0.5);
    this->addChild(btn3);
    
    //auto funcCallAction = CallFunc::create([=](){
    //    transitionToGameScene();
    //});
    
    return true;
}

void MenuScene::transitionToGameScene() {
    auto director = Director::getInstance();
    
    if (m_prev_scene==0)
    {
        auto scene2 = TouchScene::createScene(false);
        director->replaceScene(scene2);
    }
    else
        director->popScene();
}

void MenuScene::transitionToAttributionScene() {
    auto director = Director::getInstance();
    int prev_scene=2;
    auto scene2 = AttributionScene::createScene(prev_scene);
    director->replaceScene(scene2);
}
