#pragma once
#include "ofMain.h"
#include "Particle.h"
#include "Emiters.h"
#include "Class.h"
#include "Fireworks.h"
#include "ofxGui.h"


class ParticleSystem
{
public:
	Snow snow;
	vector<Fireworks> fireworks;
	vector<Emiters> emit; //Emiters
	vector<Particle> p; //Particles
	ofVec2f pos;
	float bornRate; //Particles born 
	float bornCount;
	float timer;//timer to born paritcles
	float timetodie;
	int id;
	bool particlesdead;

public:
	bool bdead;
	void setup();
	void update(float dt);
	template<typename T>
	void emiters(T &f,float dt);

	template<typename T>
	void draws(T& f);
	void draw();
	void mousePressed(int x, int y, int button);

	//intatrface
	ofxToggle addEmit;
	ofxToggle whichEmit;
	ofxIntSlider Born;
	ofxFloatSlider Force;
	ofxButton addFireworks;
	ofxButton deleteparticles;
	ofxPanel gui;

	ofEasyCam camera;
};

