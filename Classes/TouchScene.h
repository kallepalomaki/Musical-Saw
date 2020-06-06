//
//  TouchScene.h
//  drums
//
//  Created by Palomäki Kalle on 04/08/15.
//
//

#ifndef __drums__TouchScene__
#define __drums__TouchScene__

#include <stdio.h>
#include <string>

#pragma once
#include "mainComp.h"
#include "cocos2d.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "../JuceLibraryCode/JuceHeader.h"
using namespace std;

class TouchScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(bool, int);
    virtual bool init();
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    virtual void onEnter();
    virtual void update(float);
    CREATE_FUNC(TouchScene);
    void playSounds(char *);
    void playTutorial();
    void animateSaha();
    void test_thread();
    float posToFreq(float);
    float posToEnvGain(float);
    float posToVibDepth(float);
    static void setRunTutorial(bool);
    string pickRecording();
    void transitionToMenuScene();
    void menuButtonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    void buttonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    int setTutorialActive(bool);
    MainContentComponent testi2;
private:
    cocos2d::Label* labelTouchInfo;
    cocos2d::Sprite *saw_player, *temp;
    cocos2d::Sprite *switch_on_off1,*switch_on_off2;
    cocos2d::Animate* animate;
    bool flagMusicPlaying=false;
    bool tutorial_active=false;
    bool flag_show_touch=false;
    bool bg_music=true;
    float scale2=0.9; // was 0.9
    float scale =1.0; // was 1
    float backGroundVolume=0.05f;
    bool m_was_here=false;
    static bool m_run_tutorial;
    static int m_prev_scene;
    //static bool wait_scene_trans;
};
#endif /* defined(__drums__TouchScene__) */
