//
//  VJIdleSet.c
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#include "VJIdleSet.h"

void VJIdleSet::setup(){
    isPlaying = false;
    title = "Idle";
    circleSize = 20;
}

void VJIdleSet::update(){
    
    circleSize = sin( ofGetElapsedTimef() ) * 30;
}

void VJIdleSet::draw(){
    ofSetColor(244,66,190);
    ofDrawEllipse( mouseX, ofGetHeight()/2, 50 + circleSize, 50 + circleSize);
}

void VJIdleSet::start(){
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJIdleSet::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJIdleSet::keyPressed);
    isPlaying = true;
    
    ofSetBackgroundColor(255);
}

void VJIdleSet::pause(){
    ofRemoveListener(ofEvents().mouseMoved, this, &VJIdleSet::mouseMoved);
    ofRemoveListener(ofEvents().keyPressed, this, &VJIdleSet::keyPressed);
    isPlaying = false;
}

void VJIdleSet::mouseMoved(ofMouseEventArgs & mouse){
    mouseX = mouse.x;
    mouseY = mouse.y;
}

void VJIdleSet::keyPressed(ofKeyEventArgs & keyboard){
    
    int key = keyboard.key;
     ofLog() << "key pressed: " << key;
    
    // don't use reserved keys : 0, D, A, K , E, S, I, Q, B
    if( key == ' '){
       
    }
}
