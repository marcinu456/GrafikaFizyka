#include "Class.h"


ofPoint Snow::randomPoint(ofPoint _pos) {
	ofPoint pnt;
	pnt.x = ofRandom(0, 1000);
	pnt.y = ofRandom(0, 10);
	return pnt;
}



void Snow::setup(int _x, int _y, int _id)
{
	//Set up parameters
	pos.x = _x;
	pos.y = _y;
	bornRate = 500;
	id = _id;
	timer = 0;
	timetodie = 0;
	bornCount = 0;
	bdead = false;
	particlesdead = false;
}

Particle Snow::update(float dt)
{
	Particle newP;

	//Born new particles
	bornCount += dt * bornRate;      //Update bornCount value
	if (!bdead) {          //It's time to born particle(s)
		int bornN = int(bornCount);//How many born
		bornCount -= bornN;          //Correct bornCount value
		ofColor color = ofColor::gray;
		newP.setup(randomPoint(pos), ofPoint(1,500), color, ofRandom(8, 10) , .5,2);               //Start a new particle
	}

	return newP;
}


Snow::~Snow()
{
}

