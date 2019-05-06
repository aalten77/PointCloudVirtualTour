#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <map>
#include <utility>
#include <iostream>

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

		bool bPlayerCam = false;

		ofCamera *theCam;
		ofEasyCam cam;
		ofCamera player;

		//variables for CMU dataset
		typedef std::pair<string, ofColor> pair;
		ofMesh pcMesh;
		map<int, pair> labelDictionary; //key: label number, value: <label name, color> -- for CMU dataset
		
		//variables for office dataset
		ofMesh officeMesh;

		//ofxGui variables
		ofxPanel gui;

		ofxToggle toggle;
};
