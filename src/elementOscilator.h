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

class elementOscilator{
public:
    elementOscilator();
    ~elementOscilator(){};
    
    void setup();
    
    float computeFunc(float phasor, int index);
    void computeMultiplyMod(float* value);
    
    void setIndexCount(int val){indexCount_Param = val;};
    
    void onGuiButtonEvent(ofxDatGuiButtonEvent e);
    
private:
    //Parameters
    ofParameter<float>  freq_Param; //Desphase Quantity
    ofParameter<int>    pow_Param; //Pow of the funcion, working on sin, cos....
    ofParameter<int>    indexCount_Param; //The max number you will get from index
    int                 invert_Param;
    
    ofxDatGui *generatorGui;
};

#endif /* elementOscilator_h */
