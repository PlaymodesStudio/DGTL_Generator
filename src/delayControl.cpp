//
//  delayControl.cpp
//  DGTL_Generator
//
//  Created by iClon Media  on 02/08/16.
//
//

#include "delayControl.h"

void delayControl::setup(){
    generatorGui = new ofxDatGui();
    
    generatorGui->addHeader();
    generatorGui->setPosition(300, 300);
    generatorGui->addLabel("Delay Modify Parameters");
    generatorGui->setPosition(ofxDatGuiAnchor::TOP_RIGHT);
    generatorGui->addToggle("Invert")->setEnabled(false);
    generatorGui->addSlider(symmetry_Param.set("Symmetry", 0, 0, 10));
    //generatorGui->addSlider(indexOffset_Param.set("Index Offset", 0, -indexCount_Param, indexCount_Param));
    generatorGui->addSlider(indexQuant_Param.set("Index Quantization", 1, 1, indexCount_Param));
    generatorGui->addSlider(comb_Param.set("Combination", 0, 0, 1));
    //generatorGui->addBreak();
    //generatorGui->addLabel("Multipliers");
    //generatorGui->addSlider(pow_Param.set("Pow", 1, -40, 40));
    //generatorGui->addDropdown("Wave Select", {"sin", "cos", "tri", "square", "saw", "inverted saw", "rand1", "rand2"});
    
    generatorGui->onButtonEvent(this, &delayControl::onGuiButtonEvent);
}


int delayControl::computeFunc(int index){
    
//    bool odd = false;
//    if((int)((index)/(indexCount_Param/(symmetry_Param+1)))%2 == 1 ) odd = true;
//    
    //SYMMETRY santi
    int veusSym = indexCount_Param/(symmetry_Param+1);
    index = veusSym-abs((((int)(index/veusSym)%2) * veusSym)-(index%veusSym));
//
//    index = odd ? index-indexOffset_Param : index+indexOffset_Param;
    
    //    index += indexOffset_Param;
    //    index %= indexCount_Param;
    
    
    
    //INVERSE
    //Fisrt we invert the index to simulate the wave goes from left to right, inverting indexes, if we want to invertit we don't do this calc
    if(!invert_Param)
        index = ((float)indexCount_Param-(float)index+1);
    
    
    //QUANTIZE
    index = ceil(index/indexQuant_Param);
    
    //cout<<index<<"-" ;
    
    //COMB
    index = abs(((index%2)*indexCount_Param*comb_Param)-index);
    
    
    //float k = (((float)index/(float)indexCount_Param) + phaseOffset_Param) * 2 * PI;
    
    
//    float indexFloat = index/indexCount_Param;
//    if(pow_Param)
//        indexFloat = (pow_Param < 0) ? pow(index, 1/(float)(-pow_Param)) : pow((float)index, pow_Param);
//    index = indexFloat * indexCount_Param;
//    index = round(index);
//;
//    index = floor(index);
    
    
    return index;

}


void delayControl::onGuiButtonEvent(ofxDatGuiButtonEvent e){
    if(e.target->getName() == "Invert")
        invert_Param = e.enabled;
}