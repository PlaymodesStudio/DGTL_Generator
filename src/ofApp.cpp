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
    
    //Gui creation
    //DAT GUI
//    gui = new ofxDatGui();
//    gui->addHeader();
//    gui->setPosition(0, 200);
//    gui->addLabel("Main Config");
//    gui->addSlider("pixelNum", 1, PIXEL_X_BAR, 432)->setPrecision(0);
//    gui->addSlider(delay_frames.set("Delay", 1, 0, 30));
//    gui->onSliderEvent(this, &ofApp::onGuiSliderEvent);
    
    //ofxGui
    gui.setup("Main Gui");
    gui.setPosition(0, 200);
    gui.add(delay_frames.set("Delay", 1, 0, 30));
    
}

//--------------------------------------------------------------
void ofApp::update(){

    singleGenerator.computeFunc(infoVec.data(), phasor.getPhasor());
    
    
    
    delayControler.applyDelayToTexture(pixelContent, infoVec);
    

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
    
    gui.draw();
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
    if(e.target->getName() == "pixelNum"){
        //change pixelNum val
//        pixelNum = e.value;
//        
//        //update pixelNum in GenerativeFunc
//        singleGenerator.setIndexCount(pixelNum);
//        
//        //Change vector storing values size
//        infoVec.clear();
//        infoVec.resize(pixelNum);
//        
//        //Change horizontal slider max, and crop it if it get out of boundaries
//        auto sli = gui->getSlider("Horizontal Frequency");
//        sli->setMax(pixelNum);
//        if(sli->getValue() > pixelNum)
//            sli->setValue(pixelNum);
//        
//        
//        //Change FBO
//        pixelContent.allocate(pixelNum, NUM_BARS);
        
    }
}
