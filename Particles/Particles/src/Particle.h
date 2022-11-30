#pragma once

#include "ofMain.h"

class Particle {
public:
	Particle(); //Class constructor
	void setup(ofPoint _pos, ofPoint _v, ofColor _color, float _lifeTime, float _vmod, int _id); //Start particle
	void update(float dt, float force); //Recalculate physics
	void draw(); //Draw particle
	ofPoint pos; //Position
	ofPoint vel; //Velocity
	ofColor color; //Color
	float time; //Time of living
	float lifeTime; //Allowed lifetime
	float vmod;
	int id;
	bool live; //Is particle live
};
