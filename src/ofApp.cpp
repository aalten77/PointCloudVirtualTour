#include "ofApp.h"
#include <fstream>

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableDepthTest();
	ofSetVerticalSync(true);

	cam.setDistance(500);
	theCam = &cam;

	player.setPosition(0, -500, 0);
	player.lookAt(glm::vec3(0, 0, 0));
	player.setNearClip(.1);
	player.setFov(65.5);

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
	theCam->begin();

	//pcMesh.drawVertices();
	ofSetColor(ofColor::black);
	for (int i = 0; i < pcMesh.getNumVertices(); i++)
	{
		ofDrawSphere(pcMesh.getVertex(i), 1);
	}

	theCam->end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case OF_KEY_UP:
		if (bPlayerCam)
		{
			player.setPosition(player.getPosition() + glm::vec3(0, 10, 0));
		}
		break;
	case OF_KEY_DOWN:
		if (bPlayerCam)
		{
			player.setPosition(player.getPosition() + glm::vec3(0, -10, 0));
		}
		break;
	case OF_KEY_LEFT:
		if (bPlayerCam)
		{
			player.setPosition(player.getPosition() + glm::vec3(-10, 0, 0));
		}
		break;
	case OF_KEY_RIGHT:
		if (bPlayerCam)
		{
			player.setPosition(player.getPosition() + glm::vec3(10, 0, 0));
		}
		break;
	case 'w':
		if (bPlayerCam)
		{
			player.setPosition(player.getPosition() + glm::vec3(0, 0, 10));
		}
		break;
	case 's':
		if (bPlayerCam)
		{
			player.setPosition(player.getPosition() + glm::vec3(0, 0, -10));
		}
		break;
	case OF_KEY_F1:
		theCam = &cam;
		bPlayerCam = false;
		break;
	case OF_KEY_F2:
		theCam = &player;
		bPlayerCam = true;
		break;
	default:
		break;
	}
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
