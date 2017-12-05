//
//  VJQin.h
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#pragma once

#include "BaseSet.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxFFTFile.h"
#include "ofxFFTBase.h"

enum gameStateQin{
    VERT,
    wFRAME,
    SURFACE
};

class VJQin: public BaseSet{
    
public:
    
    void setup();
    void update();
    void draw();
    void start();
    void pause();
    
    void mouseMoved(ofMouseEventArgs& mouse);
    void keyPressed(ofKeyEventArgs & key);
    
    // by default has vars: mouseX, mouseY, title
    
    // custom vars
    ofxPanel gui;
    int meshIndex;
    float audioPeakDecay;
    bool bUseAudioInput;
    float audioMaxDecay;
    bool audioMirror;
    
    // ofxFFTLive fftLive;
    ofxFFTFile fftFile;
    
    ofSoundPlayer music;
    
    ofEasyCam camera;
    
    ofTexture meshTexture;
    vector<ofMesh> meshes;
    ofMesh meshWarped;
    ofMesh exportobj;
    
    ofShader shader;
    
    float * audioData;
    
    float audioValue;
    
    ofSpherePrimitive sphere;
    ofxColorSlider color;
    
    gameStateQin currentState;
};
