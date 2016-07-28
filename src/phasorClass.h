//
//  phasorClass.h
//  DGTL_Generator
//
//  Created by Eduard Frigola on 28/07/16.
//
//

#ifndef phasorClass_h
#define phasorClass_h

#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofEvents.h"

class phasorClass: public ofBaseSoundInput{
public:
    phasorClass();
    ~phasorClass(){};
    void setup();
    
    void setFrequency(float frequency){freq = frequency;};
    float getPhasor();
    
    void audioIn(float * input, int bufferSize, int nChannels);
    
private:
    float phasor;
    float freq;
    float timestamp;
    
    ofSoundStream soundStream;
};


#endif /* phasor_h */
