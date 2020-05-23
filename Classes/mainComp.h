//
//  mainComp.h
//  drums4
//
//  Created by Kalle Palomäki on 17/08/15.
//
//
#include <iostream>
#ifndef drums4_mainComp_h
#define drums4_mainComp_h

/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */


//#include "/Users/kpalomak/juce_dynlib/JuceLibraryCode/JuceHeader.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "envelope.h"

//#include "../JuceLibraryCode/JuceHeader.h"
//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */

class MainContentComponent   : public AudioAppComponent
{
public:
    MainContentComponent();
    ~MainContentComponent();

    void ini();
    bool flagOn;
    bool touchBegun=false;
    bool touchEnded=false;
    void shut();
    int timeSampleIdx;
    double freqSin=500;
    double envGain=0.8;
    double depth;
    void prepareToPlay (int , double) override;
    void releaseResources() override;
    void getNextAudioBlock (const AudioSourceChannelInfo& ) override;
    
    Random random;
private:
    int tap=100000;
    double  *filterMemory;
    envelope sawEnvelope;
    
//    double filterMemory[tap];
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
 //   CREATE_FUNC(MainContentComponent);
};
        
        // Component* createMainContentComponent()     { return new MainContentComponent(); }
        
        
#endif  // MAINCOMPONENT_H_INCLUDED

