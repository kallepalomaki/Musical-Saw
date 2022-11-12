//
//  filterIIR.hpp
//  saha
//
//  Created by Kalle Palomäki on 13/11/15.
//
//

#ifndef filterIIR_hpp
#define filterIIR_hpp

#include <stdio.h>
#include <vector>

class filterIIR {
public:
    int taps,buffLen;
    std::vector <double> a, b, xBuffer, yBuffer,inSignal, outEnvelope;
    double y;
    void initializeVibIntegrator();
    void filterLoop();
    void initializeLpIIR();
};

class envelope {
public:
    std::vector <double> outEnvelope;
    void generateEnvelope(int);
    envelope();
    filterIIR vibIntegrator, lpIIR;
};

//envelope vibIntegrator, lpIIR;

#endif /* filterIIR_hpp */
