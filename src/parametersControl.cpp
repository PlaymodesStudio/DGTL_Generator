//
//  parametersControl.cpp
//  DGTL_Generator
//
//  Created by Eduard Frigola on 03/08/16.
//
//

#include "parametersControl.h"

void parametersControl::setup(){
    
    
    //DatGui
    datGui = new ofxDatGui();
    datGui->addHeader();
    datGui->setPosition(ofxDatGuiAnchor::TOP_LEFT);
    //PHASPR
    datGui->addSlider(phasorParams.getFloat("BPM"));// bpm_Param.set("BPM", 60, 30, 180));
    datGui->addSlider(phasorParams.getInt("Beats Div"));
    datGui->addSlider(phasorParams.getInt("Beats Mult"));
    datGui->addSlider(phasorParams.getInt("Quantization"));
    datGui->addSlider(phasorParams.getFloat("Initial phase"))->setPrecision(2);
    datGui->addButton("Reset Phase");
    datGui->addToggle("Loop")->setEnabled(true);
    
    //OSCILATOR
    datGui->addBreak();
    datGui->addLabel("Oscilator");
    datGui->addSlider(oscilatorParams.getFloat("n Waves"));
    datGui->addSlider(oscilatorParams.getFloat("Phase offset"));
    datGui->addToggle("Invert")->setChecked(false);
    datGui->addSlider(oscilatorParams.getInt("Symmetry"));
    datGui->addSlider(oscilatorParams.getInt("Index Offset"));
    datGui->addSlider(oscilatorParams.getInt("Index Quantization"));
    datGui->addSlider(oscilatorParams.getFloat("Combination"));
    datGui->addSlider(oscilatorParams.getInt("Modulo"));
    datGui->addBreak();
    datGui->addLabel("Multipliers");
    datGui->addSlider(oscilatorParams.getFloat("Random addition"));
    datGui->addSlider(oscilatorParams.getFloat("Quantization"));
    datGui->addSlider(oscilatorParams.getFloat("Scale"));
    datGui->addSlider(oscilatorParams.getFloat("Offset"));
    datGui->addSlider(oscilatorParams.getInt("Pow"));
    datGui->addSlider(oscilatorParams.getFloat("Square PWM"));
    datGui->addDropdown("Wave Select", {"sin", "cos", "tri", "square", "saw", "inverted saw", "rand1", "rand2"});
//
    datGui->onButtonEvent(this, &parametersControl::onGuiButtonEvent);
    datGui->onToggleEvent(this, &parametersControl::onGuiToggleEvent);
    datGui->onDropdownEvent(this, &parametersControl::onGuiDropdownEvent);
}


void parametersControl::onGuiButtonEvent(ofxDatGuiButtonEvent e){
        if(e.target->getName() == "Reset Phase")
            phasorParams.getBool("Reset Phase") = true;
    
}
void parametersControl::onGuiToggleEvent(ofxDatGuiToggleEvent e){
    if(e.target->getName() == "Loop")
        phasorParams.getBool("Loop") = e.target->getChecked();
    if(e.target->getName() == "Invert")
        oscilatorParams.getBool("Invert") = e.target->getChecked();
}

void parametersControl::onGuiDropdownEvent(ofxDatGuiDropdownEvent e){
    if(e.target->getName() == "Wave Select")
        oscilatorParams.getInt("Wave Select") = (e.child);
}