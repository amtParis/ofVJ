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
    isDone = false;
    timeStarted = ofGetElapsedTimef();
    duration = 10.495;
    
    //--------------- audio in
    int bufferSize = 128;
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    smoothedVol     = 0.0;
    
    //--------------- set up particles
    for(int i = 0; i < 700; i++){
        particles.push_back(IdleParticle());
        particles[i].setup();
    }
    
    //--------------- set up font
    verdana30.load("verdana.ttf", 100, true, true);
    verdana30.setLetterSpacing(1.15);
    verdana30.setLineHeight(0);
    
    //--------------- set up names list
    string the_names[] = {"DASHA","AMANDA","ICE","BELLA","QINQIN","ERICA","SANIE","KRIS"};
    for(int i = 0; i < 8; i++){ allNames.push_back(the_names[i]); }
    currVj = 0;
    
    //--------------- set up fbo
    fbo.allocate(ofGetWidth(), ofGetHeight());
    plane.set(ofGetWidth(), ofGetHeight(), 50, 50);
    plane.mapTexCoordsFromTexture(fbo.getTexture());
    shader.load("idle_data/shaderIdle.vert","idle_data/shaderIdle.frag");
    
    //---------------  create noise image for shader
    int w = ofGetWidth();
    int h = ofGetHeight();
    img.allocate(ofGetWidth(), ofGetHeight(),OF_IMAGE_COLOR);
    
    ofPixels pixels = img.getPixels();
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            int i = x + y * w;
            pixels[i*3] = ofNoise(ofRandom(.05),x*.005,y*.005)*255;
            pixels[i*3+1] = pixels[i*3];
            pixels[i*3+2] = pixels[i*3];
        }
    }
    img.setFromPixels(pixels);
    
    cam.tilt(180);
    
}

void VJIdleSet::setupAttractors(string myName){
    vector<ofPoint> attractors = getAttractorsFromTitle(myName);
    for(int i = 0; i < particles.size(); i++){
        particles[i].attractPoints = attractors;
        particles[i].currentAttractor = ofRandom(0,attractors.size()-1);
    }
}

vector<ofPoint> VJIdleSet::getAttractorsFromTitle(string myName){
    
    float stringHeight = verdana30.stringHeight(myName);
    float stringWidth =  verdana30.stringWidth(myName);
    
    ofFbo tempFbo;
    tempFbo.allocate(ofGetWidth(), ofGetHeight());
    tempFbo.begin();
    ofBackground(0);
    ofSetColor(255);
    verdana30.drawString(myName, ofGetWidth()/2 - stringWidth/2,ofGetHeight()/2 + stringHeight/2);
    tempFbo.end();
    
    // get pixels
    ofPixels pixels;
    tempFbo.readToPixels(pixels);
    
    vector<ofPoint> pts;
    
    // loop through and get every 10th white point
    int i = 0;
    int w = ofGetWidth();
    for(int x = 0; x < ofGetWidth(); x+= 10){
        for(int y = 0; y < ofGetHeight(); y += 10){
            if( pixels.getColor(x, y).r > 0 ){
                pts.push_back(ofPoint(x,y) );
            }
        }
    }
    
    return pts;
    
}

void VJIdleSet::update(){
    
    for(int i = 0; i < particles.size(); i++) particles[i].update();
    
    if( ofGetElapsedTimef() - timeStarted > duration ) isDone = true;
}

void VJIdleSet::draw(){
    
    
    ofEnableAlphaBlending();
    
    fbo.begin();
    ofClear(255,255,255,1);
    ofSetColor(0);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(255,80);
    for(int i = 0; i < particles.size(); i++){
        ofFill();
        particles[i].draw();
        ofNoFill();
        particles[i].drawTrails();
    }
    fbo.end();
    fbo.draw(0,0);
    
    
    ofDisableAlphaBlending();
    cam.begin();
    fbo.getTexture().bind();
    shader.begin();
    //shader.setUniform1f("time", smoothedVol);
    shader.setUniform1f("time", (mouseX*.01));
    shader.setUniformTexture("tex1", img.getTexture(), 1);
    plane.draw();
    shader.end();
    fbo.getTexture().unbind();
    cam.end();
    
}

void VJIdleSet::start(){
    
    timeStarted = ofGetElapsedTimef();
    isDone = false;
    
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJIdleSet::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJIdleSet::keyPressed);
    isPlaying = true;
    
    ofSetBackgroundColor(255);
    
    if( title != "Idle" ){
        //soundPlayer.play();
        setupAttractors(title);
    }
}

void VJIdleSet::pause(){
    
    ofRemoveListener(ofEvents().mouseMoved, this, &VJIdleSet::mouseMoved);
    ofRemoveListener(ofEvents().keyPressed, this, &VJIdleSet::keyPressed);
    isPlaying = false;
    //soundPlayer.stop();
}

void VJIdleSet::mouseMoved(ofMouseEventArgs & mouse){
    mouseX = mouse.x;
    mouseY = mouse.y;
}

void VJIdleSet::keyPressed(ofKeyEventArgs & keyboard){
    
    int key = keyboard.key;
    ofLog() << "key pressed: " << key;
    
    shader.load("shaderIdle.vert","shaderIdle.frag");
    
    switch(key){
        case 'd': setupAttractors("DASHA"); break;
        case 'a': setupAttractors("AMANDA");break;
        case 'k': setupAttractors("KRIS");break;
        case 'q': setupAttractors("QINQIN");break;
        case 's': setupAttractors("SANIE");break;
        case 'i': setupAttractors("ICE");break;
        case 'b': setupAttractors("BELLA");break;
        case 'e': setupAttractors("ERICA");break;
    }
    // don't use reserved keys : 0, D, A, K , E, S, I, Q, B
    if( key == ' '){
        currVj++;
        int r = currVj % allNames.size();//ofRandom(0,allNames.size()-1);
        setupAttractors(allNames[r]);
    }
    
    ofHideCursor();
}

//--------------------------------------------------------------
void VJIdleSet::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]        = input[i*2]*0.5;
        right[i]    = input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    
}

