//
//  envelope.cpp
//  saha
//
//  Created by Kalle Palomäki on 13/11/15.
//
//

#include "envelope.h"
#include <math.h>

void filterIIR::filterLoop(){
    int coeffIdx,tIdx;
    outEnvelope.clear();
    if(1){
        for (tIdx=0; tIdx<buffLen; tIdx++) {
            yBuffer[0]=y;
            xBuffer[0]=inSignal[tIdx];
            y=xBuffer[0]*b[0];
            
            //     filtering loop
            for(coeffIdx=0; coeffIdx<taps-1; coeffIdx++) {
                y=y+b[coeffIdx+1]*xBuffer[coeffIdx+1]-a[coeffIdx]*yBuffer[coeffIdx];
            }
            
            // buffer update loop
            for (coeffIdx=0; coeffIdx<taps-1; coeffIdx++) {
                xBuffer[taps-1-coeffIdx]=xBuffer[taps-1-coeffIdx-1];
                yBuffer[taps-1-coeffIdx]=yBuffer[taps-1-coeffIdx-1];
            }
            //y=inSignal[tIdx];
           // printf("%f\n",y);
            outEnvelope.push_back(y);
            //k=k+1;
        }
    }
};

void filterIIR::initializeVibIntegrator(){
    a = {-2.996999269953500,2.994002270683550,-0.997002999000000};//a = {-0.9}; // don't put here the first 1 coeff
    b = {1,       0,      0,       0};
    y=0;
    taps = b.size();
    xBuffer.assign(taps,0);
    yBuffer.assign(taps,0);
    //printf("taps %d\n", taps);
}

void filterIIR::initializeLpIIR(){
    a = {-4.976946936254024,   9.908053243459456,  -9.862476225051555,   4.908580473024985,  -0.977210555160725};//a = {-0.9}; // don't put here the first 1 coeff
    b = {1.0e-11*0.0567, 1.0e-11*0.2834, 1.0e-11*0.5668, 1.0e-11*0.5668, 1.0e-11*0.2834, 1.0e-11*0.05671};
    taps = b.size();
    y=0;
    xBuffer.assign(taps,0);
    yBuffer.assign(taps,0);
    printf("taps %d\n", taps);
}


envelope::envelope(){
    vibIntegrator.initializeVibIntegrator();
    lpIIR.initializeLpIIR();
    
}

void envelope::generateEnvelope(int numSamples)
{
    int i;
    double ranNu;
    
    vibIntegrator.inSignal.clear();
    vibIntegrator.outEnvelope.clear();
    lpIIR.inSignal.clear();
    lpIIR.outEnvelope.clear();
    for (i=0;i<numSamples;i++){
        ranNu= pow(10,-5)*(((double) rand())/ ((double) RAND_MAX)-0.488);
        vibIntegrator.inSignal.push_back(ranNu);
    }/**/
    vibIntegrator.buffLen=vibIntegrator.inSignal.size();
    vibIntegrator.filterLoop();
    

    lpIIR.inSignal=vibIntegrator.outEnvelope;//,vibIntegrator.out.size());
    lpIIR.buffLen=lpIIR.inSignal.size();
    lpIIR.filterLoop();
    
     outEnvelope=lpIIR.outEnvelope;
    
}



