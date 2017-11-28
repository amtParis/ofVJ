//
//  VJFF.c
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#include "VJFF.h"

void VJFF::setup(){
    isPlaying = false;
    title = "Idle";
    circleSize = 20;
}

void VJFF::update(){
    
    circleSize = sin( ofGetElapsedTimef() ) * 30;
}

void VJFF::draw(){
    //cout << "draw";
    ofSetColor(18,79,64);
    ofDrawEllipse( mouseX, ofGetHeight()/2, 50 + circleSize, 50 + circleSize);
}

void VJFF::start(){
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJFF::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJFF::keyPressed);
    isPlaying = true;
    
    ofSetBackgroundColor(255);
}

void VJFF::pause(){
    ofRemoveListener(ofEvents().mouseMoved, this, &VJFF::mouseMoved);
    ofRemoveListener(ofEvents().keyPressed, this, &VJFF::keyPressed);
    isPlaying = false;
}

void VJFF::mouseMoved(ofMouseEventArgs & mouse){
    mouseX = mouse.x;
    mouseY = mouse.y;
}

void VJFF::keyPressed(ofKeyEventArgs & keyboard){
    
    int key = keyboard.key;
     ofLog() << "key pressed: " << key;
    
    // don't use reserved keys : 0, D, A, K , E, S, I, Q, B
    if( key == ' '){
       
    }
}
