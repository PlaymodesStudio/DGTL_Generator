//
//  parametersControl.h
//  DGTL_Generator
//
//  Created by Eduard Frigola on 03/08/16.
//
//

#ifndef parametersControl_h
#define parametersControl_h

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxDatGui.h"

class parametersControl{
public:
    
    parametersControl(){};
    ~parametersControl(){};
    
    void bindPhasorParams(ofParameterGroup paramGroup){phasorParams = paramGroup;};
    void bindOscilatorParams(ofParameterGroup paramGroup){oscilatorParams = paramGroup;};
    void bindDelayParams(ofParameterGroup paramGroup){delayParams = paramGroup;};
    
    void setup();
    void update();
    
    void onGuiButtonEvent(ofxDatGuiButtonEvent e);
    void onGuiToggleEvent(ofxDatGuiToggleEvent e);
    void onGuiDropdownEvent(ofxDatGuiDropdownEvent e);
    
private:
    
    ofParameterGroup phasorParams;
    ofParameterGroup oscilatorParams;
    ofParameterGroup delayParams;
    
    ofxDatGui *datGui;
    
    ofxOscReceiver oscReceiver;
};


#endif /* parametersControl_h */
