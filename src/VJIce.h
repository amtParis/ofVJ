//
//  VJIdleSet.h
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#pragma once

#include "BaseSet.h"

class VJIce: public BaseSet{
    
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
    ofImage image;
    ofMesh mesh;
    ofMesh meshCopy;
    ofEasyCam easyCam;
    
    vector<ofVec3f> offsets;
    
    void audioIn(float * input, int bufferSize, int nChannels);
    
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int     bufferCounter;
    int     drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    //ofSoundStream soundStream;
    
};
