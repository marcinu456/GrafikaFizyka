#include "ofApp.h"
#include "Point.h"
#include "Spring.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(0, 0, 0);
	ofSetFrameRate(60);

	G = 90;
	KS = 1755.0;
	KD = 35.0;
	counter = 0;
	pointSize = 10;
	dragForce = { 0,0 };
	debug = false;
	groundHeight = 450;
	springColor = { 10,255,10 };
	tarzanFont.loadFont("verdana.ttf", 10);

	createLine(200, 100);
	createLine(500, 100);
	createLine(800, 100);

	player = new Player(100, 200, 15);
}

//--------------------------------------------------------------
void ofApp::update(){
	
	// grawitacja
	for (auto &p : myPoints)
	{
		p->v_forces.y = p->m_mass*G;
		p->v_forces.x = 0;
	}
		
	// ============================================== SPRÊ¯YNA
	// si³a sprê¿ystoœci
	for (auto &s : mySprings)
	{
		// liczenie odleg³oœci miêdzy po³¹czonymi punktami
		Point *p1 = myPoints[s->i];		Point *p2 = myPoints[s->j];
		ofVec2f pos1 = p1->v_position;	ofVec2f pos2 = p2->v_position;
		float dist = pos1.distance(pos2);

		if (dist != 0)
		{
			// prêdkoœci z po³o¿eñ 
			p1->v_velocity = p1->v_position - p1->v_positionOld;
			p2->v_velocity = p2->v_position - p2->v_positionOld;
			ofVec2f vn = p1->v_velocity - p2->v_velocity;	// ró¿nica prêdkoœci
			ofVec2f dpos = pos1 - pos2;						// ró¿nica po³o¿eñ
			
			// si³y
			ofVec2f f = (dist - s->length) * KS + (vn * dpos) * KD / dist;
			ofVec2f F = f * (dpos / dist);
			p1->v_forces -= F;
			p2->v_forces += F;
			
		}
	}

	if (selectedPoint)
	{
		ofVec2f mousePos = { float(mouseX), float(mouseY) };
		dragForce = (mousePos - selectedPoint->v_position);
		selectedPoint->v_forces += dragForce;
	}

	// gdy gracz trzyma linkê jakomœ
	// bardzo prowizoryczne bujanie siê na lince
	if (player->isHoldingLine)
	{
		//player->grabbedPoint->v_forces.y += 500;
		if (keyIsDown['a'])
			player->grabbedPoint->v_forces.x -= 100;
		if (keyIsDown['d'])
			player->grabbedPoint->v_forces.x += 100;
	}

	// bardzo prowizoryczne sprawdzanie kolizji z punktami
	if (keyIsDown['e'] && !player->isHoldingLine)
		for (auto &p : myPoints)
		{
			float dist = player->v_position.distance(p->v_position);
			if (dist < (player->m_radius + pointSize))
			{
				player->grabbedPoint = p;
				p->v_forces.x += player->v_speed.x * 750;
				p->v_forces.y += player->v_speed.y * 250;
				player->isHoldingLine = true;
				break;
			}
		}

	// aktualizacja po³o¿eñ
	if (counter < 2)
		for (auto &p : myPoints)
		{
			p->updateEuler();
			counter++;
		}
	else
		for (auto &p : myPoints)
		{
			p->updateVerlet();
		}

	// ============================================ BARDZO PROWIZORYCZNY GRACZ
	player->v_speed.y += .5; // grawitacja
	if (player->v_speed.y >= 15) player->v_speed.y = 15; //ograniczenie prêdkoœci spadania

	// bardzo prowizoryczna kolizja z pod³o¿em 
	if (player->v_position.y > groundHeight - player->m_radius) 
	{
		player->v_speed.y = 0;
		// a gdy siê oka¿e, ¿e wyl¹dowa³ pod pod³og¹
		if (player->v_position.y > groundHeight - player->m_radius) 
			player->v_position.y = groundHeight - player->m_radius; 
	}

	// bardzo prowizoryczne skakanie
	if (player->v_position.y == groundHeight - player->m_radius) // gdy stoi na pod³o¿u
		if (keyIsDown['w'] && player->v_speed.y == 0)
			player->v_speed.y = -15;

	// bardzo prowizoryczne poruszanie siê w poziomie
	if (keyIsDown['a']) player->v_speed.x = -5;
	else if (keyIsDown['d']) player->v_speed.x = 5;
	else if (player->v_speed.x != 0)
		if (player->v_speed.x > 0)
			player->v_speed.x -= .5;
		else
			player->v_speed.x += .5;

	// takie ma³o prowizoryczne aktualizowanie po³o¿enia
	player->updatePosition();

	

	// bardzo prowizoryczne puszczanie siê linki
	if (player->isHoldingLine && keyIsDown['w'] && !keyIsDown['e'])
	{
		player->grabbedPoint = nullptr;
		player->isHoldingLine = false;
		player->v_speed.y = -10;
	}

	
}

//--------------------------------------------------------------
void ofApp::draw(){

	drawPoints();
	drawAllSprings();
	ofDrawLine(0, groundHeight, ofGetWidth(), groundHeight);
	if (player) player->draw();
	// TARZAAAAN
	tarzanFont.drawString("TARZAN", player->v_position.x-25, player->v_position.y-20);
	//
	if (debug)
	{
		ofDrawBitmapString("Debug ON", 10, 15);
		if (player->isHoldingLine)
		{
			char str[255];
			sprintf(str, "Grabbed line forces: %f %f",player->grabbedPoint->v_forces.x, player->grabbedPoint->v_forces.y);
			ofDrawBitmapString(str, 10, 30);
		}

		drawVelocities();
		if (selectedPoint)
		{
			ofSetColor(0, 255, 0);
			ofDrawCircle(selectedPoint->v_position, 5);
			ofSetColor(255, 255, 255);
		}
		if (selectedPoint)
			ofDrawLine(selectedPoint->v_position, selectedPoint->v_position + dragForce);
	}
	

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'p')
	{
		debug = !debug;
	}
	
	keyIsDown[key] = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	keyIsDown[key] = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	for (auto const &p : myPoints)
	{
		ofVec2f mousePos = ofVec2f(x, y);
		ofVec2f tempPos = mousePos - p->v_position;
		float dist = tempPos.length();

		if (dist < pointSize)
		{
			selectedPoint = p;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	clickPoint = nullptr;
	delete clickPoint;
	selectedPoint = nullptr;
	delete selectedPoint;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void ofApp::drawAllSprings()
{
	ofSetColor(springColor);
	ofSetLineWidth(5);
	for (auto const& s : mySprings)
	{
		ofVec2f pos1 = myPoints[s->i]->v_position;
		ofVec2f pos2 = myPoints[s->j]->v_position;
		ofDrawLine(pos1,pos2);
	}
	ofSetLineWidth(1);
	ofSetColor(255, 255, 255);
}

void ofApp::drawVelocities()
{
	for (auto const &p : myPoints)
	{
		ofSetColor(255, 0, 0);
		ofVec2f pos = p->v_position;
		ofDrawLine(pos, pos + p->v_velocity*10);
		ofSetColor(255, 255, 255);
	}
}

void ofApp::drawPoints()
{
	ofSetColor(springColor);
	for (auto const &p : myPoints)
		ofDrawCircle(p->v_position, pointSize);
	ofSetColor(255, 255, 255);
}

void ofApp::createLine(float x, float y)
{
	// co by wiedzieæ ile ju¿ jest naszych punktów
	int currentSize = myPoints.size();

	// nowy punkt (x, y, masa, isStatic)
	myPoints.push_back(new Point(x, y, 1, true));
	myPoints.push_back(new Point(x-10, y+40, 1, false));
	myPoints.push_back(new Point(x+10, y+80, 1, false));
	myPoints.push_back(new Point(x-10, y+120, 1, false));
	myPoints.push_back(new Point(x+10, y+160, 1, false));

	mySprings.push_back(new Spring(currentSize, currentSize+1, myPoints));
	mySprings.push_back(new Spring(currentSize+1, currentSize+2, myPoints));
	mySprings.push_back(new Spring(currentSize+2, currentSize+3, myPoints));
	mySprings.push_back(new Spring(currentSize+3, currentSize+4, myPoints));
}