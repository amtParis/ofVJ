#pragma once

#include "BaseSet.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCV.h"
#include "ofxGui.h"

enum gameState{
    //check value with name instead of number, in this case it increases so play mode will be 1 and game over will be 2, these values will stay the same
    DEBUG = 0,
    PLAY_MODE,
    GAME_OVER
};
class VJAmanda: public BaseSet{
    
public:
    
    void setup();
    void update();
    void draw();
    void start();
    void pause();
    
    void mouseMoved(ofMouseEventArgs& mouse);
    void keyPressed(ofKeyEventArgs & keyboard);
    void audioIn(float * input, int bufferSize, int nChannels);
    
    // by default has vars: mouseX, mouseY, title
    
    // custom vars
    //use this to check current state or switch between states
    gameState currentState;
    
    //load + play videos
    ofVideoGrabber camera;
    
    //finding objects in the image (?)
    ofxCv::RunningBackground background;
    
    // Audio
    ofSoundPlayer music;
    float audioPan, audioPanMax;
    float avgSound;
    float* fftSmoothed;
    int nBandsToGet;
    
    ofxPanel gui;
    ofxFloatSlider scaleFreq;
    
    
    ofShader shader;
    ofImage img;
    ofPlanePrimitive plane;
    ofEasyCam cam;
        
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int     bufferCounter;
    int     drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    ofSoundStream soundStream;
    
    ofSpherePrimitive sphere;
    ofFbo fboSphere;
    
    
    ofSoundPlayer  soundPlayer;
    ofTrueTypeFont    font;
    float             synthPosition;
    
    
    ofShader shadercircle;
    ofVideoPlayer myPlayer;
};
