//
//  elementOscilator.cpp
//  DGTL_Generator
//
//  Created by Eduard Frigola on 29/07/16.
//
//

#include "elementOscilator.h"

elementOscilator::elementOscilator(){
    freq_Param = PI;
    indexCount_Param = 144;
    pow_Param = 1;
    invert_Param = 1;
    
    generatorGui = new ofxDatGui();
}

void elementOscilator::setup(){
    generatorGui->addHeader();
    generatorGui->addLabel("Index Modify Parameters");
    generatorGui->setPosition(ofxDatGuiAnchor::TOP_RIGHT);
    generatorGui->addSlider(freq_Param.set("Horizontal displacement", 1, 0, indexCount_Param));
    generatorGui->addToggle("Invert");
    generatorGui->addSlider(pow_Param.set("Pow", 1, -40, 40));
    
    generatorGui->onButtonEvent(this, &elementOscilator::onGuiButtonEvent);
}

float elementOscilator::computeFunc(float phasor, int index){
    //get phasor to be w (radial freq)
    float w = phasor*2*PI;
    
    //we first get the displacement between 0 and 1 depending of the index
    float k = ((float)index/(float)indexCount_Param) * 2 * PI;
    
    //invert it?
    k *= invert_Param;
    
    k *=  freq_Param; //Index Modifiers
    float val = sin(w+k);

    computeMultiplyMod(&val);
    return val;
}

void elementOscilator::computeMultiplyMod(float *value){
    //Values between 0 and 1
    *value = ofMap(*value, -1, 1, 0, 1);
    
    //pow
    if(pow_Param)
        *value = (pow_Param < 0) ? pow(*value, 1/(float)(-pow_Param)) : pow(*value, pow_Param);
}


void elementOscilator::onGuiButtonEvent(ofxDatGuiButtonEvent e){
    if(e.target->getName() == "Invert")
        invert_Param = e.enabled ? -1 : 1;
}

