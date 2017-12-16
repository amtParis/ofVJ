//
//  VJSanie.h
//  ofVJSet
//
//  Created by csugrue & sanie on 14/9/17.
//

#pragma once

#include "BaseSet.h"
#include "ofxGui.h"

//STATES
enum gameState {
	//creating variables
	//clean way to manage dif states of game
	START = 0,
	LEVEL_1,
	LEVEL_2,
	LEVEL_3
};

class VJSanie: public BaseSet{
    
public:
	void setup();
	void update();
	void draw();

	void mouseMoved(ofMouseEventArgs& mouse);
	void keyPressed(ofKeyEventArgs & key);

	void start();
	void pause();

	//FIRST SHADER
	ofShader shader;
	ofImage img;
	ofSpherePrimitive sphere;
	ofEasyCam cam;

	//SECOND SHADER
	ofShader scene2shader;
	ofImage img2;
	ofPlanePrimitive plane;

	//SOUND
	void audioIn(float * input, int bufferSize, int nChannels);

	vector <float> left;
	vector <float> right;
	vector <float> volHistory;

	int 	bufferCounter;
	int 	drawCounter;

	float smoothedVol;
	float scaledVol;

	//GUI
	ofxFloatSlider radius;
	ofxFloatSlider myVolume;
	ofxFloatSlider lines;
	ofxPanel gui;

	//volume gui
	ofSoundPlayer mySound;

	//STATES
	gameState currentState;

	//TYPE
	ofTrueTypeFont	verdana30;
	bool bFirst;
	string typeStr;

	//TIMER
	float myTimeKeeper;
	string instStr;

	//SCENE 3
	float w, h;
	ofVideoGrabber vid;
    
    // custom vars
    float circleSize;
};
