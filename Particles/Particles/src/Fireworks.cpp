#include "Fireworks.h"

ofPoint Fireworks::randomPoint(ofPoint _pos) {
	ofPoint pnt;
	pnt.x = ofRandom(-25, 25);
	pnt.y = _pos.y + 25;
	return pnt;
}



void Fireworks::setup(int _x, int _y, int _id)
{
	//Set up parameters
	pos.x = _x;
	pos.y = _y;
	bornRate = 200;
	id = _id;
	timer = 0;
	timetodie = 0;
	bornCount = 0;
	bdead = false;
	particlesdead = false;
}

Particle Fireworks::update(float dt)
{
	Particle newP;
	timer += dt;
	timetodie += dt;
	pos.y -= 200 * dt;
	//std::cout << pos << "\n";
	//Born new particles
	bornCount += dt * bornRate;      //Update bornCount value
	if (bornCount > 3 && !bdead) {          //It's time to born particle(s)
		int bornN = int(bornCount);//How many born
		bornCount -= bornN;          //Correct bornCount value
		ofColor color;
		color.set(255, ofRandom(255), ofRandom(255));
		newP.setup(ofPoint(pos.x+15,pos.y+50), randomPoint(pos), color, ofRandom(2, 4), ofRandom(1, 2),0);               //Start a new particle
	}
	
	if (timetodie > 2.3)
	{
		bdead = true;
	}
	return newP;
}



void Fireworks::draw()
{
	ofSetColor(ofColor::green);
	if (!bdead)
		ofDrawRectangle(pos.x, pos.y, 30,50);

}

Fireworks::~Fireworks()
{
}
