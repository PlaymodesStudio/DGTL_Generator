#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    //Set the FrameRate to be 40, that is the frame rate of the Pixel Bars
    ofSetFrameRate(40);
    
    //Initialize our pixelNum var to have all the pixels in one bar
    pixelNum = PIXEL_X_BAR;
    
    //Setup the generator of waves and pass it the numbers of items it will have
    singleGenerator.setup();
    singleGenerator.setIndexCount(pixelNum);
    
    //Initialize the calculator of index modifications in delaying the info calulated by the singleGenerator
    delayControler.setup();
    delayControler.setIndexCount(NUM_BARS);
    
    //Initialize our vector that stores the information of the oscilators
    infoVec.resize(pixelNum, 0);
    
    //Initlize our syphon and specify the name
    syphonServer.setName("DGTL Generator");
    
    //Allocation of the texture, and modify to show correctly the discrete pixels
    pixelContent.allocate(PIXEL_X_BAR, NUM_BARS, GL_RGB);
    pixelContent.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
    //Setup of the phasor, wich controls the oscilator generator
    phasor.setup();
    
    
    //Paramters binding
    paramsControl.bindPhasorParams(phasor.getParameterGroup());
    paramsControl.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    //Phasor updates automatically at audio rate
    
    //Calculation of the oscilators for each element, with phasor info
    singleGenerator.computeFunc(infoVec.data(), phasor.getPhasor());
    
    //Fill the fbo with the information in infoVec, and delaying it and modifing with it's controls
    delayControler.applyDelayToTexture(pixelContent, infoVec);
    
    //Pass texture to syphon
    syphonServer.publishTexture(&pixelContent.getTexture());
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    
    //Draw the fbo
    pixelContent.draw(0,0, ofGetWidth(), 5*ofGetHeight()/11);
    
    //Draw the Bars
    float wid = (float)ofGetWidth()/pixelNum;
    float hei = 5*ofGetHeight()/11;
    for(int i = 0; i < pixelNum; i++)
        ofDrawRectangle(i*wid, (1-infoVec[i])*hei+hei, wid, infoVec[i]*hei);
    
    
    //draw the phasor evolution
    ofDrawTriangle(0, ofGetHeight(), ofGetWidth(), ofGetHeight(), ofGetWidth(), 10*ofGetHeight()/11);
    ofSetColor(127);
    ofDrawRectangle((float)ofGetWidth() * phasor.getPhasor(), 10*ofGetHeight()/11, 5, ofGetHeight()/11);
    
    //Draw the framerate
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
