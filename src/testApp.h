#pragma once


#include "ofMain.h"
#include "ofxFontStash.h"
#include "ofxNetwork.h"
#include "ofxOsc.h"
#include "ofxSyphon.h"
#include "ACSentence.h"
#include "ACSentenceManager.h"
#include "ofxXmlSettings.h"

#define PORT 12345
#define NUM_MSG_STRINGS 20

//comment this line to ignore "ofxTimeMeasurements" calls
//enabling it requires the ofxTimeMeasurements addon
//https://github.com/armadillu/ofxTimeMeasurements
//#define MEASURE_PERFORMANCE

#ifdef MEASURE_PERFORMANCE
#include "ofxTimeMeasurements.h"
#else
#define TIME_SAMPLE_START ;
#define TIME_SAMPLE_STOP ;
#define TIME_SAMPLE_DRAW_BOTTOM_RIGHT() ;
#endif


class testApp : public ofBaseApp{

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void drawPoint(float x, float y);
        ofxTCPServer TCP;

        ofxFontStash font;
        ofxFontStash unicodeFont;
        vector <string> msgLines;
        vector <string> storeText;
    
        vector <string> oneWords;
        ofxSyphonServer mainOutputSyphonServer;
        string curr_str;
    
        ACSentence testSentence;
        ACSentenceManager sentences;
    
        ofxOscReceiver receiver;
        int mouseX, mouseY;
        string mouseButtonState;
        
        ofxXmlSettings XML;
    
        ofMaterial material;
        ofLight cam1Light;
//        ofCamera cam1;
    ofEasyCam cam1;

        ofRectangle cam1ViewPort;
        ofIcoSpherePrimitive icoSphere;

};
