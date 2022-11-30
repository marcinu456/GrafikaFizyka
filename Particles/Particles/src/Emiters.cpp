#include "Emiters.h"

ofPoint Emiters::randomPoint(ofPoint _pos) {
	ofPoint pnt;
	pnt.x = ofRandom(-_pos.x, _pos.x);
	pnt.y = ofRandom(-_pos.y, _pos.y);
	pnt.z = ofRandom(-_pos.y, _pos.y);
	return pnt;
}

void Emiters::setup(int _x, int _y, int _id)
{
	//Set up parameters
	pos.x = _x;
	pos.y = _y;
	bornRate = _id;
	id = _id;
	timer = 0;
	timetodie = 0;
	bornCount = 0;
	bdead = false;
	particlesdead = false;
}

Particle Emiters::update(float dt)
{

	Particle newP;
	timer += dt;
	timetodie += dt;

	//Born new particles
	bornCount += dt * bornRate;      //Update bornCount value
	if (bornCount >2 && !bdead) {          //It's time to born particle(s)
		int bornN = int(bornCount);//How many born
		bornCount -= bornN;          //Correct bornCount value
		ofColor color;
		color.set(ofRandom(255), ofRandom(255), ofRandom(255));
		float hue = ofMap(timer, 0, 5, 0, 128);
		color.setHue(hue);
		newP.setup(pos, randomPoint(pos), color, ofRandom(2, 4), 1,1);               //Start a new particle

	}

	if (timetodie > 5)
	{
		bdead = true;
	}
	return newP;
}



void Emiters::draw()
{
	ofSetColor(ofColor::red);
	if (!bdead)
		ofDrawCircle(pos.x, pos.y, 10);

}

Emiters::~Emiters()
{
}

