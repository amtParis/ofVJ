//
//  VJIdleSet.h
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#pragma once

#include "ofMain.h"

class BaseSet : public ofBaseSoundInput{
    
public:
    
    virtual void setup(){ title = ""; };
    virtual void update(){};
    virtual void draw(){};
    virtual void pause(){};
    virtual void start(){};
    
    virtual void mouseMoved(ofMouseEventArgs& mouse){};
    virtual void keyPressed(ofKeyEventArgs & key){};
   // virtual void audioIn(float * input, int bufferSize, int nChannels){};
    
    int mouseX, mouseY;
    bool isPlaying;
    string title;
    
    float duration;
    float timeStarted;
    bool isDone;
    
};
