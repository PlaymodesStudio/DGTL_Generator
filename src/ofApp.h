#pragma once

#include "ofMain.h"
#include "phasorClass.h"
#include "ofxSyphon.h"
#include "elementOscilator.h"
#include "delayControl.h"
#include "parametersControl.h"

static const int NUM_BARS = 11;
static const int PIXEL_X_BAR = 432;

#define MULTIPLE_OSC;

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
    
    
    int pixelNum;
    
    vector<float> infoVec;
    ofFbo pixelContent;
    
    
    ofxSyphonServer syphonServer;
    
    phasorClass phasor;
    elementOscilator singleGenerator;
#ifdef MULTIPLE_OSC
    elementOscilator singleGenerator2;
    vector<float>   infoVec2;
    parametersControl   paramsControl2;
#endif
    delayControl     delayControler;
    
    parametersControl paramsControl;
		
};
