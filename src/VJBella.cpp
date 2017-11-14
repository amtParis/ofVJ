//
//  VJSanie.c
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#include "VJBella.h"

void VJSanie::setup(){
    isPlaying = false;
    title = "*airh horns* v-v-vj beLLAAAAA *air horns*";
    circleSize = 20;
}

void VJSanie::update(){
    
    circleSize = sin( ofGetElapsedTimef() ) * 30;
}

void VJSanie::draw(){
    //cout << "draw";
    ofSetColor(0,0,0);
    ofDrawEllipse( mouseX, ofGetHeight()/2, 50 + circleSize, 50 + circleSize);
}

void VJSanie::start(){
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJSanie::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJSanie::keyPressed);
    isPlaying = true;
    
    ofSetBackgroundColor(255);
}

void VJSanie::pause(){
    ofRemoveListener(ofEvents().mouseMoved, this, &VJSanie::mouseMoved);
    ofRemoveListener(ofEvents().keyPressed, this, &VJSanie::keyPressed);
    isPlaying = false;
}

void VJSanie::mouseMoved(ofMouseEventArgs & mouse){
    mouseX = mouse.x;
    mouseY = mouse.y;
}

void VJSanie::keyPressed(ofKeyEventArgs & keyboard){
    
    int key = keyboard.key;
    ofLog() << "key pressed: " << key;
    
    // don't use reserved keys : 0, D, A, K , E, S, I, Q, B
    if( key == ' '){
        
    }
}
