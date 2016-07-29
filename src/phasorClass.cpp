//
//  phasorClass.cpp
//  DGTL_Generator
//
//  Created by Eduard Frigola on 28/07/16.
//
//

#include "phasorClass.h"


phasorClass::phasorClass()
{
    gui = new ofxDatGui();
    loop_Param = true;
}

void phasorClass::setup(){
    soundStream.setup(0, 2, 44100, 512, 4);
    soundStream.setInput(this);
    
    gui->setPosition(ofxDatGuiAnchor::TOP_LEFT);
    gui->addSlider(freq_Param.set("Frequency", 1, 0, 10));
    gui->addSlider(quant_Param.set("Quantization", 30, 1, 30));
    gui->addBreak();
//    gui->addLabel("Phasor Parameters");
    gui->addSlider(initPhase_Param.set("Initial phase", 0, 0, 1))->setPrecision(2);
    gui->addButton("Reset Phase");
    gui->addToggle("Loop")->setEnabled(true);
    gui->onButtonEvent(this, &phasorClass::onGuiButtonEvent);
}


float phasorClass::getPhasor(){
    return phasorMod;
}

void phasorClass::resetPhasor(float phase){
    phasor = phase;
}

void phasorClass::audioIn(float * input, int bufferSize, int nChannels){
    //tue phasor that goes from 0 to 1 at desired frequency
    if ( phasor < 1)
        phasor += (1./(((float)44100/(float)512)/(freq_Param)));
    
    if ( phasor >= 1.0 && loop_Param) phasor -= 1.0;
    
    //Assign a copy of the phasor to make some modifications
    phasorMod = phasor;
    
    //Quantization
    if(quant_Param != 30){
        phasorMod = (int)(phasorMod*quant_Param);
        phasorMod /= quant_Param;
    }
    
    
    //Hold to freq
    //No control over phase holding
//    phasorMod *= (1.0f/(1.0f-holdTime));
//    if(phasorMod >= 1)
//        phasorMod = 0;
    
    
}


void phasorClass::onGuiButtonEvent(ofxDatGuiButtonEvent e){
    if(e.target->getName() == "Reset Phase")
        resetPhasor(initPhase_Param);
    
    if(e.target->getName() == "Loop")
        loop_Param = e.enabled;
}

