#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    
    pixelNum = PIXEL_X_BAR;
    
    infoVec.reserve(pixelNum);
    
    pixelContent.allocate(PIXEL_X_BAR, NUM_BARS, GL_RGB);
    phasor.setup();
    
    gui = new ofxDatGui();
    gui->addSlider(freq.set("Frequency", 1, 0, 10));
    gui->addSlider(hFreq.set("Horizontal Frequency", 0.5, 0, PIXEL_X_BAR+1));
    gui->addSlider("pixelNum", 1, PIXEL_X_BAR)->setPrecision(0);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
}

//--------------------------------------------------------------
void ofApp::update(){
    float w = phasor.getPhasor()*TWOPI;
    for (int i = 0; i < pixelNum ; i++){
        float k = i*hFreq/pixelNum;
        float val = sin(w+k);
        val /= 2;
        val += 0.5;
        infoVec[i] = val;
    }
    
    
    pixelContent.begin();
    for (int i = 0; i < pixelContent.getWidth() ; i++){
        ofSetColor(infoVec[i]*255);
        for(int j = 0 ; j < pixelContent.getHeight() ; j++){
            ofDrawRectangle(i, j, 1, 1);
        }
    }
    
    pixelContent.end();
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    pixelContent.draw(0,0, ofGetWidth(), ofGetHeight()/2);
    
    float wid = (float)ofGetWidth()/pixelNum;
    float hei = ofGetHeight()/2;
    for(int i = 0; i < pixelNum; i++){
        ofDrawRectangle(i*wid, infoVec[i]*hei+hei, wid, ofGetHeight()-infoVec[i]*hei);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    phasor.setFrequency(ofToInt(ofToString(key-)));
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void ofApp::onSliderEvent(ofxDatGuiSliderEvent e){
    if(e.target->getName() == "Frequency")
        phasor.setFrequency(e.value);
    if(e.target->getName() == "pixelNum"){
        //change pixelNum val
        pixelNum = e.value;
        //Change vector storing values size
        infoVec.clear();
        infoVec.reserve(pixelNum);
        
        //Change horizontal slider max, and crop it if it get out of boundaries
        auto sli = gui->getSlider("Horizontal Frequency");
        sli->setMax(pixelNum);
        if(sli->getValue() > pixelNum)
            sli->setValue(pixelNum);
        
        
        //Change FBO
        pixelContent.allocate(pixelNum, NUM_BARS);
        
    }
}
