//
//  elementOscilator.h
//  DGTL_Generator
//
//  Created by Eduard Frigola on 29/07/16.
//
//

#ifndef elementOscilator_h
#define elementOscilator_h

#include "ofMain.h"
#include "ofxDatGui.h"

enum oscTypes{
    sinOsc = 1,
    cosOsc = 2,
    triOsc = 3,
    squareOsc = 4,
    sawOsc = 5,
    sawInvOsc = 6,
    rand1Osc = 7,
    rand2Osc = 8
};

class elementOscilator{
public:
    elementOscilator();
    ~elementOscilator(){};
    
    void setup();
    
    float computeFunc(float phasor, int index);
    void computeMultiplyMod(float* value);
    
    void setIndexCount(int val){indexCount_Param = val;};
    
    void onGuiButtonEvent(ofxDatGuiButtonEvent e);
    void onGuiDropdownEvent(ofxDatGuiDropdownEvent e);
    
private:
    //Parameters
    ofParameter<float>  freq_Param; //Desphase Quantity
    ofParameter<int>    pow_Param; //Pow of the funcion, working on sin, cos....
    ofParameter<int>    indexCount_Param; //The max number you will get from index
    ofParameter<float>  pwm_Param;
    bool                 invert_Param;
    ofParameter<float>  holdTime_Param; //The duration of the hold in percentage (0.5) --> 50% of the cycle is the phase in initPhase
    ofParameter<float>  phaseOffset_Param;
    
    oscTypes modulation;
    
    ofxDatGui *generatorGui;
};

#endif /* elementOscilator_h */
