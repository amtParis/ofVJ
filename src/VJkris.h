//
//  VJIdleSet.h
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#pragma once

#include "BaseSet.h"
#include "ofMain.h"
#include "ofxGui.h"
#include <math.h>

enum Scenez{
    IDLEZ,
    SKY_SCENE,
    SUN_SCENE,
    PHOTO
};

class VJkris: public BaseSet{
    
public:
    
    void setup();
    void update();
    void draw();
    void start();
    void pause();
    
    void mouseMoved(ofMouseEventArgs& mouse);
    void keyPressed(ofKeyEventArgs & key);
    
    // by default has vars: mouseX, mouseY, title
    
    // custom vars
    float circleSize;
    
    
    //shape?
    float r(float theta, float a, float b, float m, float n1, float n2, float n3);
    float t;
    
    ofxFloatSlider This;
    ofxFloatSlider That;
    ofxFloatSlider TheOther;
    
    //hide captions
    bool hidden;
    
    Scenez currentScene;
    string scenenumber;
    ofColor scenecolor;
    
    string fontname;
    ofTrueTypeFont font0;
    ofTrueTypeFont font1;
    ofTrueTypeFont font2;
    ofTrueTypeFont font3;
    ofTrueTypeFont font4;
    
    ofShader shader;
    ofShader shader1;
    ofShader shader2;
    
    
    // Audio
    ofSoundPlayer music;
    float audioPan, audioPanMax;
    float avgSound;
    float* fftSmoothed;
    int nBandsToGet;
    
    // Interpolated values
    float count;
    float roll;
    ofColor background;
    //ofColor rainbow;
    float hue;
    ofColor interp;
    float interpAmt;
    
    ofxFloatSlider red;
    ofxFloatSlider green;
    ofxFloatSlider blue;
    ofxPanel gui;
    
};
