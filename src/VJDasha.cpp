#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    currentScene = IDLE;

    shader.load("","dasha_data/shader.frag");
    receiver.setup(PORT);
    ofSetFrameRate(60);
    shader2.load("dasha_data/shader2.vert","dasha_data/shader2.frag");
//    plane.set(1024,150,50,50);
    sphere.setRadius( 200 );


//    ofBackground(0, 0, 0);
    oceandeep.load("dasha_data/sounds/OceanDeep-Tinkle.mp3");
    oceandeep.setVolume(0.75f);
    
    ofSetVerticalSync(true);
    ofSetCircleResolution(80);
    ofBackground(54, 54, 54);
    
    soundStream.printDeviceList();
    
    int bufferSize = 256;
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
    gui.setup(); // most of the time you don't need a name
//    gui.add(filled.setup("fill", true));
    gui.add(colorR.setup("color R", 140, 00, 255));
    gui.add(colorG.setup("color G", 140, 00, 255));
    gui.add(colorB.setup("color B", 140, 00, 255));
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(1280,720);
//    grayBg.allocate(320,240);
    grayDiff.allocate(1280,720);

    bLearnBakground = true;
    threshold = 80;


}


//--------------------------------------------------------------
void ofApp::update(){
    if(currentScene == IDLE){
        // updates for idle scene
        // check for waiting messages
        while(receiver.hasWaitingMessages()){
            // get the next message
            ofxOscMessage m;
            receiver.getNextMessage(m);
            
            // check for osc moved message
            if(m.getAddress() == "/hfosc/horizontalmotion"){
                oscX = m.getArgAsFloat(0);
            }
            
            if(m.getAddress() == "/hfosc/verticalmotion"){
                oscY = m.getArgAsFloat(0);
            }
            
        }

    }else if(currentScene == SCENE2){

        //lets scale the vol up to a 0-1 range
        scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
        
        //lets record the volume into an array
        volHistory.push_back( scaledVol );
        
        //if we are bigger the the size we want to record - lets drop the oldest value
        if( volHistory.size() >= 400 ){
            volHistory.erase(volHistory.begin(), volHistory.begin()+1);
        }
        
    }else if(currentScene == SCENE3){
        //lets scale the vol up to a 0-1 range
        scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
        
        //lets record the volume into an array
        volHistory.push_back( scaledVol );
        
        //if we are bigger the the size we want to record - lets drop the oldest value
        if( volHistory.size() >= 400 ){
            volHistory.erase(volHistory.begin(), volHistory.begin()+1);
        }
        bool bNewFrame = false;
        vidGrabber.update();
        bNewFrame = vidGrabber.isFrameNew();
        if (bNewFrame){
            
            colorImg.setFromPixels(vidGrabber.getPixels());
            
            grayImage = colorImg;
            if (bLearnBakground == true){
                grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
                bLearnBakground = false;
            }
            if(scaledVol>0.01){
            grayDiff.absDiff(grayBg, grayImage);
            grayDiff.threshold(threshold);
            }
        }

    }
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    if(currentScene == IDLE){
        
        shader.begin();
        shader.setUniform2f("osc", oscX, oscY);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        shader.end();
        ofSetColor(240, 149, 100);
        ofDrawBitmapString("Press keys 1-3 to change scenes.", 30, 30);
        ofDrawBitmapString("Connect your OSC device to port 12345 and the IP address of your computer.", 30, 50);
        ofDrawBitmapString("X-axis should be called /hfosc/horizontalmotion", 30, 70);
        ofDrawBitmapString("Y-axis should be called /hfosc/verticalmotion", 30, 90);
//        oceandeep.stop();
        
    }else if(currentScene == SCENE2){
//        oceandeep.play();

        gui.draw();
        cam.begin();
        shader2.begin();
        
        shader2.setUniform1f("scaledVol",scaledVol* 50.0f);

            ofSetColor(colorR, colorG, colorB);
            sphere.setPosition(50, scaledVol*5, 0);
            sphere.drawWireframe();
        shader2.end();
        cam.end();
    }else if(currentScene == SCENE3){
//        grayBg.draw(20,280);
        ofBackground(0, 0, 0);
        ofSetColor(45, 75, 200);
        grayDiff.draw(ofGetWidth()/18,ofGetHeight()/15);
        ofDrawBitmapString("Make a sound to update the image.", 30, 30);
        ofDrawBitmapString("Press ' ' to capture the background.", 30, 50);
//        oceandeep.stop();


//        320 240
    }
}


//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
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



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // use key press to change scenes and make any operations that
    // only need to happen on change (not update or draw )
    switch(key){
        case ' ':
            bLearnBakground = true;
            break;
        case 'f':
            ofToggleFullscreen();
            break;
        case '1':
            currentScene = IDLE;
            oceandeep.stop();
            break;
        case '2':
            currentScene = SCENE2;
            oceandeep.play();
            break;
        case '3':
            currentScene = SCENE3;
            oceandeep.stop();
            break;
    }


//    switch(key){
//        case 'c':
//            myAudio.setup();
//            myAudio.update();
//            myAudio.draw();
//            break;
//            //        case ' ':
//            //            //do something else
//            //            break;
//        case OF_KEY_UP:
//            ofLog() <<"key up";
//            break;
//    }
    
//    if (key == 't'){
//        myAudio.setup();
//        myAudio.update();
//        myAudio.draw();
////        ofBackground(0, 0, 0) ; // do something
//    } else if (key == 'r'){
//        ofBackground(255, 255, 255) ; // do something else
//    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
