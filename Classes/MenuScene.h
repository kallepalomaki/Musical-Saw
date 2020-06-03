//
//  MenuScene.hpp
//  saw
//
//  Created by Kalle Palomäki on 28.5.2020.
//

#ifndef __drums__MenuScene__
#define __drums__MenuScene__

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
   // virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    void buttonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    void soundButtonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
    void attributionButtonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);

    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    void transitionToGameScene();
    void transitionToAttributionScene();

    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
private:
    cocos2d::Label* labelTouchInfo;
    cocos2d::Sprite* on_sprite;
    static bool run_tutorial;
    static int m_prev_scene;

};
#endif /* MenuScene_h */
