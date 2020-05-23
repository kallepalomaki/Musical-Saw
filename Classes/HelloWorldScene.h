//
//  HelloWorldScene.h
//  drums
//
//  Created by Palomäki Kalle on 05/08/15.
//
//

#ifndef __drums__HelloWorldScene__
#define __drums__HelloWorldScene__

//#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
   // virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    void buttonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    void transitionToGameScene();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
    cocos2d::Label* labelTouchInfo;
    bool run_tutorial = false;

};

#endif //__drums__HelloWorldScene__
