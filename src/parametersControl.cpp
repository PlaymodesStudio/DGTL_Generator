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
    
    loadPreset(1);
    
    presetMatrix = datGui->addMatrix("Presets", 24, true);
    presetMatrix->setRadioMode(true);
    presetMatrix->setOpacity(.75);
    
    presetMatrix->onMatrixEvent(this, &parametersControl::onGuiMatrixEvent);
    
    
    
    //MIDI
    ofxMidiOut::listPorts();
    midiOut.openPort("BCF2000");
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
    
    //Iterate for all the three parameterGroups
    for (int i = 0; i < 3 ; i++){
        
        //get the grup in each iteration
        ofParameterGroup groupParam;
        switch (i){
            case 0: groupParam = phasorParams; break;
            case 1: groupParam = oscilatorParams; break;
            case 2: groupParam = delayParams; break;
        }
        
        //set XML structure to parameterGroup
        xml.addChild(groupParam.getName());
        xml.setTo(groupParam.getName());
        
        //Iterate for all parameters in parametergroup and look for the type of the parameter
        for (int j = 0; j < groupParam.size() ; j++){
            ofAbstractParameter &absParam = groupParam.get(j);
            if(absParam.type() == typeid(ofParameter<float>).name()){
                //Cast it
                ofParameter<float> castedParam = absParam.cast<float>();
                
                //Replace blank spaces with underscore
                string noSpaces = castedParam.getName();
                ofStringReplace(noSpaces, " ", "_");
                
                //add the value of that parameter into xml
                xml.addValue(noSpaces, castedParam.get());
            }
            if(absParam.type() == typeid(ofParameter<int>).name()){
                ofParameter<int> castedParam = absParam.cast<int>();
                string noSpaces = castedParam.getName();
                ofStringReplace(noSpaces, " ", "_");
                xml.addValue(noSpaces, castedParam.get());
            }
            if(absParam.type() == typeid(ofParameter<bool>).name()){
                ofParameter<bool> castedParam = absParam.cast<bool>();
                string noSpaces = castedParam.getName();
                ofStringReplace(noSpaces, " ", "_");
                xml.addValue(noSpaces, castedParam.get());
            }
        }
        xml.setToParent();
    }
    
    xml.save("Preset_"+ofToString(presetNum)+".xml");
}

void parametersControl::loadPreset(int presetNum){
    //Test if there is no problem with the file
    if(!xml.load("Preset_"+ofToString(presetNum)+".xml"))
        return;
    
    //Iterate for all the three parameterGroups
    for (int i = 0; i < 3 ; i++){
        
        //get the grup in each iteration
        ofParameterGroup groupParam;
        switch (i){
            case 0: groupParam = phasorParams; break;
            case 1: groupParam = oscilatorParams; break;
            case 2: groupParam = delayParams; break;
        }
        
        //Put xml in the place of the parametergroup
        if(xml.exists(groupParam.getName())){
            xml.setTo(groupParam.getName());
            
            //Iterate for all parameters in parametergroup and look for the type of the parameter
            for (int j = 0; j < groupParam.size() ; j++){
                ofAbstractParameter &absParam = groupParam.get(j);
                if(absParam.type() == typeid(ofParameter<float>).name()){
                    //Cast it
                    ofParameter<float> castedParam = absParam.cast<float>();
                    
                    //Replace blank spaces with underscore
                    string noSpaces = castedParam.getName();
                    ofStringReplace(noSpaces, " ", "_");
                    
                    //get the value of that parameter
                    castedParam = xml.getValue(noSpaces, castedParam.get());
                }
                if(absParam.type() == typeid(ofParameter<int>).name()){
                    ofParameter<int> castedParam = absParam.cast<int>();
                    string noSpaces = castedParam.getName();
                    ofStringReplace(noSpaces, " ", "_");
                    castedParam = xml.getValue(noSpaces, castedParam.get());
                }
                if(absParam.type() == typeid(ofParameter<bool>).name()){
                    ofParameter<bool> castedParam = absParam.cast<bool>();
                    string noSpaces = castedParam.getName();
                    ofStringReplace(noSpaces, " ", "_");
                    castedParam = xml.getValue(noSpaces, castedParam.get());
                }
            }
            //Jump one label before in xml structure
            xml.setToParent();
        }
    }
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

void parametersControl::onGuiMatrixEvent(ofxDatGuiMatrixEvent e){
    if(ofGetKeyPressed(OF_KEY_SHIFT))
        savePreset(e.child+1);
    else
        loadPreset(e.child+1);
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
    
    midiOut.sendControlChange(1, position, normalizedVal);
    
    cout<<"Para Change: "<< e.getName() << " |pos: " << position << " |val: " << e  << " |MIDI: " << normalizedVal << endl;
}