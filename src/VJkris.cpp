//
//  VJkris.c
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#include "VJkris.h"

void VJkris::setup(){
    isPlaying = false;
    title = "Kris";
    
    //my stuffffffffff
    shader.load("","data_kris/shader.frag");
    shader2.load("","data_kris/shader2.frag");
    shader1.load("","data_kris/shader1.frag");
    
    currentScene = PHOTO;
    scenenumber = "1";
    scenecolor.r=134;
    scenecolor.g=204;
    scenecolor.b=198;
    //fontname = "King-Basil-Lite.ttf";
    
    
    font0.load("data_kris/King-Basil-Lite.ttf", 30);
    
    font1.load("data_kris/King-Basil-Lite.ttf", 30);
    font2.load("data_kris/Hangar Nine.otf", 30);
    font3.load("data_kris/Heroic.ttf", 30);
    font4.load("data_kris/zorque.ttf", 30);
    
    // init of incrementing values
    audioPan = 0.5f;
    interpAmt = 0.0f;
    hue = background.getHue();
    
    // load song
    music.loadSound("data_kris/song.mp3");
    music.setVolume(0.0f);
    music.play();
    music.setLoop(true);
    
    // FFT initialization
    fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
    }
    nBandsToGet = 128;
    
    gui.setup();
    gui.add(red.setup("red", 0, 0, 255));
    gui.add(green.setup("green", 0, 0, 255));
    gui.add(blue.setup("blue", 0, 0, 255));
    
    gui.add(This.setup("this", 6, 0, 20));
    gui.add(That.setup("that", 2, 0, 13));
    gui.add(TheOther.setup("the other", 2, 0, 10));
    
    //shape
    float t = 0.1;
    
    bool hidden = false;
}

void VJkris::update(){
    
    //added
    // interpolate speaker direction
    audioPanMax = 0.5f;
    if (audioPan <= audioPanMax)
        audioPan += 0.001f;
    music.setPan(audioPan);
    
    // interpolate between background colours
    if (interpAmt <= 1.0f)
        interpAmt += 0.01f;
    background.lerp(interp, interpAmt);
    
    // update the sound playing system:
    ofSoundUpdate();
    float* val = ofSoundGetSpectrum(nBandsToGet);
    avgSound = 0;
    
    // smooth fft and calc average volume
    for (int i = 0;i < nBandsToGet; i++){
        fftSmoothed[i] *= 0.96f;
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
        avgSound += fftSmoothed[i];
    }
    
    
    avgSound /= nBandsToGet;
    
    if(currentScene == PHOTO){
        // updates for sun scene
        music.setVolume(0.0f);
        font0.load("kris_data/zorque.ttf", 30);
        
        
    }else if(currentScene == SKY_SCENE){
        // updates for sky scene
        music.setVolume(0.0f);
        font0.load("data_kris/Hangar Nine.otf", 30);
    }else if(currentScene == SUN_SCENE ){
        // updates for sun scene
        music.setVolume(1.0f);
        font0.load("data_kris/Heroic.ttf", 30);
    }else if(currentScene == IDLEZ ){
        // updates for idle scene
        music.setVolume(0.0f);
        font0.load("kris_data/King-Basil-Lite.ttf", 30);
        t = t + 0.1;
    }
    
}

void VJkris::draw(){
    // draws for each scene:
    
    if(currentScene == IDLEZ){
        scenenumber = "4";
        ofBackground(red, green, blue);
        ofSetColor(255);
        //ofDrawBitmapString("Idle mode: Press keys 1-4 to change.", 100, 100);
        if(!hidden){
            font1.drawString("Press keys 1-4 to change.", 100, 100);
        }
        
        
        //how do i move this down?!?!?!
        gui.draw();
        
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        
        
        //shape
        ofBeginShape();
        for (float theta = 0; theta <= 2 * PI; theta +=0.1){
            float rad = r(theta, TheOther, That, This, 1, sin(t) * 0.5 + 0.5, cos(t) * 0.5 + 0.5);
            float x = rad * cos(theta) * 50;
            float y = rad * sin(theta) * 50;
            ofVertex(x,y);
            
        }
        
        
        ofEndShape();
        
        scenecolor.r=134;
        scenecolor.g=204;
        scenecolor.b=198;
        
    }else if(currentScene == SKY_SCENE){
        scenenumber = "2";
        ofBackgroundGradient( ofColor(66, 229, 244), ofColor(255,255,255) );
        scenecolor.r=255;
        scenecolor.g=216;
        scenecolor.b=0;
        
        int rectH = ofGetHeight()/2;
        int rectW = 5;
        
        shader1.begin();
        shader1.setUniform2f("u_resolution1", rectW, rectH);
        for(int i = -5; i < ofGetWidth(); i+= 10){
            ofDrawRectangle(i, 0, rectW, rectH);
            //looks cool: i/1.9, i/2,
            shader1.setUniform1f("u_time1", ofGetElapsedTimef() - pow((i+1000), 0.3));
        }
        shader1.end();
        
        shader2.begin();
        shader1.setUniform2f("u_resolution1", rectW, rectH - 0);
        for(int i = -5; i < ofGetWidth(); i+= 10){
            ofDrawRectangle(i, 384, rectW, rectH);
            //looks cool: i/1.9, i/2,
            shader1.setUniform1f("u_time1", ofGetElapsedTimef() - pow((i+1000), 0.3));
        }
        shader2.end();
        ofSetColor(255, 216, 0);
        if(!hidden){
            font2.drawString("Press keys 1-4 to change.", 100, 100);
        }
        
        
    }else if(currentScene == SUN_SCENE ){
        scenenumber = "3";
        ofBackgroundGradient(ofColor(255, 252, 104), ofColor(255, 68, 227) );
        ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, pow(2 + avgSound * 100, 2.5));
        ofSetColor(255);
        if(!hidden){
            font3.drawString("Press keys 1-4 to change.", 100, 100);
        }
        
        scenecolor.r=0;
        scenecolor.g=0;
        scenecolor.b=0;
    }else if(currentScene == PHOTO){
        scenenumber = "1";
        ofSetColor(26,2,142);
        ofBackgroundGradient(ofColor(40,100,240), ofColor(200,150,230));
        //font4.drawString("Press keys 1-4 to change.", 100, 100);
        //ofSetColor(40,100,240);
        
        //ofDrawRectangle(150, 150, 5, 200);
        
        
        
        
        
        shader.begin();
        int rectW = ofGetWidth();
        int rectH = 5;
        shader.setUniform2f("u_resolution", rectW, rectH);
        // shader.setUniform1f("u_time", ofGetElapsedTimef());
        for(int i = 0; i < ofGetHeight(); i+= 10){
            ofDrawRectangle(0, i, rectW, rectH);
            float calc = ofGetElapsedTimef() - i;
            //looks cool: i/1.9, i/2,
            shader.setUniform1f("u_time", ofGetElapsedTimef() - (i/1.9));
        }
        shader.end();
        if(!hidden){
            font4.drawString("Press keys 1-4 to change.", 100, 100);
            font4.drawString("Press f for fullscreen.", 100, 160);
            font4.drawString("Press h to hide titles.", 100, 220);
        }
        scenecolor.r=26;
        scenecolor.g=2;
        scenecolor.b=142;
    }
    
    
    ofSetColor(scenecolor);
    if(!hidden){
        font0.drawString("SCENE: " + scenenumber, 700, 100);
    }
    
    //ofDrawBitmapString("avgSound " + std::to_string(avgSound), 300, 300);
}

//shape
float VJkris::r(float theta, float a, float b, float m, float n1, float n2, float n3){
    return pow(pow(abs(cos(m * theta / 4.0 ) / a), n2) + pow(abs(sin(m * theta / 4.0 ) / b), n3), -1.0 / n1);
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
    
    //minnnnnnnnnne
    shader.load("","data_kris/shader.frag");
    
    
    // use key press to change scenes and make any operations that
    // only need to happen on change (not update or draw )
    switch(key){
        case '1':
            currentScene = PHOTO;
            break;
        case '2':
            currentScene = SKY_SCENE;
            break;
        case '3':
            currentScene = SUN_SCENE;
            ofSetCircleResolution(100);
            break;
        case '4':
            currentScene = IDLEZ;
            break;
        case 'f':
            ofToggleFullscreen();
            break;
        case 'h':
            if(hidden){
                hidden = false;
                //show the titles
                
            }else{
                hidden = true;
                //hide the titles
                
            }
    }
}
