//
//  elementOscilator.cpp
//  DGTL_Generator
//
//  Created by Eduard Frigola on 29/07/16.
//
//

#include "elementOscilator.h"

elementOscilator::elementOscilator(){
    freq_Param = 10;
    indexCount_Param = 144;
    pow_Param = 1;
}

float elementOscilator::computeFunc(float phasor, int index){
    float w = phasor*2*PI; //Phase modifiers go outside
    float k = index * (freq_Param/indexCount_Param); //Index Modifiers
    float val = sin(w+k);
    val /= 2;
    val += 0.5;
    val = pow(val, pow_Param);
    
    return val;

}