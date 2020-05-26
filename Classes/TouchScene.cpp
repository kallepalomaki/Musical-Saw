//
//  TouchScene.cpp
//  drums
//
//  Created by Palomäki Kalle on 04/08/15.
//
//

#include "TouchScene.h"
#include <iostream>
USING_NS_CC;

//bool m_run_tutorial=false;
//bool wait_scene_trans=false;

bool TouchScene::m_run_tutorial=false;
bool TouchScene::wait_scene_trans=false;

cocos2d::Scene* TouchScene::createScene(bool run_tutorial)
{
    auto scene = cocos2d::Scene::create();
    auto layer = TouchScene::create();
    scene->addChild(layer);
    //this->setRunTutorial(run_tutorial);
    m_run_tutorial=run_tutorial; // run_tutorial;
    //auto director = Director::getInstance();
    wait_scene_trans=true;
    return scene;
}

void TouchScene::onEnter()
{
    cocos2d::Layer::onEnter();
  //  m_run_tutorial=true;
    //if (m_run_tutorial==true) {
    //    playTutorial();
    //}
    //while(wait_scene_trans==false);
    if (m_run_tutorial) {
        playTutorial();
    }
    else {
        cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        ui::Button* btn = ui::Button::create("saha_tutorial_button.png");
        auto hideShow = Sequence::create(DelayTime::create(5), RemoveSelf::create(),NULL);
        btn->runAction(hideShow);
        btn->setPosition(Vec2(4*visibleSize.width/5 + origin.x, visibleSize.height/4 + origin.y));
        btn->addTouchEventListener(CC_CALLBACK_2(TouchScene::buttonPressed, this) );
        btn->setScale(0.5);
        this->addChild(btn);
    }

}


void TouchScene::update(float delta)
{
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    //audio->setBackgroundMusicVolume(0.001f);
    if (!audio->isBackgroundMusicPlaying()) {
        auto backGroundAudio= CocosDenshion::SimpleAudioEngine::getInstance();
        //backGroundAudio->setBackgroundMusicVolume(0.1f);
        backGroundAudio-> playBackgroundMusic("352051_kaki.mp3",false);
        backGroundAudio->setBackgroundMusicVolume(backGroundVolume);
        sleep(1.0f);
        printf("update\n");
    }
}


void TouchScene::buttonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType) {
    if (cocos2d::ui::Widget::TouchEventType::BEGAN == eventType) {
        playTutorial();
    }
}

void TouchScene::setRunTutorial(bool run_tutorial)
{
    m_run_tutorial=run_tutorial;
}
bool TouchScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Initialize touch listener
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(TouchScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TouchScene::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(TouchScene::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(TouchScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    // Add background image
    auto sprite = cocos2d::Sprite::create("saha_keskella_tausta_test.png");
//    auto sprite = cocos2d::Sprite::create("saha_tausta_test.png");

    sprite->setAnchorPoint(cocos2d::Vec2(0, 0));
    sprite->setPosition(20*scale2-330+30, 25*scale2-160); // 110 30remove last pluses
    sprite->setScale(scale*scale2);
    this->addChild(sprite, 0);
    
    saw_player = cocos2d::Sprite::create("saha_keskella_test2.png");
    saw_player->setAnchorPoint(cocos2d::Vec2(0, 0));
    saw_player->setPosition(20*scale2+30, 25*scale2-50); // 45 remove last plus
    saw_player->setScale(scale*scale2);
    this->addChild(saw_player, 0);
    testi2.ini();

    //while(m_run_tutorial==false);
    if (flag_show_touch) {
        temp = Sprite::create("red_dot.png");
            
            // position the sprite on the center of the screen
        temp->setPosition(100, 100);
        temp->setScale(0.5);
        // add the sprite as a child to this layer
        temp->setVisible(false);
        this->addChild(temp, 0);
    }
    
    auto backGroundAudio= CocosDenshion::SimpleAudioEngine::getInstance();
    //backGroundAudio->setBackgroundMusicVolume(0.1f);
    //backGroundAudio-> playBackgroundMusic("352051_kaki.mp3");
    //backGroundAudio->setBackgroundMusicVolume(backGroundVolume);
    //backGroundAudio->setBackgroundMusicVolume(UserDefault::getInstance()->getFloatForKey("musicVolume", 0.5f));
    this->scheduleUpdate();
    return true;
}

void TouchScene::playTutorial() {
    //std::chrono::seconds duration( 2 );
    if (tutorial_active==false) {
        tutorial_active=true;
        cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        // add "HelloWorld" splash screen"
        auto sprite = Sprite::create("saha_tutorial.png");
      
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        sprite->setScale(0.5);
        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
        auto scaleBy = ScaleBy::create(0.8,2.2);
        sprite->runAction(scaleBy);
        //auto remove_child = DelayTime::create(3);
        //sleep(10);
        //this->removeChild(sprite2, true);
        //animSpr->runAction(Sequence::create(animate, removeSelf, nullptr));
        auto action = Sequence::create(DelayTime::create(5), RemoveSelf::create(), NULL);
    
        sprite->runAction(action);
    
        auto sprite2 = Sprite::create("red_dot.png");

        auto action2 = Sequence::create(DelayTime::create(4), MoveBy::create(5,Vec2(250,0)), MoveBy::create(0,Vec2(-200,0)), DelayTime::create(4), MoveBy::create(3,Vec2(0,150)), DelayTime::create(4), RemoveSelf::create(), NULL);
        sprite2->runAction(action2);
        // position the sprite on the center of the screen
        sprite2->setPosition(Vec2(visibleSize.width/6 + origin.x, visibleSize.height/4 + origin.y));
        sprite2->setScale(0.5);
        // add the sprite as a child to this layer
        this->addChild(sprite2, 0);
    
        auto sprite3 = Sprite::create("saha_pitch.png");
        // add the sprite as a child to this layer
        auto action3 = Sequence::create(Hide::create(), DelayTime::create(4), Show::create(), DelayTime::create(6), RemoveSelf::create(), NULL);
        sprite3->runAction(action3);
        // position the sprite on the center of the screen
        sprite3->setPosition(Vec2(visibleSize.width/4 + origin.x, visibleSize.height/8 + origin.y));
        sprite3->setScale(1);
        this->addChild(sprite3, 0);
    
        auto sprite4 = Sprite::create("saha_vibrato.png");
    
        auto action4 = Sequence::create(Hide::create(), DelayTime::create(10), Show::create(), DelayTime::create(6), RemoveSelf::create(), NULL);
        sprite4->runAction(action4);
        // position the sprite on the center of the screen
        sprite4->setPosition(Vec2(visibleSize.width/6 + origin.x, visibleSize.height/2 + origin.y));
        sprite4->setScale(1);
        // add the sprite as a child to this layer
        this->addChild(sprite4, 0);
    
        auto sprite5 = Sprite::create("saha_ready_to_go.png");
    
        auto action5 = Sequence::create(Hide::create(), DelayTime::create(20), Show::create(), DelayTime::create(4), RemoveSelf::create(), NULL);
        sprite5->runAction(action5);
        // position the sprite on the center of the screen
        sprite5->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        sprite5->setScale(1);
        // add the sprite as a child to this layer
        this->addChild(sprite5, 0);
    
    }
}


void TouchScene::animateSaha(){
    saw_player->setAnchorPoint(Vec2(0, 0));
    saw_player->setPosition(20*scale2+30, 25*scale2-50);
    saw_player->setScale(scale*scale2);
    cocos2d::Size s = saw_player->getContentSize();
    //setTextureRect(Rect(0,0,s.width,s.height));
    // now lets animate the sprite we moved
    
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(10);
    animFrames.pushBack(cocos2d::SpriteFrame::create("saha_keskella_test1.png", cocos2d::Rect(0,0,s.width,s.height)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("saha_keskella_test2.png", cocos2d::Rect(0,0,s.width,s.height)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("saha_keskella_test3.png", cocos2d::Rect(0,0,s.width,s.height)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("saha_keskella_test4.png", cocos2d::Rect(0,0,s.width,s.height)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("saha_alhaalla_test2.png", cocos2d::Rect(0,0,s.width,s.height)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("saha_alhaalla_test.png", cocos2d::Rect(0,0,s.width,s.height)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("saha_alhaalla_test2.png", cocos2d::Rect(0,0,s.width,s.height)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("saha_keskella_test4.png", cocos2d::Rect(0,0,s.width,s.height)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("saha_keskella_test3.png", cocos2d::Rect(0,0,s.width,s.height)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("saha_keskella_test2.png", cocos2d::Rect(0,0,s.width,s.height)));
    // create the animation out of the frames
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.15f);
    //Animate*
    animate = Animate::create(animation);
    animate->setTag(10);
    
    saw_player->runAction(RepeatForever::create(animate));
}

bool TouchScene::onTouchBegan(Touch* touch, Event* event)
{
    TouchScene touched;
    testi2.touchBegun=true;
    
    testi2.freqSin=posToFreq(touch->getLocation().x);
    testi2.envGain=posToEnvGain(touch->getLocation().y);
    testi2.depth=posToVibDepth(touch->getLocation().y);

    animateSaha();

    //labelTouchInfo->setPosition(1000,1300);
    
    //char touchLocBody[] = "You Touched Here X: %f Y: %f";
    //char *touchLocStr = new char[strlen(touchLocBody)+20];
    
    //sprintf(touchLocStr,touchLocBody,touch->getLocation().x, touch->getLocation().y);
    if (flag_show_touch) {
        temp->setVisible(true);
        temp->setPosition(Vec2(touch->getLocation().x, touch->getLocation().y));
    }
    //labelTouchInfo->setString(touchLocStr);
    //temp->setPosition(Vec2(200,200));
    return true;
}

float TouchScene::posToFreq(float x)
{
    float a=0.0509,  b=105, f; //b was 115
    
    f=pow(2,((a*x+b)/12));
    //f=972; //dbg
    return f;
   
}

float TouchScene::posToEnvGain(float y) {
    float a=0.142,b=-40 ,f ;
    f=pow(10,(a*y+b)/20);
    //f=0.165462; //dbg
    return f;
}

float TouchScene::posToVibDepth(float y) {
    float f;
    f=0.0107*y;
    return f;
}

void TouchScene::onTouchEnded(Touch* touch, Event* event)
{
    testi2.touchEnded=true;
    saw_player->stopAllActions();
    if (flag_show_touch)
        temp->setVisible(false);

}

void TouchScene::onTouchMoved(Touch* touch, Event* event)
{
    testi2.freqSin=posToFreq(touch->getLocation().x);
    testi2.envGain=posToEnvGain(touch->getLocation().y);
    testi2.depth=posToVibDepth(touch->getLocation().y);
    //cocos2d::log("touch moved");
    if (flag_show_touch)
        temp->setPosition(Vec2(touch->getLocation().x, touch->getLocation().y));

}

void TouchScene::onTouchCancelled(Touch* touch, Event* event)
{
    //cocos2d::log("touch cancelled");
}

