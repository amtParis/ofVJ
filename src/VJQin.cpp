//
//  VJIdleSet.c
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#include "VJQin.h"

void VJQin::setup(){
    gui.setup();
    shader.load("qinqin_data/shader.vert","qinqin_data/shader.frag");
    
    fftFile.setMirrorData(false);
    fftFile.setup();
    
    //ofLoadImage(meshTexture, "texture.jpg");
    music.load("qinqin_data/music.mp3");
    music.setLoop(true);
    
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofBackground(100);
    
    sphere.setRadius( 100 );
    currentState=VERT;
    meshes.push_back(sphere.getMesh());
    //--------------------------------------------------------------
    fftFile.setup();
    
    //--------------------------------------------------------------
    string guiPath = "audio.xml";
    meshIndex = 0;
    // gui.setup("audio", guiPath, 20, 20);
    bUseAudioInput = true;
    audioPeakDecay = 0.915;
    audioMaxDecay = 0.995;
    audioMirror = true;
    gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.loadFromFile(guiPath);
}

void VJQin::update(){

    fftFile.setPeakDecay(audioPeakDecay);
    fftFile.setMaxDecay(audioMaxDecay);
    fftFile.setMirrorData(audioMirror);
    fftFile.update();
    
    
    //---------------------------------------------------------- dispacing mesh using audio.
    ofMesh & meshOriginal = meshes[meshIndex];
    meshWarped = meshOriginal;
    
    if(bUseAudioInput == false) {
        return;
    }
    
    vector<ofVec3f> & vertsOriginal = meshOriginal.getVertices();
    vector<ofVec3f> & vertsWarped = meshWarped.getVertices();
    int numOfVerts = meshOriginal.getNumVertices();
    
    audioData = new float[numOfVerts];
    fftFile.getFftPeakData(audioData, numOfVerts);
    
    float meshDisplacement = 20;
    
    for(int i=0; i<numOfVerts; i++) {
        audioValue = audioData[i];
        ofVec3f & vertOriginal = vertsOriginal[i];
        ofVec3f & vertWarped = vertsWarped[i];
        exportobj.addVertex(vertsWarped[i]);
        ofVec3f direction = vertOriginal.getNormalized();
        vertWarped = vertOriginal + direction * meshDisplacement * audioValue;
    }
}

void VJQin::draw(){
    ofSetBackgroundColor(0);
    //----------------------------------------------------------
    gui.draw();
    
    //----------------------------------------------------------
    ofEnableDepthTest();
    
    float dist = 400;
    camera.setDistance(dist);
    camera.begin();
    
    shader.begin();
    
    shader.setUniform1f("peak", audioValue);
    shader.setUniform1f("change", ofGetElapsedTimef());
    shader.setUniform1f("time", ofGetElapsedTimef());
    ofSetColor(color);
    //  ofSetColor(ofColor::white);
    //sphere.draw();
    //ofSetColor(ofColor::white);
    if(currentState==VERT){
        ofSetColor(ofColor::white);
        sphere.drawVertices();}
    if(currentState==wFRAME)
        sphere.drawWireframe();
    if(currentState==SURFACE)
        sphere.draw();
    
    shader.end();
    camera.end();
    
    ofDisableDepthTest();
}

void VJQin::start(){
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJQin::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJQin::keyPressed);
    isPlaying = true;
    music.play();
    ofSetBackgroundColor(255);
}

void VJQin::pause(){
    ofRemoveListener(ofEvents().mouseMoved, this, &VJQin::mouseMoved);
    ofRemoveListener(ofEvents().keyPressed, this, &VJQin::keyPressed);
    isPlaying = false;
     music.stop();
}

void VJQin::mouseMoved(ofMouseEventArgs & mouse){
    mouseX = mouse.x;
    mouseY = mouse.y;
}


void VJQin::keyPressed(ofKeyEventArgs & keyboard){
    
    // use key press to change scenes and make any operations that
    // only need to happen on change (not update or draw )
    int key = keyboard.key;
    switch(key){
        case '1':
            currentState = VERT;
            break;
        case '2':
            currentState = wFRAME;
            break;
        case '3':
            currentState=SURFACE;
            break;
        case '4':
            exportobj.save("new.ply");
    }

     ofLog() << "key pressed: " << key;
    
    // don't use reserved keys : 0, D, A, K , E, S, I, Q, B
    if( key == ' '){
       
    }
}
