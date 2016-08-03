//
//  delayControl.h
//  DGTL_Generator
//
//  Created by iClon Media  on 02/08/16.
//
//

#ifndef delayControl_h
#define delayControl_h

#include "ofMain.h"
#include "ofxDatGui.h"

class delayControl{
public:
    delayControl(){};
    ~delayControl(){};
    
    void setup();
    int computeFunc(int index);
    
    void onGuiToggleEvent(ofxDatGuiToggleEvent e);
    void setIndexCount(int indexCount){indexCount_Param = indexCount;};
    
private:
    
    ofxDatGui *generatorGui;
    
    //Parameters
    ofParameter<int>    pow_Param; //Pow of the funcion, working on sin, cos....
    ofParameter<int>    indexCount_Param; //The max number you will get from index
    bool                 invert_Param;
    ofParameter<int>    symmetry_Param;
    ofParameter<float>  holdTime_Param; //The duration of the hold in percentage (0.5) --> 50% of the cycle is the phase in initPhase
    ofParameter<int>    indexOffset_Param;
    ofParameter<int>    indexQuant_Param;
    ofParameter<float>  comb_Param;
};

#endif /* delayControl_h */
