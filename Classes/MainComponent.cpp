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
#include <random>
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
            double fs=44100, timeSec, a=0.005,aG=0.001,sinTmp, sinTmp2, sinTmp3,fVibBase=4, fVib,envGainAdj,  envFunc,envFuncSmooth,TExpWin=0.5,expWin,dBAtt=-60,linWin, gain=1.5;
            static double freqSinSmoothLog=0, FM[1000],freqSinSmooth,freqUpdate, raSmooth=0, freq2Update, ra_sample=0, freq3Update,depthSmooth,envGainSmooth,TEndSampleIdx=0;
            static bool flagAtt=false;
            int i;
            static int buffer_cnt=0;
            // random device class instance, source of 'true' randomness for initializing random seed
            
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
            //printf("start sample buffer\n");
            
            if (buffer_cnt==0){
                std::random_device rd;

                // Mersenne twister PRNG, initialized with seed from previous random device instance
                std::mt19937 gen(rd());
                std::normal_distribution<float> d(0, 5.0);
                ra_sample = d(gen);
            }
            buffer_cnt++;

            if (buffer_cnt==20) {
                buffer_cnt=0;
            }
            
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
                            //printf("flagAtt false\n");
                        }
                        else{
                            if(touchEnded==true)
                            {
                                flagAtt=true;
                                touchEnded=false;
                                TEndSampleIdx=TExpWin*fs;
                                //printf("set FlagAtt true\n");
                            }
//                            printf("flag att %d\n",flagAtt);
                        //    if(flagOn==true){
                                timeSec=((double) timeSampleIdx++)/fs;
                                freqSinSmoothLog=a*log2(freqSin+0.01)+(1-a)*freqSinSmoothLog;
                                
                                //printf("freq smft %lf freq %lf mem0 %lf mem1 %lf \n",freqSinSmooth,freqSin,FM[0],FM[1]);
                                freqSinSmooth=pow(2,freqSinSmoothLog);
                                freqUpdate=freqUpdate+freqSinSmooth;
                                freq2Update=1.001*freqUpdate;
                                freq3Update=0.9991*freqUpdate;
                                envGainSmooth=aG*envGain+(1-aG)*envGainSmooth;
                                envGainAdj=pow(envGainSmooth,0.5);
                                
                                //printf("envgain %f \n",envGainAdj);
                                depthSmooth=aG*depth*1.3+(1-aG)*depthSmooth;
                                envFunc=pow(fabs(0.05*sawEnvelope.outEnvelope[sample]),envGainAdj);
                                raSmooth=0.0000001*ra_sample+(1-0.0000001)*raSmooth;

                                
                                fVib=fVibBase+raSmooth;
                                //if (sample==0)
                                 //   printf("val %f %f %f %f\n", fVib, envGainAdj, ra_sample, raSmooth);
                                sinTmp=sin(2*3.14*freqUpdate/fs+2*depthSmooth*sin(2*3.14*fVib*timeSec))+ 0.25*sin(2*3.14*2*freqUpdate/fs+depthSmooth*sin(2*3.14*fVib*timeSec/fs));
                                sinTmp2=sin(2*3.14*freq2Update/fs+2*depthSmooth*sin(2*3.14*fVib*timeSec))+ 0.25*sin(2*3.14*2*freq2Update/fs+depthSmooth*sin(2*3.14*fVib*timeSec/fs));
                                sinTmp3=sin(2*3.14*freq3Update/fs+2*depthSmooth*sin(2*3.14*fVib*timeSec))+ 0.25*sin(2*3.14*2*freq3Update/fs+depthSmooth*sin(2*3.14*fVib*timeSec/fs));
                                
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
                                    buffer0[sample]=expWin*pow(fabs(0.05*sawEnvelope.outEnvelope[sample]),0*envGainAdj)*0.03*0.7*(sinTmp+0.1*sinTmp2+0.1*sinTmp3);
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
