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
    //ofHideCursor();
    currentSet = TITLE;
    nextSet = IDLE;
    useKeyControl = true;
    showGui = false;
    gui.setup();
    gui.add( autoVJ.set("auto mode", true) );
    autoVJ.addListener(this,&ofApp::OnAutoModeChange);
                       //this, &ofApp::OnAutoModeChange);
    
    
    
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
    
    ResetRandomOrder();
    
    int bufferSize = 128;
    soundStream.setup(0, 2, 44100, bufferSize, 2);
    soundStream.setInput(this);
    
    ChangeSet(IDLE,"Idle");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    allSVJs[currentSet]->update();
    
    if( currentSet == IDLE && allSVJs[currentSet]->isDone == true ){
        ChangeSet(nextSet);
    }else if( autoVJ == true && currentSet != IDLE && ofGetElapsedTimef() - allSVJs[currentSet]->timeStarted > allSVJs[currentSet]->duration){
        ChangeAutoSet();
        //VJSetState nextSet = allSetStates[0];//VJSetState( int(ofRandom(2,10) ) );
        //ChangeSet(nextSet, allSVJs[nextSet]->title );
        //allSetStates.erase( allSetStates.begin() );
        //if(allSetStates.size() == 0 ) ResetRandomOrder();
    }
    
}

void ofApp::ChangeAutoSet(){
    VJSetState nextSet = allSetStates[0];//VJSetState( int(ofRandom(2,10) ) );
    ChangeSet(nextSet, allSVJs[nextSet]->title );
    allSetStates.erase( allSetStates.begin() );
    if(allSetStates.size() == 0 ) ResetRandomOrder();
}

void ofApp::OnAutoModeChange(bool & autoVJ){
    if(autoVJ){
        ChangeAutoSet();
    }
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    allSVJs[currentSet]->draw();
    
    //ofDisableDepthTest();
    if(showGui) gui.draw();
    
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
    ofShowCursor();
}

void ofApp::ResetRandomOrder(){
    
    allSetStates.clear();
    
    for ( int i = DASHA; i != LAST; i++ ){
        if( static_cast<VJSetState>(i) != ERICA && static_cast<VJSetState>(i) != BELLA){
            VJSetState vj = static_cast<VJSetState>(i);
            allSetStates.push_back(vj);
        }
    }
    
    std::random_shuffle(allSetStates.begin(), allSetStates.end());
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
            //case OF_KEY_TAB: autoVJ = !autoVJ; break;
            case OF_KEY_TAB: showGui = !showGui; break;//case 'M': ofShowCursor(); break;
        }
    }else if(key == OF_KEY_DEL){
        useKeyControl= !useKeyControl;
    }
    
    ofLog() << "useKeyControl " << useKeyControl;
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

