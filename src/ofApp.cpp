#include "ofApp.h"
#include "VJIdleSet.h"
#include "VJSanie.h"
#include "VJChris.h"
#include "VJkris.h"
#include "VJFF.h"
#include "VJIce.h"
#include "VJAmanda.h"
#include "VJBella.h"
#include "VJQin.h"
#include "VJDasha.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //IDLE = 0, TITLE, DASHA, SANIE, AMANDA, BELLA, QINQIN, ERICA, ICE, KRIS
    ofHideCursor();
    currentSet = TITLE;
    nextSet = IDLE;
    useKeyControl = true;
    autoVJ = false;
    
    //   IDLE = 0, TITLE, DASHA, SANIE, AMANDA, BELLA, QINQIN, ERICA, ICE, KRIS
    allSVJs.push_back( new VJIdleSet() ); // Idle
    allSVJs.push_back( new BaseSet() ); // Empty
    allSVJs.push_back( new VJDasha() ); // Dasha
    allSVJs.push_back( new VJSanie() ); // Sanie
    allSVJs.push_back( new VJAmanda() ); // Amanda
    allSVJs.push_back( new VJBella() ); // Bella
    allSVJs.push_back( new VJQin() ); // Qinqin
    allSVJs.push_back( new VJFF() ); // Erica
    allSVJs.push_back( new VJIce() ); // Ice
    allSVJs.push_back( new VJkris() ); // Kris
    allSVJs.push_back( new BaseSet() ); // Empty
    
    for ( int i = 0; i< allSVJs.size(); i++ ) {
        allSVJs[i]->duration = 60.0;
        allSVJs[i]->setup();
        
    }
    
    int bufferSize = 128;
    soundStream.setup(0, 2, 44100, bufferSize, 2);
    soundStream.setInput(this);
    
    ChangeSet(IDLE);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    allSVJs[currentSet]->update();
    
    if( currentSet == IDLE && allSVJs[currentSet]->isDone == true ){
        ChangeSet(nextSet);
    }else if( autoVJ == true && currentSet != IDLE && ofGetElapsedTimef() - allSVJs[currentSet]->timeStarted > allSVJs[currentSet]->duration){
        VJSetState nextSet = VJSetState( int(ofRandom(2,10) ) );
        ChangeSet( nextSet, allSVJs[nextSet]->title );
    }
    
    //ofLog() <<
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    allSVJs[currentSet]->draw();
    
}

void ofApp::ChangeSet(VJSetState newSet, string nextTitle){
    
    allSVJs[currentSet]->pause();
    
    if( currentSet == IDLE ){
        currentSet = newSet;
    }else{
        currentSet = IDLE;
        nextSet = newSet;
        allSVJs[currentSet]->title = nextTitle;
    }
    
    allSVJs[currentSet]->start();
    allSVJs[currentSet]->timeStarted = ofGetElapsedTimef();
    
    ofLog() << "New Set: " << newSet << " " << allSVJs[currentSet]->title;
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(useKeyControl){
        switch(key){
            case 'D': ChangeSet(DASHA,"DASHA"); break;
            case 'A': ChangeSet(AMANDA, "AMANDA"); break;
            case 'K': ChangeSet(KRIS, "KRIS"); break;
            case 'E': ChangeSet(ERICA, "ERICA"); break;
            case 'S': ChangeSet(SANIE, "SANIE"); break;
            case 'B': ChangeSet(BELLA, "BELLA"); break;
            case 'Q': ChangeSet(QINQIN, "QINQIN"); break;
            case 'I': ChangeSet(ICE, "ICE"); break;
            case '0': ChangeSet(IDLE, "Idle"); break;
            case '9': ChangeSet(IDLE, ""); break;
            case OF_KEY_TAB: autoVJ = !autoVJ; break;
        }
    }else if(key == OF_KEY_DEL){
        useKeyControl= !useKeyControl;
    }
    
    ofLog() << "useKeyControl " << useKeyControl;
    ofLog() << "autoVJ " << autoVJ;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
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

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    allSVJs[currentSet]->audioIn(input, bufferSize, nChannels);
    
    
}

