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
    
    ofxDatGuiLog::quiet();
    
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
    
    cout<<phasorParams.size()<<endl;
    
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
    
    
    //DELAY
    datGui->addBreak();
    datGui->addLabel("Delay");
    datGui->addSlider(delayParams.getInt("Delay"));
    datGui->addToggle("Invert ")->setChecked(false);
    datGui->addSlider(delayParams.getInt("Symmetry"));
    datGui->addSlider(delayParams.getFloat("Combination"));

    //Gui Events
    datGui->onButtonEvent(this, &parametersControl::onGuiButtonEvent);
    datGui->onToggleEvent(this, &parametersControl::onGuiToggleEvent);
    datGui->onDropdownEvent(this, &parametersControl::onGuiDropdownEvent);
    
    
    //add listerners for midi sending when parameter is changed
    ofAddListener(phasorParams.parameterChangedE(), this, &parametersControl::listenerFunction);
    ofAddListener(oscilatorParams.parameterChangedE(), this, &parametersControl::listenerFunction);
    ofAddListener(delayParams.parameterChangedE(), this, &parametersControl::listenerFunction);
    
    //OSC
    oscReceiver.setup(12345);
    
    savePreset(1);
    
}


void parametersControl::update(){
    while(oscReceiver.hasWaitingMessages()){
        ofxOscMessage m;
        oscReceiver.getNextMessage(m);
        
        vector<string> splitAddress = ofSplitString(m.getAddress(), "/");
        if(splitAddress[1] == "phasor"){
            ofAbstractParameter &absParam = phasorParams.get(splitAddress[2]);
            if(absParam.type() == typeid(ofParameter<float>).name())
                phasorParams.getFloat(splitAddress[2]) = m.getArgAsFloat(0);
            else if(absParam.type() == typeid(ofParameter<int>).name())
                phasorParams.getInt(splitAddress[2]) = m.getArgAsInt(0);
            else if(absParam.type() == typeid(ofParameter<bool>).name())
                phasorParams.getBool(splitAddress[2]) = m.getArgAsBool(0);
        }
        else if(splitAddress[1] == "delay"){
            ofAbstractParameter &absParam = delayParams.get(splitAddress[2]);
            if(absParam.type() == typeid(ofParameter<float>).name())
                delayParams.getFloat(splitAddress[2]) = m.getArgAsFloat(0);
            else if(absParam.type() == typeid(ofParameter<int>).name())
                delayParams.getInt(splitAddress[2]) = m.getArgAsInt(0);
            else if(absParam.type() == typeid(ofParameter<bool>).name())
                delayParams.getBool(splitAddress[2]) = m.getArgAsBool(0);
        }
        else if(splitAddress[1] == "oscillator"){
            ofAbstractParameter &absParam = oscilatorParams.get(splitAddress[2]);
            if(absParam.type() == typeid(ofParameter<float>).name())
                oscilatorParams.getFloat(splitAddress[2]) = m.getArgAsFloat(0);
            if(absParam.type() == typeid(ofParameter<int>).name())
                oscilatorParams.getInt(splitAddress[2]) = m.getArgAsInt(0);
            if(absParam.type() == typeid(ofParameter<bool>).name())
                oscilatorParams.getBool(splitAddress[2]) = m.getArgAsBool(0);
        }
    }
}


void parametersControl::savePreset(int presetNum){
    //xml.load("Preset_"+ofToString(presetNum)+".xml");
    xml.clear();
    
    //Root Element
    xml.addChild("PRESET");
    
    // now we set our current element so we're on the right
    // element, so when add new nodes, they are still inside
    //the root element
    xml.setTo("PRESET");
    
    for (int i = 0; i < 3 ; i++){
        ofParameterGroup groupParam;
        switch (i){
            case 0: groupParam = phasorParams; break;
            case 1: groupParam = oscilatorParams; break;
            case 2: groupParam = delayParams; break;
        }
        xml.addChild(groupParam.getName());
        xml.setTo(groupParam.getName());
        
        for (int j = 0; j < groupParam.size() ; j++){
            ofAbstractParameter &absParam = groupParam.get(j);
            if(absParam.type() == typeid(ofParameter<float>).name()){
                ofParameter<float> castedParam = absParam.cast<float>();
                xml.addValue(castedParam.getName(), castedParam.get());
            }
            if(absParam.type() == typeid(ofParameter<int>).name()){
                ofParameter<int> castedParam = absParam.cast<int>();
                xml.addValue(castedParam.getName(), castedParam.get());
            }
            if(absParam.type() == typeid(ofParameter<bool>).name()){
                ofParameter<bool> castedParam = absParam.cast<bool>();
                xml.addValue(castedParam.getName(), castedParam.get());
            }
        }
        xml.setToParent();
    }
    
    xml.save("Preset_"+ofToString(presetNum)+".xml");
}

void parametersControl::loadPreset(int presetNum){
    
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
    if(e.target->getName() == "Invert ")
        delayParams.getBool("Invert") = e.target->getChecked();
}

void parametersControl::onGuiDropdownEvent(ofxDatGuiDropdownEvent e){
    if(e.target->getName() == "Wave Select")
        oscilatorParams.getInt("Wave Select") = (e.child);
}


void parametersControl::listenerFunction(ofAbstractParameter& e){
    int position = 0;
    
    
    int normalizedVal = 0;
    if(e.type() == typeid(ofParameter<float>).name()){
        ofParameter<float> castedParam = e.cast<float>();
        normalizedVal = ofMap(castedParam, castedParam.getMin(), castedParam.getMax(), 0, 127);
        position = castedParam.getFirstParent().getPosition(e.getName());
        if(castedParam.getFirstParent().getName() == "oscillator")
            position += phasorParams.size();
        else if(castedParam.getFirstParent().getName() == "delay")
            position += phasorParams.size() + oscilatorParams.size();
    }
    else if(e.type() == typeid(ofParameter<int>).name()){
        ofParameter<int> castedParam = e.cast<int>();
        normalizedVal = ofMap(castedParam, castedParam.getMin(), castedParam.getMax(), 0, 127);
        position = castedParam.getFirstParent().getPosition(e.getName());
        if(castedParam.getFirstParent().getName() == "oscillator")
            position += phasorParams.size();
        else if(castedParam.getFirstParent().getName() == "delay")
            position += phasorParams.size() + oscilatorParams.size();
    }
    else if(e.type() == typeid(ofParameter<bool>).name()){
        ofParameter<bool> castedParam = e.cast<bool>();
        normalizedVal = castedParam ? 127 : 0;
        position = castedParam.getFirstParent().getPosition(e.getName());
        if(castedParam.getFirstParent().getName() == "oscillator")
            position += phasorParams.size();
        else if(castedParam.getFirstParent().getName() == "delay")
            position += phasorParams.size() + oscilatorParams.size();
    }
    
    cout<<"Para Change: "<< e.getName() << " |pos: " << position << " |val: " << e  << " |MIDI: " << normalizedVal << endl;
}