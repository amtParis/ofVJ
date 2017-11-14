//
//  VJSanie.h
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#pragma once

#include "BaseSet.h"

class VJBella: public BaseSet{
    
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
