//
//  VJBella.c
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#include "VJBella.h"

void VJBella::setup(){
    isPlaying = false;
    title = "BELLA";//*airh horns* v-v-vj beLLAAAAA *air horns*";
    circleSize = 10;
}

void VJBella::update(){
    
    circleSize = sin( ofGetElapsedTimef() ) * 30;
}

void VJBella::draw(){
    //cout << "draw";
    ofSetColor(240,240,240);
    ofDrawEllipse( mouseX, ofGetHeight()/2, 50 + circleSize, 50 + circleSize);
    ofSetColor(50, 50, 50);
    ofDrawRectangle(10, 10, ofGetWidth()/2, mouseY);
}

void VJBella::start(){
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJBella::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJBella::keyPressed);
    isPlaying = true;
    
    ofSetBackgroundColor(140, 0, 230);
}

void VJBella::pause(){
    ofRemoveListener(ofEvents().mouseMoved, this, &VJBella::mouseMoved);
    ofRemoveListener(ofEvents().keyPressed, this, &VJBella::keyPressed);
    isPlaying = false;
}

void VJBella::mouseMoved(ofMouseEventArgs & mouse){
    mouseX = mouse.x;
    mouseY = mouse.y;
}

void VJBella::keyPressed(ofKeyEventArgs & keyboard){
    
    int key = keyboard.key;
    ofLog() << "key pressed: " << key;
    
    // don't use reserved keys : 0, D, A, K , E, S, I, Q, B
    if( key == ' '){
        
    }
}
