//
//  VJIdleSet.h
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#pragma once

#include "BaseSet.h"
#include "IdleParticle.h"

class VJIdleSet: public BaseSet{
    
public:
    
    void setup();
    void update();
    void draw();
    void start();
    void pause();
    
    void mouseMoved(ofMouseEventArgs& mouse);
    void keyPressed(ofKeyEventArgs & key);
    
    // audio
    //ofSoundStream soundStream;
    void audioIn(float * input, int bufferSize, int nChannels);
    vector <float> left;
    vector <float> right;
    float smoothedVol;
    
    // particles methods
    void setupAttractors(string myName);
    vector<ofPoint> getAttractorsFromTitle(string myName);
    
    // particles
    vector<IdleParticle> particles;
    
    // vj names
    vector<string> allNames;
    int currVj;
    ofTrueTypeFont    verdana30;
    
    // fbo effects
    ofFbo fbo;
    ofShader shader;
    ofPlanePrimitive plane;
    ofEasyCam cam;
    ofImage img;
    bool isDone;
    
};
