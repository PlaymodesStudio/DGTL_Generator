//
//  parametersControl.cpp
//  DGTL_Generator
//
//  Created by Eduard Frigola on 03/08/16.
//
//

#include "parametersControl.h"

void parametersControl::setup(){
    
    
    //datGui
    datGui = new ofxDatGui();
    datGui->addHeader();
    datGui->setPosition(ofxDatGuiAnchor::TOP_LEFT);
    datGui->addSlider(phasorParams.getFloat("BPM"));// bpm_Param.set("BPM", 60, 30, 180));
    datGui->addSlider(phasorParams.getInt("Beats Div"));
    datGui->addSlider(phasorParams.getInt("Beats Mult"));
    datGui->addSlider(phasorParams.getInt("Quantization"));
    datGui->addSlider(phasorParams.getFloat("Initial phase"))->setPrecision(2);
    datGui->addButton("Reset Phase");
    datGui->addToggle("Loop")->setEnabled(true);
//
    datGui->onButtonEvent(this, &parametersControl::onGuiButtonEvent);
    datGui->onToggleEvent(this, &parametersControl::onGuiToggleEvent);
//    datGui->onSliderEvent(this, &phasorClass::onGuiSliderEvent);
}


void parametersControl::onGuiButtonEvent(ofxDatGuiButtonEvent e){
        if(e.target->getName() == "Reset Phase")
            phasorParams.getBool("Reset Phase") = true;
    
}
void parametersControl::onGuiToggleEvent(ofxDatGuiToggleEvent e){
    if(e.target->getName() == "Loop")
        phasorParams.getBool("Loop") = e.target->getChecked();
}