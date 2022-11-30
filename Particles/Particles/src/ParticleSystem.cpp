#include "ParticleSystem.h"
#include <iostream>
void ParticleSystem::setup()
{
	bornRate = 10;
	bornCount = 0;
	snow.setup(1,1,0);
	gui.setup();
	gui.add(addEmit.setup("Snow", false));
	gui.add(whichEmit.setup("which emit", false));
	gui.add(addFireworks.setup("fireworks"));
	gui.add(deleteparticles.setup("fireworks"));
	gui.add(Born.setup("Born", 0, 0, 100));
	gui.add(Force.setup("Force", 1, -3, 3));
}

void ParticleSystem::update(float dt)
{

	if (addFireworks)
	{
		Fireworks f;
		f.setup(500, 768, Born);
		fireworks.push_back(f);
	}
	if (deleteparticles)
	{
		p.clear();
	}

	timer += dt;
	//Delete inactive particles
	int f = 0;
	while (f < p.size()) {
		if (!p[f].live) {
			p.erase(p.begin() + f);
		}
		else {
			f++;
		}
	}
	if(addEmit)
	p.push_back(snow.update(dt));
	


	emiters(emit, dt);


	for (int i = 0; i < fireworks.size(); i++)
	{
		if (fireworks[i].timetodie >= 2.28)
		{
			Emiters e;
			e.setup(fireworks[i].pos.x + 15, fireworks[i].pos.y, 500);
			emit.push_back(e);
		}
	}
	emiters(fireworks, dt);

	//Update the particles
	for (int j = 0; j < p.size(); j++) {
		p[j].update(dt, Force);

	}
	
	
}

template<typename T>
void ParticleSystem::emiters(T &f,float dt)
{
	for (int j = 0; j < f.size(); j++) {
		p.push_back(f[j].update(dt));
		
	}
	
	int i = 0;
	while (i < f.size()) {
		if (f[i].bdead) {
			f.erase(f.begin() + i);
		}
		else {
			i++;
		}
	}
}

template<typename T>
void ParticleSystem::draws(T& f)
{
	for (int i = 0; i < f.size(); i++) {
		f[i].draw();
	}
}


void ParticleSystem::draw()
{
	//camera.begin();
	ofEnableDepthTest();
	for (int i = 0; i < p.size(); i++) {
		p[i].draw();
	}
	draws(emit);
	draws(fireworks);
	ofDisableDepthTest();
	//camera.end();


	gui.draw();
}




//--------------------------------------------------------------
void ParticleSystem::mousePressed(int x, int y, int button) {
	if (whichEmit)
	{
		Fireworks f;
		f.setup(x, y, Born);
		fireworks.push_back(f);
	}
	else
	{
		Emiters e;
		e.setup(x, y, Born);
		emit.push_back(e);
	}
}

