#include "ofApp.h"
#include "VJIdleSet.h"
#include "VJSanie.h"
#include "VJChris.h"
#include "VJkris.h"
#include "VJFF.h"
#include "VJIce.h"
#include "VJAmanda.h"
#include "VJBella.h"
#include "VJDasha.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
	//IDLE = 0, TITLE, DASHA, SANIE, AMANDA, BELLA, QINQIN, ERICA, ICE, KRIS

    currentSet = IDLE;
    //   IDLE = 0, TITLE, DASHA, SANIE, AMANDA, BELLA, QINQIN, ERICA, ICE, KRIS
    allSVJs.push_back( new VJIdleSet() ); // Idle
    allSVJs.push_back( new BaseSet() ); // Title / Chris
    allSVJs.push_back( new BaseSet() ); // Dasha
    allSVJs.push_back( new VJSanie() ); // Sanie
    allSVJs.push_back( new VJAmanda() ); // Amanda
    allSVJs.push_back( new VJBella() ); // Bella
    allSVJs.push_back( new BaseSet() ); // Qinqin
    allSVJs.push_back( new VJFF() ); // Erica
    allSVJs.push_back( new VJIce() ); // Ice
    allSVJs.push_back( new VJkris() ); // Kris
    
    for ( int i = 0; i< allSVJs.size(); i++ ) { allSVJs[i]->setup(); }
    
    ChangeSet(IDLE);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    allSVJs[currentSet]->update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    allSVJs[currentSet]->draw();
    
}

void ofApp::ChangeSet(VJSetState newSet){
    
    allSVJs[currentSet]->pause();
    currentSet = newSet;
    allSVJs[currentSet]->start();
    ofLog() << "New Set: " << newSet << " " << allSVJs[currentSet]->title;

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'D': ChangeSet(DASHA); break;
        case 'A': ChangeSet(AMANDA); break;
        case 'K': ChangeSet(KRIS); break;
        case 'E': ChangeSet(ERICA); break;
        case 's': ChangeSet(SANIE); break;
        case 'B': ChangeSet(BELLA); break;
        case 'Q': ChangeSet(QINQIN); break;
        case 'I': ChangeSet(ICE); break;
        case '0': ChangeSet(IDLE); break;
    }
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
