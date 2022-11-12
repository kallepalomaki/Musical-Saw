//
//  StartScene.h
//
//  Created by Palomäki Kalle on 05/08/15.
//
//

#ifndef __StartScene__
#define __StartScene__

//#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class StartScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
   // virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    void buttonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    void menuButtonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    void attributionButtonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    void transitionToGameScene();
    void transitionToMenuScene();
    void transitionToAttributionScene();


    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);
private:
    cocos2d::Label* labelTouchInfo;
    bool run_tutorial = false;
    int m_prev_scene = 0;

};

#endif //__StartScene__
