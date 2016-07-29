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
    freq = 2;
    holdTime = 0;
    quantization = 0;
}

void phasorClass::setup(){
    soundStream.setup(0, 2, 44100, 512, 4);
    soundStream.setInput(this);
}


float phasorClass::getPhasor(){
    return phasorMod;
}

void phasorClass::resetPhasor(float phase){
    phasor = phase;
}

void phasorClass::audioIn(float * input, int bufferSize, int nChannels){
    //tue phasor that goes from 0 to 1 at desired frequency
    phasor += (1./(((float)44100/(float)512)/(freq)));
    if ( phasor >= 1.0 ) phasor -= 1.0;
    
    //Assign a copy of the phasor to make some modifications
    phasorMod = phasor;
    
    //Quantization
    if(quantization){
        phasorMod = (int)(phasorMod*quantization);
        phasorMod /= quantization;
    }
    
    
    //Hold to freq
    //No control over phase holding
    phasorMod *= (1.0f/(1.0f-holdTime));
    if(phasorMod <= 1)
        phasorMod = 0;
    
    
}

