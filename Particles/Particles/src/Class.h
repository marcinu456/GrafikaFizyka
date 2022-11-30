#pragma once
#include "ofMain.h"
#include "Particle.h"
//Jeden lub dwa typy emiterow
//emitery z poziomu aplikacje tablice emiterow
class Snow
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
	~Snow();
};

