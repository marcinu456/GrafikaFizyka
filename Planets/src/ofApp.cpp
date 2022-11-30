#include "ofApp.h"
#include "Object.h"





void ofApp::setup() {
    ofBackground(0, 0, 0);
    ofSetFrameRate(75);


	dt = 0;
	ofVec3f sunpos = { 0,0,0 };
	
	sun = Object(sunpos, ofRandom(1000000000, 1000000000000), ofRandom(20, 30), ofColor(255, 255, 150));
	
	
	planets = new Object[NOBJECT];
		for (int i = 0; i < NOBJECT; i++) {
			ofVec3f location = { ofRandom(20,150), ofRandom(20, 150), ofRandom(20, 30) };
			float mass = ofRandom(10000, 800000);
			float dim = ofRandom(8, 16);
			ofColor color; 
			color.set(ofRandom(255), ofRandom(255), ofRandom(255));
			planets[i] = Object(&sun, location, mass,dim, color,i);
		}

}

//--------------------------------------------------------------
void ofApp::update() {

	dt = ofGetElapsedTimef();
	ofResetElapsedTimeCounter();
	for (int i = 1; i < NOBJECT; i++) {

		planets[i].update(dt);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	camera.begin();
	ofNoFill();
	sun.draw();
	for (int i = 1; i < NOBJECT; i++) {

		planets[i].draw();
	}
	camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
