//
//  VJ DASHA
//  ofVJSet

#include "VJDasha.h"

void VJDasha::setup(){
    isPlaying = false;
    title = "VJ Dasha!!";
    circleSize = 20;
}

void VJDasha::update(){
    
    circleSize = sin( ofGetElapsedTimef() ) * 30;
}

void VJDasha::draw(){
    ofSetColor(244,0,0);
    ofDrawEllipse( mouseX, ofGetHeight()/2, 50 + circleSize, 50 + circleSize);
}

void VJDasha::start(){
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJDasha::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJDasha::keyPressed);
    isPlaying = true;
    
    ofSetBackgroundColor(255);
}

void VJDasha::pause(){
    ofRemoveListener(ofEvents().mouseMoved, this, &VJDasha::mouseMoved);
    ofRemoveListener(ofEvents().keyPressed, this, &VJDasha::keyPressed);
    isPlaying = false;
}

void VJDasha::mouseMoved(ofMouseEventArgs & mouse){
    mouseX = mouse.x;
    mouseY = mouse.y;
}

void VJDasha::keyPressed(ofKeyEventArgs & keyboard){
    
    int key = keyboard.key;
     ofLog() << "key pressed: " << key;
    
    // don't use reserved keys : 0, D, A, K , E, S, I, Q, B
    if( key == ' '){
       
    }
}
