#pragma once

#include "ofMain.h"
#include "phasorClass.h"
#include "ofxDatGui.h"
#include "ofxSyphon.h"
#include "elementOscilator.h"
#include "delayControl.h"

static const int NUM_BARS = 11;
static const int PIXEL_X_BAR = 432;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    void onGuiSliderEvent(ofxDatGuiSliderEvent e);
    void onGuiButtonEvent(ofxDatGuiButtonEvent e);
    
    
    int pixelNum;
    
    
    int count;
    vector<float> infoVec;
    deque<vector<float>> infoVec_Buffer;
    ofParameter<int> delay_frames;
    ofFbo pixelContent;
    phasorClass phasor;
    
    ofxDatGui* gui;
    ofxDatGuiWaveMonitor* plotter;
    
    ofParameter<float> freq, hFreq, powVal;
    
    ofxSyphonServer syphonServer;
    
    
    elementOscilator singleGenerator;
    delayControl        delayControler;
    
		
};
