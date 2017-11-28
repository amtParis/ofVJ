//
//  IdleParticle.cpp
//  ofVJ
//
//  Created by csugrue on 11/16/17.
//

#include "IdleParticle.h"

void IdleParticle::setup(){
    
    mode = PARTICLE_MODE_ATTRACT;
    pos  = ofPoint( ofRandom(0,ofGetWidth()), ofRandom(0,ofGetHeight()), 0.0f);
    vel  = ofPoint(0,0,0);
    frc  = ofPoint(0,0,0);
    drag = .99f;
    
    attractPoints.push_back( ofPoint(ofRandom(0,ofGetWidth() ), ofRandom(0,ofGetHeight() ) ) );
    currentAttractor = 0;
}

void IdleParticle::update(){
    
    if( mode == PARTICLE_MODE_ATTRACT ){
        
        ofPoint attractPt(ofGetMouseX(), ofGetMouseY());
        if(attractPoints.size() > 0 ) attractPt = attractPoints[currentAttractor];
        
        trails.push_back(pos);
        if(trails.size() > 100 ) trails.erase(trails.begin());
        
        frc = attractPt-pos;
        frc.normalize();
        
        vel *= drag; //apply drag
        vel += frc * 0.6; //apply force
    }
    
    pos += vel;
    
}

void IdleParticle::draw(){
    ofDrawCircle(pos.x, pos.y, 1 * 4.0);
}

void IdleParticle::drawTrails(){
    
    ofBeginShape();
    for( auto p : trails ){
        ofVertex(p);
    }
    ofEndShape();
}
