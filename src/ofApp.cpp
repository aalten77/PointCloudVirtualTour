#include "ofApp.h"
#include <fstream>

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	//use distance of 20 for the office dataset
	cam.setDistance(20);
	cam.setNearClip(.1);
	cam.setFov(65.5);
	theCam = &cam;

	player.setPosition(-200, 0, 0);
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
	//read labels and store in map
	ifstream officeLabelFile;
	officeLabelFile.open("../bin/data/scene_labels.txt");
	if (!officeLabelFile) cout << "Unable to open office labels file" << endl;

	string officelabelname;
	int num = 0;
	while (officeLabelFile >> officelabelname) {
		officeDictionary.insert(std::pair<int, string>(num, officelabelname));
		num++;
	}

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
			player.setPosition(player.getPosition() + 10 * player.getLookAtDir());
		}
		break;
	case OF_KEY_DOWN:
		if (bPlayerCam)
		{
			player.setPosition(player.getPosition() - 10 * player.getLookAtDir());
		}
		break;
	case OF_KEY_LEFT:
		if (bPlayerCam)
		{
			player.rotateDeg(5, 0, 1, 0);
		}
		break;
	case OF_KEY_RIGHT:
		if (bPlayerCam)
		{
			player.rotateDeg(-5, 0, 1, 0);
		}
		break;
	case 'w':
		if (bPlayerCam)
		{
			player.setPosition(player.getPosition() + glm::vec3(0, 10, 0));
		}
		break;
	case 's':
		if (bPlayerCam)
		{
			player.setPosition(player.getPosition() + glm::vec3(0, -10, 0));
		}
		break;
	case 'a':
		if (bPlayerCam)
		{
			player.setPosition(player.getPosition() - 10 * player.getSideDir());
		}
		break;
	case 'd':
		if (bPlayerCam)
		{
			player.setPosition(player.getPosition() + 10 * player.getSideDir());
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
	case OF_KEY_F3: //toggle for point selection examine mode
		bExaminePoint = !bExaminePoint;
		if (bExaminePoint) {
			cout << "Examine mode on" << endl;
			cam.disableMouseInput();
		}
		else {
			cout << "Examine mode off" << endl;
			cam.enableMouseInput();
		}
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
	// if moving camera, don't allow mouse interaction
	//
	if (cam.getMouseInputEnabled()) return;

	//examine points
	if (bExaminePoint) {
		cout << "Looking for a point to select..." << endl;
		if (doPointSelection()) {
			cout << selectedPoint << endl;
		}
		else {
			cout << "MISS" << endl;
		}
		return;
	}

	if (toggle) { //reset cam for CMU dataset
		cam.disableMouseInput();
		cam.setDistance(200);
		cam.enableMouseInput();
	}
	else { //reset cam for office scene dataset
		cam.disableMouseInput();
		cam.setDistance(20);
		cam.enableMouseInput();
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


//
//  ScreenSpace Selection Method: 
//  This is not the octree method, but will give you an idea of comparison
//  of speed between octree and screenspace.
//
//  Select Target Point on Terrain by comparing distance of mouse to 
//  vertice points projected onto screenspace.
//  if a point is selected, return true, else return false;
//
bool ofApp::doPointSelection() {

	ofMesh mesh;
	if (toggle) { //get mesh for CMU dataset
		mesh = pcMesh;
	}
	else { //get mesh for office scene dataset
		mesh = officeMesh;
	}

	int n = mesh.getNumVertices();
	float nearestDistance = 0;
	int nearestIndex = 0;

	bPointSelected = false;

	ofVec2f mouse(mouseX, mouseY);
	vector<ofVec3f> selection;

	// We check through the mesh vertices to see which ones
	// are "close" to the mouse point in screen space.  If we find 
	// points that are close, we store them in a vector (dynamic array)
	//
	for (int i = 0; i < n; i++) {
		ofVec3f vert = mesh.getVertex(i);
		ofVec3f posScreen = cam.worldToScreen(vert);
		float distance = posScreen.distance(mouse);
		//cout << "Vert: " << vert << " Distance: " << distance << endl;
		if (distance < selectionRange) {
			selection.push_back(vert);
			bPointSelected = true;
		}
		
	}

	//  if we found selected points, we need to determine which
	//  one is closest to the eye (camera). That one is our selected target.
	//
	if (bPointSelected) {
		float distance = 0;
		for (int i = 0; i < selection.size(); i++) {
			ofVec3f point = cam.worldToCamera(selection[i]);

			// In camera space, the camera is at (0,0,0), so distance from 
			// the camera is simply the length of the point vector
			//
			float curDist = point.length();

			if (i == 0 || curDist < distance) {
				distance = curDist;
				selectedPoint = selection[i];
			}
		}
	}
	return bPointSelected;
}