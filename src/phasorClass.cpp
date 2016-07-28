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
}

void phasorClass::setup(){
    soundStream.setup(0, 2, 44100, 512, 4);
    soundStream.setInput(this);
}


float phasorClass::getPhasor(){
    return phasor;
}

void phasorClass::resetPhasor(float phase){
    phasor = phase;
}

void phasorClass::audioIn(float * input, int bufferSize, int nChannels){    
    phasor += (1./(((float)44100/(float)512)/(freq)));
    if ( phasor >= 1.0 ) phasor -= 1.0;
}

