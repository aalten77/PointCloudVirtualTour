#pragma once

#ifndef _GRAVITYMESH_H_
#define _GRAVITYMESH_H_

#include "ofMain.h"

class gravityMesh : public ofMesh {
public:
	vector<float> velocities;
	vector<glm::vec3> basePos;
	vector<bool> resting;
};

#endif // !_gravitymesh_

