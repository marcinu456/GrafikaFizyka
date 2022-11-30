#pragma once
#include "ofMain.h"
#include "Particle.h"

class Fireworks
{
public:
	vector<Particle> p; //Particles
	ofPoint pos;
	float bornRate; //Particles born 
	float bornCount;
	float timer;//timer to born paritcles
	float timetodie;
	int id;
	bool particlesdead;

public:
	bool bdead;
	ofPoint randomPoint(ofPoint _pos);
	void setup(int _x, int _y, int _id);
	Particle update(float dt);
	void draw();
	~Fireworks();
};

