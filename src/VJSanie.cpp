//
//  VJSanie.cpp
//  ofVJSet
//
//  Created by csugrue + sanie on 14/9/17.
//

#include "VJSanie.h"

void VJSanie::setup(){
    isPlaying = false;
    title = "VJ SANIE";
    circleSize = 20;

	//STATES
	currentState = LEVEL_2;
	//

	//TIMER
	myTimeKeeper = ofGetElapsedTimef();

	ofTrueTypeFont::setGlobalDpi(72);
	//verdana30.load("data/verdana.ttf", 30, true, true);
	//verdana30.setLineHeight(34.0f);
	//verdana30.setLetterSpacing(1.035);
	bFirst = true;
	//typeStr = "PRESS SPACE TO START";
	//instStr = "PRESS 1-3 TO CHANGE MODES\nMUTE VOLUME FOR LIVE AUDIO";

	shader.load("sanie_data/shader.vert", "sanie_data/shader.frag");
	shader.load("sanie_data/scene2shader.vert", "sanie_data/scene2shader.frag");

	//SECOND SHADER
	img2.load("sanie_data/bure.png");
	img2.resize(50, 50);
	img2.update();
	plane.set(500, 500, 50, 50, OF_PRIMITIVE_TRIANGLES);
	plane.mapTexCoordsFromTexture(img2.getTexture());

	//SOUNDTRACK
	mySound.load("sanie_data/bucky.mp3");
	//mySound.play();

	//plane.set(500, 500, 25, 25, OF_PRIMITIVE_TRIANGLES);

	img.load("sanie_data/diffuse_4.jpg");
	img.resize(50, 50);
	img.update();
	sphere.setRadius(250);
	sphere.mapTexCoordsFromTexture(img.getTexture());

	ofSetBackgroundColor(255);

	//SOUND
	ofSetVerticalSync(true);

	//soundStream.printDeviceList();

	int bufferSize = 128;


	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);

	bufferCounter = 0;
	drawCounter = 0;
	smoothedVol = 0.0;
	scaledVol = 0.0;

	//GUI
	gui.setup();
	gui.add(radius.setup("radius", 150, 40, 300));
	gui.add(myVolume.setup("volume", 0.5, 0, 1));
	gui.add(lines.setup("lines", 4, 4, 15));
	//

	//SCENE 3
	w = ofGetWidth();
	h = ofGetHeight();
	
}

void VJSanie::update(){
    
    circleSize = sin( ofGetElapsedTimef() ) * 30;

	//SOUND

	//scale vol up to 0-1 range
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);

	volHistory.push_back(scaledVol);

	if (volHistory.size() >= 400) {
		volHistory.erase(volHistory.begin(), volHistory.begin() + 1);
	}
    
   

	//GUI
	sphere.setRadius(radius);
	mySound.setVolume(myVolume);
	//

	//SCENE 3
	//ofSetWindowTitle(ofToString(ofGetFrameRate()));
	vid.update();
}

void VJSanie::draw(){
   
	if (currentState == START) {
		ofSetBackgroundColor(225);
		ofSetColor(0);
		//verdana30.drawString(typeStr, ofGetWidth() / 2 - 180, ofGetHeight() / 2);

	}
	else if (currentState == LEVEL_1) {
		ofSetBackgroundColor(170);
		if (ofGetElapsedTimef() - myTimeKeeper<8) {
			verdana30.drawString(instStr, ofGetWidth() / 2 - 230, ofGetHeight() / 2);
		}
		ofEnableDepthTest();
		img.bind();

		cam.begin();

		shader.begin();
		shader.setUniform1f("time", smoothedVol*200.0);
		sphere.drawWireframe();
		//sphere.draw();
		//plane.drawWireframe();
		shader.end();

		cam.end();

		ofDisableDepthTest();
		//GUI
		gui.draw();
		//
	}
	else if (currentState == LEVEL_2) {
		ofSetBackgroundColor(225);

		ofEnableDepthTest();
		img2.bind();

		cam.begin();
		shader.begin();
		shader.setUniform1f("time", smoothedVol * 100);
		plane.drawWireframe();
		shader.end();
		cam.end();

		ofDisableDepthTest();
		gui.draw();
	}
	else if (currentState == LEVEL_3) {
		ofBackground(255, 255, 255);
		ofSetColor(255, 255, 255);

		//TO FIX THE FULLSCREEN ISSUE:
		//use pop push matrix to offset it in the y
		//how to reinitialize the camera
		for (int y = 0; y<h; y += lines) {
			for (int x = 0; x<w; x += lines) {

				//get pixel color
				int i = (y*w + x) * 3;
				int r = vid.getPixels()[i + 0];
				int g = vid.getPixels()[i + 1];
				int b = vid.getPixels()[i + 2];

				//calculate brightness
				float br = (r + r + r) / 765.0;

				//use HSB color
				//ofSetColor(ofColor::fromHsb(br * 255, 255, 255));
				ofSetColor(br * 255);
				//ofSetColor(0, 0, 0);

				//calculate sine and cosine of brightness
				float co = cos(br*TWO_PI);
				float si = sin(br*TWO_PI);

				//draw rotated line based on brightness
				ofLine(x - 5 * co, y - 20 * si, x + 20 * co, y + 5 * si);
			}
		}
	}
	//GUI
	gui.draw();
	//
}

//--------------------------------------------------------------
void VJSanie::audioIn(float * input, int bufferSize, int nChannels) {

	float curVol = 0.0;

	// samples are "interleaved"
	int numCounted = 0;

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (int i = 0; i < bufferSize; i++) {
		left[i] = input[i * 2] * 0.5;
		right[i] = input[i * 2 + 1] * 0.5;

		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted += 2;
	}

	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;

	// this is how we get the root of rms :) 
	curVol = sqrt(curVol);

	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;

	bufferCounter++;

}

void VJSanie::start(){
    vid.initGrabber(w, h, true);
    
    // sets up mouse move events
    ofAddListener(ofEvents().mouseMoved, this, &VJSanie::mouseMoved);
    ofAddListener(ofEvents().keyPressed, this, &VJSanie::keyPressed);
    isPlaying = true;
    
    ofSetBackgroundColor(255);
}

void VJSanie::pause(){
    vid.close();

    ofRemoveListener(ofEvents().mouseMoved, this, &VJSanie::mouseMoved);
    ofRemoveListener(ofEvents().keyPressed, this, &VJSanie::keyPressed);
    isPlaying = false;
}

void VJSanie::mouseMoved(ofMouseEventArgs & mouse){
    mouseX = mouse.x;
    mouseY = mouse.y;
}

void VJSanie::keyPressed(ofKeyEventArgs & keyboard){
    
    int key = keyboard.key;
     ofLog() << "key pressed: " << key;
    
    // don't use reserved keys : 0, D, A, K , E, S, I, Q, B
	 switch (key) {
	 case '0':
		 currentState = START;
		 break;
	 case 'f':
		 ofToggleFullscreen();
		 break;
	 case ' ':
		 currentState = LEVEL_1;
		 shader.load("sanie_data/shader.vert", "sanie_data/shader.frag");
		 break;
	 case '1':
		 currentState = LEVEL_1;
		 shader.load("sanie_data/shader.vert", "sanie_data/shader.frag");
		 break;
	 case '2':
		 currentState = LEVEL_2;
		 shader.load("sanie_data/scene2shader.vert", "sanie_data/scene2shader.frag");
		 break;
	 case '3':
		 currentState = LEVEL_3;
		 break;
	 }
       
    }
