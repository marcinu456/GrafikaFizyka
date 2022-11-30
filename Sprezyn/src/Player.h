#pragma once
#include <ofVec3f.h>
#include "Point.h"
class Player
{

private:
	
public:
	Player(float x, float y, float radius);
	~Player();
	void updatePosition();
	void draw();

	ofVec3f v_position;
	ofVec3f v_speed;
	float m_radius;
	bool isHoldingLine;
	Point* grabbedPoint;
};

