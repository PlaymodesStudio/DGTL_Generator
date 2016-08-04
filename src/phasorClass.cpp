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
    loop_Param = true;
}

void phasorClass::setup(){
    soundStream.setup(0, 2, 44100, 512, 4);
    soundStream.setInput(this);
    
    
    parameters.setName("Phasor");
    parameters.add(bpm_Param.set("BPM", 60, 30, 180));
    parameters.add(beatsDiv_Param.set("Beats Div", 1, 1, 12));
    parameters.add(beatsMult_Param.set("Beats Mult", 1, 1, 12));
    parameters.add(quant_Param.set("Quantization", 40, 1, 30));
    parameters.add(initPhase_Param.set("Initial phase", 0, 0, 1));
    parameters.add(resetPhase_Param.set("Reset Phase", false));
    parameters.add(loop_Param.set("Loop", true));
    
    resetPhase_Param.addListener(this, &phasorClass::resetPhasor);
}


float phasorClass::getPhasor(){
    return phasorMod;
}

void phasorClass::resetPhasor(bool &reset){
    phasor = initPhase_Param;
    resetPhase_Param = false;
}

void phasorClass::audioIn(float * input, int bufferSize, int nChannels){
    //tue phasor that goes from 0 to 1 at desired frequency
    float freq = bpm_Param/60;
    freq *= beatsMult_Param;
    freq /= beatsDiv_Param;
    
    if ( phasor < 1)
        phasor += (1./(((float)44100/(float)512)/freq));
    
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

