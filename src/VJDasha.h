#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

#define _USE_LIVE_VIDEO	
#define PORT 12345 // listen on port 12345
#define NUM_MSG_STRINGS 20

enum Scenes{
    IDLE,
    SCENE2,
    SCENE3
};


class ofApp : public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxOscReceiver receiver; 
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];

    float oscX = 0.0;
    float oscY = 0.0;
    ofShader shader;
    ofShader shader2;
    ofSoundPlayer  oceandeep;

    void audioIn(float * input, int bufferSize, int nChannels);
    
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int 	bufferCounter;
    int 	drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    ofPlanePrimitive plane;
    ofSpherePrimitive sphere;
    ofBoxPrimitive box;
    ofEasyCam cam;
    ofSoundStream soundStream;

    Scenes currentScene;
    ofxFloatSlider colorR;
    ofxFloatSlider colorG;
    ofxFloatSlider colorB;
    ofVideoGrabber 	vidGrabber;

    ofxPanel gui;
    
    ofxCvColorImage			colorImg;
    
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    
//    ofxCvContourFinder 	contourFinder;

    int 				threshold;
    bool				bLearnBakground;
    
};
