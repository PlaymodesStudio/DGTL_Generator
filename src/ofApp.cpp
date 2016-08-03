#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(40);
    
    pixelNum = PIXEL_X_BAR;
    singleGenerator.setup();
    singleGenerator.setIndexCount(pixelNum);
    delayControler.setup();
    delayControler.setIndexCount(NUM_BARS);
    
//    infoVec.reserve(pixelNum);
    infoVec.resize(pixelNum, 0);
    
    syphonServer.setName("DGTL_Gen");
    
    pixelContent.allocate(PIXEL_X_BAR, NUM_BARS, GL_RGB);
    pixelContent.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    phasor.setup();
    
    gui = new ofxDatGui();
    gui->addHeader();
    gui->setPosition(0, 200);
    gui->addLabel("Main Config");
    gui->addSlider("pixelNum", 1, PIXEL_X_BAR, 432)->setPrecision(0);
    gui->addSlider(delay_frames.set("Delay", 1, 0, 30));
    gui->onSliderEvent(this, &ofApp::onGuiSliderEvent);
    gui->onButtonEvent(this, &ofApp::onGuiButtonEvent);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < pixelNum ; i++){
        infoVec[i] = singleGenerator.computeFunc(phasor.getPhasor(), i);
        //cout<< i << endl;
    }
    infoVec_Buffer.push_back(infoVec);
    
    //cout<<infoVec_Buffer.size()<<endl;
    //cout<<endl;
    
    pixelContent.begin();
    
    ofSetColor(0);
    //ofSetColor(infoVec[i]*255);
    for(int j = 0 ; j < pixelContent.getHeight() ; j++){
        int delayIndex = delay_frames*(delayControler.computeFunc(j));
        while( infoVec_Buffer.size() <= delayIndex) delayIndex--;
        for (int i = 0; i < pixelContent.getWidth() ; i++){
            ofSetColor(infoVec_Buffer[delayIndex][i] * 255);
            ofDrawRectangle(i, j, 1, 1);
        }
    }
    
    while(infoVec_Buffer.size() > delay_frames*NUM_BARS)
        infoVec_Buffer.pop_front();
    
    pixelContent.end();
    syphonServer.publishTexture(&pixelContent.getTexture());
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    
    pixelContent.draw(0,0, ofGetWidth(), 5*ofGetHeight()/11);
    
    float wid = (float)ofGetWidth()/pixelNum;
    float hei = 5*ofGetHeight()/11;
    for(int i = 0; i < pixelNum; i++)
        ofDrawRectangle(i*wid, (1-infoVec[i])*hei+hei, wid, infoVec[i]*hei);
    
    
    ofDrawTriangle(0, ofGetHeight(), ofGetWidth(), ofGetHeight(), ofGetWidth(), 10*ofGetHeight()/11);
    ofSetColor(127);
    ofDrawRectangle((float)ofGetWidth() * phasor.getPhasor(), 10*ofGetHeight()/11, 5, ofGetHeight()/11);
    
    ofSetColor(255, 0,0);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, ofGetHeight()-20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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


void ofApp::onGuiSliderEvent(ofxDatGuiSliderEvent e){
    if(e.target->getName() == "Frequency")
        phasor.setFrequency(e.value);
    if(e.target->getName() == "pixelNum"){
        //change pixelNum val
        pixelNum = e.value;
        
        //update pixelNum in GenerativeFunc
        singleGenerator.setIndexCount(pixelNum);
        
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

void ofApp::onGuiButtonEvent(ofxDatGuiButtonEvent e){
    if(e.target->getName() == "Reset Phase")
        phasor.resetPhasor(gui->getSlider("Initial Phase")->getValue());
}
