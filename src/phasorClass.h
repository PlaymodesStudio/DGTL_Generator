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
#include "ofxDatGui.h"

class phasorClass: public ofBaseSoundInput{
public:
    phasorClass();
    ~phasorClass(){};
    void setup();
    
    void setFrequency(float frequency){freq_Param = frequency;};
    float getPhasor();
    void resetPhasor(float phase);
    
    void audioIn(float * input, int bufferSize, int nChannels);
    
    void onGuiButtonEvent(ofxDatGuiButtonEvent e);
    
private:
    ofParameter<float> phasor;
    ofParameter<float> phasorMod;
    ofParameter<float> freq_Param;
    ofParameter<float> initPhase_Param;
    ofParameter<int> quant_Param;
    bool                loop_Param;
    
    ofxDatGui* gui;
    
    
    ofSoundStream soundStream;
};


#endif /* phasor_h */
