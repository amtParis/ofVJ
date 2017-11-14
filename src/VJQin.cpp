//
//  VJIdleSet.c
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#include "VJQin.h"

void VJQin::setup(){
    isPlaying = false;
    title = "Idle";
    circleSize = 20;
}

void VJQin::update(){
    
    circleSize = sin( ofGetElapsedTimef() ) * 30;
}

void VJQin::draw(){
    ofSetColor(100,120,50);
    ofDrawEllipse( mouseX, ofGetHeight()/2, 50 + circleSize, 50 + circleSize);
}

void VJQin::start(){
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJQin::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJQin::keyPressed);
    isPlaying = true;
    
    ofSetBackgroundColor(255);
}

void VJQin::pause(){
    ofRemoveListener(ofEvents().mouseMoved, this, &VJQin::mouseMoved);
    ofRemoveListener(ofEvents().keyPressed, this, &VJQin::keyPressed);
    isPlaying = false;
}

void VJQin::mouseMoved(ofMouseEventArgs & mouse){
    mouseX = mouse.x;
    mouseY = mouse.y;
}

void VJQin::keyPressed(ofKeyEventArgs & keyboard){
    
    int key = keyboard.key;
     ofLog() << "key pressed: " << key;
    
    // don't use reserved keys : 0, D, A, K , E, S, I, Q, B
    if( key == ' '){
       
    }
}
