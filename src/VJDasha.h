#pragma once

#include "ofMain.h"
#include "BaseSet.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

#define _USE_LIVE_VIDEO	
#define PORT 12345 // listen on port 12345
#define NUM_MSG_STRINGS 20

enum Scenes{
    DASHA_IDLE = 0,
    DASHA_SCENE2,
    DASHA_SCENE3
};


class VJDasha : public BaseSet {
public:
    
    void setup();
    void update();
    void draw();
    
    void mouseMoved(ofMouseEventArgs& mouse);
    void keyPressed(ofKeyEventArgs & key);
    
    void start();
    void pause();
    
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
    //ofSoundStream soundStream;

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
