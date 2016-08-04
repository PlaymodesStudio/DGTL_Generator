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
    indexCount_Param = 432;
    pow_Param = 1;
    invert_Param = false;
    symmetry_Param = 0;
}

void elementOscilator::setup(){
    parameters.add(freq_Param.set("n Waves", 1, 0, indexCount_Param));
    parameters.add(phaseOffset_Param.set("Phase offset", 0, 0, 1));
    parameters.add(invert_Param.set("Invert", false));
    parameters.add(symmetry_Param.set("Symmetry", 0, 0, 10));
    parameters.add(indexOffset_Param.set("Index Offset", 0, -indexCount_Param, indexCount_Param));
    parameters.add(indexQuant_Param.set("Index Quantization", 1, 1, indexCount_Param));
    parameters.add(comb_Param.set("Combination", 0, 0, 1));
    parameters.add(modulo_Param.set("Modulo", indexCount_Param, 1, indexCount_Param));
    parameters.add(randomAdd_Param.set("Random addition", 0, -1, 1));
    parameters.add(quant_Param.set("Quantization", 0, 0, 1));
    parameters.add(scale_Param.set("Scale", 1, 0, 2));
    parameters.add(offset_Param.set("Offset", 0, -1, 1));
    parameters.add(pow_Param.set("Pow", 1, -40, 40));
    parameters.add(pwm_Param.set("Square PWM", 0.5, 0, 1));
    parameters.add(waveSelect_Param.set("Wave Select", 0, 0, 7));
}

void elementOscilator::computeFunc(float *infoVec, float phasor){
    
    for (int i = 0; i < indexCount_Param ; i++){
        
        int index = i;
        
        //get phasor to be w (radial freq)
        float w = (phasor*2*PI);// + (phaseOffset_Param*2*PI);
        
        bool odd = false;
        if((int)((index)/(indexCount_Param/(symmetry_Param+1)))%2 == 1 ) odd = true;
        
        //SYMMETRY santi
        int veusSym = indexCount_Param/(symmetry_Param+1);
        index = veusSym-abs((((int)(index/veusSym)%2) * veusSym)-(index%veusSym));
        
        index = odd ? index-indexOffset_Param : index+indexOffset_Param;
        
        //    index += indexOffset_Param;
        //    index %= indexCount_Param;
        
        
        
        //INVERSE
        //Fisrt we invert the index to simulate the wave goes from left to right, inverting indexes, if we want to invertit we don't do this calc
        if(!invert_Param)
            index = ((float)indexCount_Param-(float)index);
        
        
        //QUANTIZE
        index = ceil(index/indexQuant_Param);
        
        //cout<<index<<"-" ;
        
        //COMB
        index = abs(((index%2)*indexCount_Param*comb_Param)-index);
        
        //modeulsafidosia
        index %= modulo_Param;
        
        
        float k = (((float)index/(float)indexCount_Param) + phaseOffset_Param) * 2 * PI;
        
        
        
        //invert it?
        //k *= invert_Param;
        k *=  freq_Param; //Index Modifiers
        
        
        float linPhase = fmod(w+k, 2*PI) / (2*PI);
        float val = 0;
        switch (static_cast<oscTypes>(waveSelect_Param.get()+1)) {
            case sinOsc:
            {
                val = sin(w+k);
                val = ofMap(val, -1, 1, 0, 1);
                break;
                
            }
            case cosOsc:
            {
                val = cos(w+k);
                val = ofMap(val, -1, 1, 0, 1);
                break;
            }
            case triOsc:
            {
                val = 1-(fabs((linPhase * (-2)) + 1));
                break;
            }
            case squareOsc:
            {
                val = (linPhase > pwm_Param) ? 1 : 0;
                break;
            }
            case sawOsc:
            {
                val = 1-linPhase;
                break;
            }
            case sawInvOsc:
            {
                val = linPhase;
                break;
            }
            case rand1Osc:
            {
                if(phasor < oldPhasor){
                    if(index != prevIndex)
                        val = ofRandom(1);
                    else
                        val = infoVec[i-1];
                }
                else
                    val = infoVec[i];
                
                break;
            }
            case rand2Osc:
            {
                val = ofNoise(w+((float)index/(float)indexCount_Param));
                val = ofMap(val, 0.25, 0.75, 0, 1, true);
                break;
            }
            default:
                break;
        }
        
        
        
        computeMultiplyMod(&val);
        if(i == indexCount_Param-1)
            oldPhasor = phasor;
        
        infoVec[i] = val;
        prevIndex = index;
    }
}

void elementOscilator::computeMultiplyMod(float *value){
  
    //SCALE
    *value *= scale_Param;
    
    //OFFSETç
    *value += offset_Param;
    
    //random Add
    if(randomAdd_Param)
        *value += randomAdd_Param*ofRandom(1);
    
    *value = ofClamp(*value, 0, 1);
    
    //pow
    if(pow_Param)
        *value = (pow_Param < 0) ? pow(*value, 1/(float)(-pow_Param)) : pow(*value, pow_Param);
    
    //Quantization
    if(quant_Param)
        *value = quant_Param*floor(*value/quant_Param);
    
}





