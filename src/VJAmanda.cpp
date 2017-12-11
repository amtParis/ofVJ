//
//  VJAmanda.cpp
//  ofVJ
//
//  Created by Amanda Lewis on 11/14/17.
//

#include "VJAmanda.h"


using namespace ofxCv;
using namespace cv;


void VJAmanda::setup(){
    title = "AMANDA";
    currentState = DEBUG;
    
    
    shadercircle.load("amanda_data/shadercircle.vert","amanda_data/shadercircle.frag");
    myPlayer.loadMovie("amanda_data/dance.mp4");
    
    //sphere scene
    shader.load("amanda_data/shader.vert","amanda_data/shader.frag");
    
    img.load("amanda_data/club.jpg");
    img.resize(50, 50);
    img.update();
    
    sphere.setRadius(80);
    sphere.setResolution(40);
    sphere.mapTexCoordsFromTexture(img.getTexture());
    //SOUND
    ofSetVerticalSync(true);
    
    //soundStream.printDeviceList();
    
    int bufferSize = 256;
    
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter = 0;
    drawCounter = 0;
    smoothedVol = 0.0;
    scaledVol = 0.0;
    
//    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
    
    //play song
    music.loadSound("amanda_data/marcus_kellis_theme.mp3");
    music.setVolume(1.0f);
   
    music.setLoop(true);
    
    ofSetVerticalSync(true);
    float check = avgSound;
    
    gui.setup();
    gui.add(scaleFreq.setup("frequency", .5, 0, 1));
}

void VJAmanda::update(){
    
    myPlayer.update();
    camera.update();
    //ofSoundUpdate();
    ofSetFrameRate(scaleFreq * 15);
    
    //scale vol up to 0-1 range
    scaledVol = ofMap(smoothedVol*scaleFreq, 0.0, 0.17, 0.0, 1.0, true);
    
    volHistory.push_back(scaledVol);
    
    if (volHistory.size() >= 400) {
        volHistory.erase(volHistory.begin(), volHistory.begin() + 1);
    }
}

void VJAmanda::draw(){
    if(currentState == DEBUG){
        ofBackground(0, 0, 0);
        ofSetColor(255);
        camera.draw(ofRandom(0,ofGetWidth()-100),ofRandom(0,ofGetHeight()-100));

    }else if(currentState == PLAY_MODE){
        ofSetFrameRate(30);
        
        ofSetBackgroundColor(0);
        fboSphere.begin();
        ofEnableDepthTest();
        img.bind();
        cam.begin();
        shader.begin();
        shader.setUniform1f("time", smoothedVol);
        sphere.drawWireframe();
        shader.end();
        cam.end();
        ofDisableDepthTest();
        fboSphere.end();
        
    }else if(currentState == GAME_OVER){
        ofBackground(0);
        //        danceimage.draw(0,0);
        
        shadercircle.begin();
        
        shadercircle.setUniform2f("u_mouse", mouseX, ofGetHeight()-mouseY);
        shadercircle.setUniform2f("u_resolution",ofGetWidth(), ofGetHeight());
        //        danceimage.draw(0,0);
        myPlayer.draw(0,0,ofGetWidth(), ofGetHeight());
        myPlayer.play();
        
        shadercircle.end();
    }
    
    glDisable(GL_DEPTH_TEST);
    gui.draw();
}

void VJAmanda::start(){
    camera.setup(640,480);
     music.play();
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJAmanda::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJAmanda::keyPressed);
    isPlaying = true;
    
//    ofSetBackgroundColor(255);
}

void VJAmanda::pause(){
    camera.close();
     music.stop();
    ofSetFrameRate(60);
    ofRemoveListener(ofEvents().mouseMoved, this, &VJAmanda::mouseMoved);
    ofRemoveListener(ofEvents().keyPressed, this, &VJAmanda::keyPressed);
    isPlaying = false;
}

void VJAmanda::mouseMoved(ofMouseEventArgs & mouse){
    mouseX = mouse.x;
    mouseY = mouse.y;
}

void VJAmanda::keyPressed(ofKeyEventArgs & keyboard){
    
    shader.load("amanda_data/shader.vert","amanda_data/shader.frag");
    shadercircle.load("amanda_data/shadercircle.vert","amanda_data/shadercircle.frag");
    
    // use key press to change scenes and make any operations that
    // only need to happen on change (not update or draw )
    int key = keyboard.key;
    switch(key){
        case 'f':
            ofToggleFullscreen();
            break;
        case '1':
            currentState = DEBUG;
            break;
        case '2':
            currentState = PLAY_MODE;
            break;
        case '3':
            currentState = GAME_OVER;
            break;
    }
}

void VJAmanda::audioIn(float * input, int bufferSize, int nChannels) {
        
        float curVol = 0.0;
        
        // samples are "interleaved"
        int numCounted = 0;
        
        //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
        for (int i = 0; i < bufferSize; i++) {
            left[i] = input[i * 2] * 0.5;
            right[i] = input[i * 2 + 1] * 0.5;
            
            curVol += left[i] * left[i];
            curVol += right[i] * right[i];
            numCounted += 2;
        }
        
        //this is how we get the mean of rms :)
        curVol /= (float)numCounted;
        
        // this is how we get the root of rms :)
        curVol = sqrt(curVol);
        
        smoothedVol *= 0.93;
        smoothedVol += 0.07 * curVol;
        
        bufferCounter++;
        
    }
