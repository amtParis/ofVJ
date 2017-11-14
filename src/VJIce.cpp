//
//  VJIce.c
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#include "VJIce.h"

void VJIce::setup(){
    isPlaying = false;
    title = "VJ Ice";
    circleSize = 20;
}

void VJIce::update(){
    
    circleSize = sin( ofGetElapsedTimef() ) * 30;
}

void VJIce::draw(){
    //cout << "draw";
    ofSetColor(244,200,190);
    ofDrawEllipse( mouseX, ofGetHeight()/2, 80 + circleSize, 50 + circleSize);
}

void VJIce::start(){
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJIce::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJIce::keyPressed);
    isPlaying = true;
    
    ofSetBackgroundColor(255,255,0);
}

void VJIce::pause(){
    ofRemoveListener(ofEvents().mouseMoved, this, &VJIce::mouseMoved);
    ofRemoveListener(ofEvents().keyPressed, this, &VJIce::keyPressed);
    isPlaying = false;
}

void VJIce::mouseMoved(ofMouseEventArgs & mouse){
    mouseX = mouse.x;
    mouseY = mouse.y;
}

void VJIce::keyPressed(ofKeyEventArgs & keyboard){
    
    int key = keyboard.key;
     ofLog() << "key pressed: " << key;
    
    // don't use reserved keys : 0, D, A, K , E, S, I, Q, B
    if( key == ' '){
       
    }
}
