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
    modulation = triOsc;
    
    generatorGui = new ofxDatGui();
}

void elementOscilator::setup(){
    generatorGui->addHeader();
    generatorGui->addLabel("Index Modify Parameters");
    generatorGui->setPosition(ofxDatGuiAnchor::TOP_RIGHT);
    generatorGui->addSlider(freq_Param.set("n Waves", 1, 0, indexCount_Param));
    generatorGui->addSlider(phaseOffset_Param.set("Phase offset", 0, 0, 1));
    generatorGui->addToggle("Invert")->setEnabled(false);
    generatorGui->addSlider(symmetry_Param.set("Symmetry", 0, 0, 10));
    generatorGui->addSlider(indexOffset_Param.set("Index Offset", 0, -indexCount_Param, indexCount_Param));
    generatorGui->addSlider(indexQuant_Param.set("Index Quantization", 1, 1, indexCount_Param));
    generatorGui->addSlider(comb_Param.set("Combination", 0, 0, 1));
    generatorGui->addSlider(modulo_Param.set("Modulo", 1, 1, indexCount_Param));
    generatorGui->addBreak();
    generatorGui->addLabel("Multipliers");
    generatorGui->addSlider(quant_Param.set("Quantization", 0, 0, 1));
    generatorGui->addSlider(pow_Param.set("Pow", 1, -40, 40));
    generatorGui->addSlider(pwm_Param.set("Square PWM", 0.5, 0, 1));
    generatorGui->addDropdown("Wave Select", {"sin", "cos", "tri", "square", "saw", "inverted saw", "rand1", "rand2"});
    
    generatorGui->onButtonEvent(this, &elementOscilator::onGuiButtonEvent);
    generatorGui->onDropdownEvent(this, &elementOscilator::onGuiDropdownEvent);
}

float elementOscilator::computeFunc(float phasor, int index){
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
    switch (modulation) {
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
            val = ofNoise(ofGetElapsedTimef()*2+((float)index/(float)indexCount_Param)*freq_Param);
            val = ofMap(val, 0.25, 0.75, 0, 1, true);
            break;
        }
        case rand2Osc:
        {
            val = ofNoise(phasor+index);
            break;
        }
        default:
            break;
    }
    

    computeMultiplyMod(&val);
    return val;
}

void elementOscilator::computeMultiplyMod(float *value){
  
    
    //pow
    if(pow_Param)
        *value = (pow_Param < 0) ? pow(*value, 1/(float)(-pow_Param)) : pow(*value, pow_Param);
    
    //Quantization
    if(quant_Param)
        *value = quant_Param*floor(*value/quant_Param);
    
}


void elementOscilator::onGuiButtonEvent(ofxDatGuiButtonEvent e){
    if(e.target->getName() == "Invert")
        invert_Param = e.enabled;
}

void elementOscilator::onGuiDropdownEvent(ofxDatGuiDropdownEvent e){
    if(e.target->getName() == "Wave Select")
        modulation = static_cast<oscTypes>(e.child+1);
}






