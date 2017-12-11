//
//  VJIce.c
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#include "VJIce.h"

void VJIce::setup(){
    isPlaying = false;
    title = "ICE";
    int bufferSize = 128;
    
    image.load("stars.jpg");
    image.resize(200, 200);
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter    = 0;
    drawCounter        = 0;
    smoothedVol     = 0.0;
    scaledVol        = 0.0;
    //soundStream.setup( 0, 2, 44100, bufferSize, 4);
    //soundStream.setInput(this);
    
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableColors();
    
    mesh.enableIndices();
    float intensityThreshold = 150.0;
    int w = image.getWidth();
    int h = image.getHeight();
    for (int x=0; x<w; ++x) {
        for (int y=0; y<h; ++y) {
            ofColor c = image.getColor(x, y);
            float intensity = c.getLightness();
            if (intensity >= intensityThreshold) {
                float saturation = c.getSaturation();
                float z = ofMap(saturation, 0, 255, -100, 100);
                ofVec3f pos(x*4, y*4, z);
                mesh.addVertex(pos);
                mesh.addColor(c);
            }
        }
    }
    float connectionDistance = 30;
    int numVerts = mesh.getNumVertices();
    for (int a=0; a<numVerts; ++a) {
        ofVec3f verta = mesh.getVertex(a);
        for (int b=a+1; b<numVerts; ++b) {
            ofVec3f vertb = mesh.getVertex(b);
            float distance = verta.distance(vertb);
            if (distance <= connectionDistance) {
                // In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
                // connected to form a line
                mesh.addIndex(a);
                mesh.addIndex(b);
            }
        }
    }
    ofSetFrameRate(60);
    
    // Some lines of code omitted for clarity, you should still
    // keep them in your local version
    
    for (int x=0; x<w; ++x) {
        for (int y=0; y<h; ++y) {
            ofColor c = image.getColor(x, y);
            float intensity = c.getLightness();
            if (intensity >= intensityThreshold) {
                float saturation = c.getSaturation();
                float z = ofMap(saturation, 0, 255, -100, 100);
                ofVec3f pos(x*4, y*4, z);
                mesh.addVertex(pos);
                meshCopy.addVertex(pos);
                mesh.addColor(c);
                
                // And add this line to your existing for loop:
                // It will create a ofVec3f with 3 random values, which
                // will allow us to move the x, y and z coordinates of
                // each vertex independently
                offsets.push_back(ofVec3f(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000)));
            }
        }
    }
}

void VJIce::update(){
    
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
    
    int numVerts = mesh.getNumVertices();
    for (int i=0; i<numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);
        
        float time = ofGetElapsedTimef();
        float timeScale = 50.0;
        float displacementScale = 0.75;
        ofVec3f timeOffsets = offsets[i];
        
        vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * scaledVol * 90.0f;
        vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * scaledVol * 90.0f;
        vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z)) * scaledVol * 90.0f;
        
        ofVec3f vertCopy = meshCopy.getVertex(i);
        float pct = .99;
        vert.x = pct*vert.x + (1-pct)*vertCopy.x;
        vert.y = pct*vert.y + (1-pct)*vertCopy.y;
        vert.z = pct*vert.z + (1-pct)*vertCopy.z;
        mesh.setVertex(i, vert);
        
    }
}

void VJIce::draw(){
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_LINEAR);
    easyCam.begin();
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/3, -ofGetHeight()/3);
    mesh.draw();
    ofPopMatrix();
    easyCam.end();
    
}

void VJIce::start(){
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJIce::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJIce::keyPressed);
    isPlaying = true;
    
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
void VJIce::audioIn(float * input, int bufferSize, int nChannels){
    
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
    
    bufferCounter++;
    
}

void VJIce::keyPressed(ofKeyEventArgs & keyboard){
    
    int key = keyboard.key;
     ofLog() << "key pressed: " << key;
    
    // don't use reserved keys : 0, D, A, K , E, S, I, Q, B
    if( key == ' '){
       
    }
}
