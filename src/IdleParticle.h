//
//  IdleParticle.hpp
//  ofVJ
//
//  Created by csugrue on 11/16/17.
//

#pragma once

#include "ofMain.h"

enum particleMode{
    PARTICLE_MODE_ATTRACT = 0,
    PARTICLE_MODE_REPEL,
    PARTICLE_MODE_NEAREST_POINTS,
    PARTICLE_MODE_NOISE
};

class IdleParticle{
    
public:
    
    void setup();
    void update();
    void draw();
    void drawTrails();
    
    ofPoint pos;
    ofPoint vel;
    ofPoint frc;
    
    float drag;
    float uniqueVal;
    float scale;
    
    particleMode mode;
    vector <ofPoint> attractPoints;
    int currentAttractor;
    
    vector<ofPoint> trails;
    
    
};
