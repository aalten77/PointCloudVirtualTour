#include "ofApp.h"
#include <fstream>

//--------------------------------------------------------------
void ofApp::setup(){
	
	
	ofEnableDepthTest();
	ofSetVerticalSync(true);

	cam.setDistance(20);
	theCam = &cam;

	player.setPosition(0, -20, 0);
	player.lookAt(glm::vec3(0, 0, 0));
	player.setNearClip(.1);
	player.setFov(65.5);

	//load pcd data into a ofMesh
	ifstream pcdFiles[4];

	//pcdFile.open("../bin/data/scene1_ascii_v2.pcd");
	//if (!pcdFile) cout << "Unable to open file 1" << endl;
	//if (!pcdFile2) cout << "Unable to open file 2" << endl;
	//if (!pcdFile3) cout << "Unable to open file 3" << endl;
	//if (!pcdFile4) cout << "Unable to open file 4" << endl;

	for (int i = 1; i < 2; i++) {
		float x, y, z, rgb, distance;
		//uint32_t rgb;
		int cameraIndex, segment, label;

		ostringstream filename;
		filename << "../bin/data/scene" << i << "_ascii_v2.pcd";
		pcdFiles[i].open(filename.str());

		while (pcdFiles[i] >> x >> y >> z >> rgb >> cameraIndex >> distance >> segment >> label) {

			pcMesh.addVertex(ofPoint(x, y, z));

			uint32_t rgbt = 0;
			memcpy(&rgbt, &rgb, sizeof rgbt);
			uint8_t r = (rgbt >> 16) & 0x0000ff;
			uint8_t g = (rgbt >> 8) & 0x0000ff;
			uint8_t b = (rgbt) & 0x0000ff;

			pcMesh.addColor(ofColor(int(r), int(g), int(b)));
		}

	}

}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	theCam->begin();

	ofDrawAxis(5);
	
	glPointSize(5);
	ofPushMatrix();
	ofTranslate(glm::vec3(0, -5, 10));
	ofScale(10);
	ofRotateY(90);
	ofRotateX(-90);
	pcMesh.drawVertices();
	ofPopMatrix();

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
