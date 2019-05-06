#include "ofApp.h"
#include <fstream>

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	//use distance of 20 for the office dataset
	cam.setDistance(20);
	theCam = &cam;

	player.setPosition(0, -200, 0);
	player.lookAt(glm::vec3(0, 0, 0));
	player.setNearClip(.1);
	player.setFov(65.5);

	//setup for ofxGui
	gui.setup();
	gui.setPosition(ofPoint(10, 10));
	gui.add(toggle.setup("next", false));

	
	/****CMU Dataset Oakland****/
	//read labels and store in map
	ifstream labelFile;
	labelFile.open("../bin/data/oakland_part2_labels.txt");
	if (!labelFile) cout << "Unable to open cmu labels file" << endl;

	int labelnum, r, g, b;
	string labelname;
	while (labelFile >> labelnum >> labelname >> r >> g >> b) {
		labelDictionary.insert(std::pair<int, pair>(labelnum, std::pair<string, ofColor>(labelname, ofColor(r, g, b))));
	}

	//read dataset
	ifstream pcdFiles[10];

	for (int i = 0; i < 10; i++) {
		float x, y, z;
		int label, conf;

		ostringstream filename;
		filename << "../bin/data/oakland_part2_" << (i+1) << ".xyz_label_conf";
		pcdFiles[i].open(filename.str());
		if (!pcdFiles[i]) cout << "Unable to open " << filename.str() << endl;

		while (pcdFiles[i] >> x >> y >> z >> label >> conf) {
			pcMesh.addVertex(ofPoint(x, y, z));
			pcMesh.addColor(labelDictionary[label].second);
		}
	}

	//**************************************************************
	//**********OFFICE Dataset************
	//load pcd data into a ofMesh
	
	ifstream officeFile;
	officeFile.open("../bin/data/scene1_ascii_v2.pcd");
	if (!officeFile) cout << "Unable to open scene1 dataset" << endl;

	float x, y, z, rgb, distance;
	int cameraIndex, segment, label;
	while (officeFile >> x >> y >> z >> rgb >> cameraIndex >> distance >> segment >> label) {
		officeMesh.addVertex(ofPoint(x, y, z));

		uint32_t rgbt = 0;
		memcpy(&rgbt, &rgb, sizeof rgbt);
		uint8_t r = (rgbt >> 16) & 0x0000ff;
		uint8_t g = (rgbt >> 8) & 0x0000ff;
		uint8_t b = (rgbt) & 0x0000ff;

		officeMesh.addColor(ofColor(int(r), int(g), int(b))); 
	}

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();
	

	theCam->begin();

	ofDrawAxis(5);
	
	glPointSize(3);

	
	if (toggle) {
		//***use for the CMU datasets ****
		ofPushMatrix();
		ofRotateY(180);
		ofRotateX(-90);
		pcMesh.drawVertices();
		ofPopMatrix();
	}
	else {
		//***use for the scene datasets****
		ofPushMatrix();
		ofTranslate(glm::vec3(0, -5, 10));
		ofScale(10);
		ofRotateY(90);
		ofRotateX(-90);
		officeMesh.drawVertices();
		ofPopMatrix();
	}

	theCam->end();

	
	ofDisableDepthTest();
	gui.draw();
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
	if (toggle) { //reset cam for CMU dataset
		cam.setDistance(200);
	}
	else { //reset cam for office scene dataset
		cam.setDistance(20);
	}
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
