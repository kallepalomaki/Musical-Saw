/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

//#include "/Users/kpalomak/juce_dynlib/JuceLibraryCode/JuceHeader.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>
#include "mainComp.h"
//#include "../JuceLibraryCode/JuceHeader.h"
//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */

void MainContentComponent::ini()
{
   // setSize (800, 600);
    setAudioChannels (0, 2); // no inputs, two outputs
    AudioDeviceManager::AudioDeviceSetup deviceSetUp = AudioDeviceManager::AudioDeviceSetup();;
    //AudioSourcePlayer::AudioSourcePlayer deviceSetUp;
    deviceSetUp.bufferSize=256;
    
    deviceSetUp.sampleRate=22050;
    filterMemory = new double[tap];
    int i;
    for (i=0;i<tap;i++){
        filterMemory[i]=0;
    }
}

void MainContentComponent::shut()
{
    shutdownAudio();
}

//class MainContentComponent   : public AudioAppComponent
//{
//public:
MainContentComponent::MainContentComponent()
    {
        timeSampleIdx=0;
    }
    
MainContentComponent::~MainContentComponent()
    {
        shutdownAudio();
    }
    
    
    
void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
    {
        String message;
        message << "Preparing to play audio...\n";
        message << " samplesPerBlockExpected = " << samplesPerBlockExpected << "\n";
        message << " sampleRate = " << sampleRate;
        Logger::getCurrentLogger()->writeToLog (message);
        }
        
void MainContentComponent::releaseResources()
        {
            Logger::getCurrentLogger()->writeToLog ("Releasing audio resources");
        }
        
void MainContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
        {
            double fs=44100, timeSec, a=0.005,aG=0.001,sinTmp,fVib=6,envGainAdj,TExpWin=0.5,expWin,dBAtt=-60,linWin, gain=1.1;
            static double freqSinSmoothLog=0, FM[1000],freqSinSmooth,freqUpdate,depthSmooth,envGainSmooth,TEndSampleIdx=0;
            static bool flagAtt=false;
            int i;
            
            //for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
            //{
                // Get a pointer to the start sample in the buffer for this audio output channel
                float* const buffer0 = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
                float* const buffer1 = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);

            //if (channel==0){
                sawEnvelope.generateEnvelope(bufferToFill.numSamples);
                //}

              // std::cout << "buff" << bufferToFill.numSamples << std::endl;
                // Fill the required number of samples with noise betweem -0.125 and +0.125
                for (int sample = 0; sample < bufferToFill.numSamples; ++sample){
                    //buffer[sample] = random.nextFloat() * 0.25f - 0.125f;
                    //if (channel==0){
                        if(touchBegun==true){
                            freqSinSmooth=freqSin;
                            timeSampleIdx=0;
                            touchBegun=false;
                            flagOn=true;
                            flagAtt=false;
                            TEndSampleIdx=TExpWin*fs;
                            printf("flagAtt false\n");
                        }
                        else{
                            if(touchEnded==true)
                            {
                                flagAtt=true;
                                touchEnded=false;
                                TEndSampleIdx=TExpWin*fs;
                                printf("set FlagAtt true\n");
                            }
//                            printf("flag att %d\n",flagAtt);
                        //    if(flagOn==true){
                                timeSec=((double) timeSampleIdx++)/fs;
                                freqSinSmoothLog=a*log2(freqSin+0.01)+(1-a)*freqSinSmoothLog;
                                
                                //printf("freq smft %lf freq %lf mem0 %lf mem1 %lf \n",freqSinSmooth,freqSin,FM[0],FM[1]);
                                freqSinSmooth=pow(2,freqSinSmoothLog);
                                freqUpdate=freqUpdate+freqSinSmooth;
                                depthSmooth=aG*depth+(1-aG)*depthSmooth;
                                sinTmp=sin(2*3.14*freqUpdate/fs+2*depthSmooth*sin(2*3.14*fVib*timeSec))+ 0.25*sin(2*3.14*2*freqUpdate/fs+depthSmooth*sin(2*3.14*fVib*timeSec/fs));
                                envGainSmooth=aG*envGain+(1-aG)*envGainSmooth;
                                envGainAdj=pow(envGainSmooth,0.5);
                                if (timeSec<TExpWin)
                                {
                                    linWin=(-1/TExpWin*dBAtt*timeSec+dBAtt);
                                    expWin=pow(10,linWin/20);
                                }
                                else
                                    expWin=1;
                            
                                if(flagAtt==true && TEndSampleIdx>=0)
                                {
                                    linWin=-1/TExpWin*dBAtt*((TEndSampleIdx--)/fs)+dBAtt;
                                    expWin=pow(10,linWin/20);
                                    if(TEndSampleIdx==0)
                                        flagOn=false;
                                }
                                else
                                {
                                    //printf("flag att false\n");
                                    
                                }
                                //printf("envGainAdj %f depthSmooth %f\n",envGainAdj, depthSmooth);
                                //printf("expWin %f linWin %f", expWin, linWin);
                                if (flagOn==true)
                                buffer0[sample]=expWin*pow(fabs(0.05*sawEnvelope.outEnvelope[sample]),envGainAdj)*0.03*sinTmp;
                                else
                                    buffer0[sample]=0;
                            }
                            //else{
                            //    buffer0[sample]=0;
                            //}
                            buffer1[sample]=gain*buffer0[sample];
                        //}
                    }
                    
                  // printf("time idx %d sec %lf buff %lf sample %d ",timeSampleIdx, timeSec, buffer[sample],sample);

                }
            //}
        //}
        
        
//Component* createMainContentComponent()     { return new MainContentComponent(); }
        

#endif  // MAINCOMPONENT_H_INCLUDED
