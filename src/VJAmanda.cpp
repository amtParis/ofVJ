//
//  VJAmanda.cpp
//  ofVJ
//
//  Created by Amanda Lewis on 11/14/17.
//

#include "VJAmanda.h"



void VJAmanda::setup(){
    isPlaying = false;
    title = "Idle";
    circleSize = 20;
}

void VJAmanda::update(){
    
    circleSize = sin( ofGetElapsedTimef() ) * 30;
}

void VJAmanda::draw(){
    //cout << "draw";
    ofSetColor(0,0,255);
    ofDrawEllipse( mouseX, ofGetHeight()/2, 50 + circleSize, 50 + circleSize);
}

void VJAmanda::start(){
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJAmanda::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJAmanda::keyPressed);
    isPlaying = true;
    
    ofSetBackgroundColor(255);
}

void VJAmanda::pause(){
    ofRemoveListener(ofEvents().mouseMoved, this, &VJAmanda::mouseMoved);
    ofRemoveListener(ofEvents().keyPressed, this, &VJAmanda::keyPressed);
    isPlaying = false;
}

void VJAmanda::mouseMoved(ofMouseEventArgs & mouse){
    mouseX = mouse.x;
    mouseY = mouse.y;
}

void VJAmanda::keyPressed(ofKeyEventArgs & keyboard){
    
    int key = keyboard.key;
    ofLog() << "key pressed: " << key;
    
    // don't use reserved keys : 0, D, A, K , E, S, I, Q, B
    if( key == ' '){
        
    }
}
