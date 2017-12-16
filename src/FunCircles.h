//
//  FunCircles.hpp
//  GLSL
//
//  Created by Aisulu Baibolova on 18/09/17.
//
//

#ifndef FunCircles_h
#define FunCircles_h

#include <stdio.h>

#include "ofMain.h" // we need to include this to have a reference to the openFrameworks framework
class FunCircles {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    void setup();	// setup method, use this to setup your object's initial state
    void update();  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing
    
    void audioIn(float * input, int bufferSize, int nChannels);
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    int 	bufferCounter;
    int 	drawCounter;
    float smoothedVol;
    float scaledVol;
    
    ofSoundStream soundStream;
    
    // variables
    float x;        // position
    float y;
    float speedY;   // speed and direction
    float speedX;
    float dim;        // size
    ofColor color;  // color using ofColor type
    
    FunCircles();  // constructor - used to initialize an object, if no properties are passed the program sets them to the default value
private: // place private functions or variables declarations here
};

#endif /* FunCircles_hpp */
