#include "ofApp.h"
#include <fstream>

//--------------------------------------------------------------
void ofApp::setup(){
	
	
	ofEnableDepthTest();
	ofSetVerticalSync(true);

	//use distance of 20 for the office dataset
	cam.setDistance(200);
	theCam = &cam;

	player.setPosition(0, -200, 0);
	player.lookAt(glm::vec3(0, 0, 0));
	player.setNearClip(.1);
	player.setFov(65.5);

	
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

	//load pcd data into a ofMesh
	//ifstream pcdFiles[4]; //**** use for scene files ****

	//****use for the scene{i}_ascii_v2.pcd files****
	//for (int i = 1; i < 2; i++) {
	//	float x, y, z, rgb, distance;
	//	//uint32_t rgb;
	//	int cameraIndex, segment, label;

	//	ostringstream filename;
	//	filename << "../bin/data/scene" << i << "_ascii_v2.pcd";
	//	pcdFiles[i].open(filename.str());

	//	while (pcdFiles[i] >> x >> y >> z >> rgb >> cameraIndex >> distance >> segment >> label) {

	//		pcMesh.addVertex(ofPoint(x, y, z));

	//		uint32_t rgbt = 0;
	//		memcpy(&rgbt, &rgb, sizeof rgbt);
	//		uint8_t r = (rgbt >> 16) & 0x0000ff;
	//		uint8_t g = (rgbt >> 8) & 0x0000ff;
	//		uint8_t b = (rgbt) & 0x0000ff;

	//		pcMesh.addColor(ofColor(int(r), int(g), int(b)));
	//	}

	//}

}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	theCam->begin();

	ofDrawAxis(5);
	
	glPointSize(3);

	//***use for the CMU datasets ****
	ofPushMatrix();
	ofRotateY(180);
	ofRotateX(-90);
	pcMesh.drawVertices();
	ofPopMatrix();

	//***use for the scene datasets****
	/*ofPushMatrix();
	ofTranslate(glm::vec3(0, -5, 10));
	ofScale(10);
	ofRotateY(90);
	ofRotateX(-90);
	pcMesh.drawVertices();
	ofPopMatrix();*/

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
