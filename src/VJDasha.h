//
//  VJDasha.h
//  ofVJSet
//
//  Created for Dasha on 14/9/17.
//

#pragma once

#include "BaseSet.h"

class VJDasha: public BaseSet{
    
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
    float circleSize;
};
