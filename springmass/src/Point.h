#pragma once

#include "ofMain.h"
#include <ofVec2f.h>


class Point
{
public:
	Point(float _x, float _y, float _pointSize, float _mass, int _id, bool _isStatic);
	~Point();
	void updateGravity(float G, float groundHeight);
	void updateVerlet(float _dt);


	ofVec2f positionOld;
	ofVec2f position;
	ofVec2f positionNew;

	ofVec2f velocity;
	ofVec2f forces;
	float pointSize;
	float mass;
	bool isStatic;
	int id;
};


