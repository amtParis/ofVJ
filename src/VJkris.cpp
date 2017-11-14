//
//  VJkris.c
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#include "VJkris.h"

void VJkris::setup(){
    isPlaying = false;
    title = "Idle";
    circleSize = 20;
}

void VJkris::update(){
    
    circleSize = sin( ofGetElapsedTimef() ) * 30;
}

void VJkris::draw(){
    //cout << "draw";
    ofSetColor(51, 63, 190);
    ofDrawEllipse( mouseX, ofGetHeight()/2, 50 + circleSize, 50 + circleSize);
}

void VJkris::start(){
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJkris::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJkris::keyPressed);
    isPlaying = true;
    
    ofSetBackgroundColor(255);
}

void VJkris::pause(){
    ofRemoveListener(ofEvents().mouseMoved, this, &VJkris::mouseMoved);
    ofRemoveListener(ofEvents().keyPressed, this, &VJkris::keyPressed);
    isPlaying = false;
}

void VJkris::mouseMoved(ofMouseEventArgs & mouse){
    mouseX = mouse.x;
    mouseY = mouse.y;
}

void VJkris::keyPressed(ofKeyEventArgs & keyboard){
    
    int key = keyboard.key;
     ofLog() << "key pressed: " << key;
    
    // don't use reserved keys : 0, D, A, K , E, S, I, Q, B
    if( key == ' '){
       
    }
}
