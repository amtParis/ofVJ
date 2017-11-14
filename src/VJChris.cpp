//
//  VJChris.c
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#include "VJChris.h"

void VJChris::setup(){
    isPlaying = false;
    title = "VJ Chris!!";
    circleSize = 20;
}

void VJChris::update(){
    
    circleSize = sin( ofGetElapsedTimef() ) * 30;
}

void VJChris::draw(){
    ofSetColor(244,0,0);
    ofDrawEllipse( mouseX, ofGetHeight()/2, 50 + circleSize, 50 + circleSize);
}

void VJChris::start(){
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJChris::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJChris::keyPressed);
    isPlaying = true;
    
    ofSetBackgroundColor(255);
}

void VJChris::pause(){
    ofRemoveListener(ofEvents().mouseMoved, this, &VJChris::mouseMoved);
    ofRemoveListener(ofEvents().keyPressed, this, &VJChris::keyPressed);
    isPlaying = false;
}

void VJChris::mouseMoved(ofMouseEventArgs & mouse){
    mouseX = mouse.x;
    mouseY = mouse.y;
}

void VJChris::keyPressed(ofKeyEventArgs & keyboard){
    
    int key = keyboard.key;
     ofLog() << "key pressed: " << key;
    
    // don't use reserved keys : 0, D, A, K , E, S, I, Q, B
    if( key == ' '){
       
    }
}
