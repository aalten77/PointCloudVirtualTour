#include "ofApp.h"
#include <fstream>

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableDepthTest();
	ofSetVerticalSync(true);

	cam.setDistance(500);

	//load pcd data into a ofMesh
	ifstream pcdFile;

	pcdFile.open("../bin/data/ism_train_lioness_v2.pcd");
	if (!pcdFile) {
		cout << "Unable to open file" << endl;
	}
	
	float x, y, z;
	while (pcdFile >> x >> y >> z) {
		pcMesh.addVertex(ofPoint(x, y, z));
		pcMesh.addColor(ofFloatColor(0, 0, 0));
		//cout << x << " " << y << " " << z << endl;
	}

}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	pcMesh.drawVertices();

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
