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
#include "ofxGui.h"

class phasorClass: public ofBaseSoundInput{
public:
    phasorClass();
    ~phasorClass(){};
    void setup();
    
    float getPhasor();
    void resetPhasor(bool &reset);
    
    void drawGui(){gui2.draw();};
    
    void audioIn(float * input, int bufferSize, int nChannels);
    
    void onGuiButtonEvent(ofxDatGuiButtonEvent e);
    void onGuiToggleEvent(ofxDatGuiToggleEvent e);
    void onGuiSliderEvent(ofxDatGuiSliderEvent e);
    
    ofParameterGroup getParameterGroup(){return parameters;};
    
private:
    ofParameterGroup    parameters;
    ofParameter<float>  phasor;
    ofParameter<float>  phasorMod;
    ofParameter<float>  bpm_Param;
    ofParameter<int>    beatsMult_Param;
    ofParameter<int>    beatsDiv_Param;
    ofParameter<float>  initPhase_Param;
    ofParameter<int>    quant_Param;
    ofParameter<bool>   loop_Param;
    ofParameter<bool>   resetPhase_Param;
    
    ofxDatGui* gui;
    ofxPanel gui2;
    
    
    ofSoundStream soundStream;
};


#endif /* phasor_h */
