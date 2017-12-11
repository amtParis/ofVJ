#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "BaseSet.h"

enum VJSetState{
  IDLE = 0, TITLE, DASHA, SANIE, AMANDA, BELLA, QINQIN, ERICA, ICE, KRIS, LAST
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void audioIn(float * input, int bufferSize, int nChannels);

        void ChangeSet(VJSetState newSet, string name="");
        void ResetRandomOrder();
    
        ofSoundStream soundStream;
        VJSetState currentSet;
        VJSetState nextSet;
        vector<VJSetState> allSetStates;
    
    
        // Sets
        vector<BaseSet*> allSVJs;
    
    
        // Controls
        bool useKeyControl;
        bool showGui;
        ofxPanel gui;
        ofxToggle autoVJ;
        ofxToggle showMouse;
    
};
