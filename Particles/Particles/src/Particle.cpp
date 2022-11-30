#include "Particle.h"


Particle::Particle() {
	live = false;
}



void Particle::setup(ofPoint _pos, ofPoint _v, ofColor _color, float _lifeTime,float _vmod,int _id) {
	pos = _pos; 
	vel = _v; 
	time = 0;
	lifeTime = _lifeTime;
	live = true;
	color = _color;
	vmod = _vmod;
	id = _id;
}

void Particle::update(float dt, float force) {
	if (live) {
		pos.x += vel.x * dt * vmod * force; //Euler method
		pos.y += vel.y * dt * vmod;
		pos.z += vel.z * dt * vmod;
		//Update time and check if particle should die
		time += dt;
		if (time >= lifeTime) {
			live = false; //Particle is now considered as died
		}
	}
}

void Particle::draw() {
	if (live) {
		float size = ofMap(
			fabs(time - lifeTime / 2), 0, lifeTime / 2, 3, 1);
		//if (id == 0) {
		//	float hue = ofMap(time, 0, lifeTime, 128, 255);
		//	color.setHue(hue);
		//	ofSetColor(color);
		//	ofDrawCircle(pos, size * 2); //Draw particle
		//}
		//if (id == 1)
		//{
			//float hue = ofMap(5, 0, lifeTime, 0, 128);
			//color.setHue(hue);
		//	ofSetColor(color);
		//	ofDrawCircle(pos, size * 3); //Draw particle
		//}
		//if (id == 2) 
		//{
			ofSetColor(color);
			
			ofDrawSphere(pos, size * 3); //Draw particle
		//}
	}
}