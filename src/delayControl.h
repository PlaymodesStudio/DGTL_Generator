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
    void applyDelayToTexture(ofFbo &fbo, vector<float> infoVec);
    
    void onGuiToggleEvent(ofxDatGuiToggleEvent e);
    void setIndexCount(int indexCount){indexCount_Param = indexCount;};
    
private:
    
    ofxDatGui *generatorGui;
    
    //Parameters
    ofParameter<int>    indexCount_Param; //The max number you will get from index
    ofParameter<bool>   invert_Param;
    ofParameter<int>    symmetry_Param;
    ofParameter<float>  comb_Param;
    ofParameter<float>  delay_frames;
    
    //Buffer of intoVec, we use deque to be able to create a circular buffer, erase the old values
    deque<vector<float>> infoVecBuffer;
};

#endif /* delayControl_h */
