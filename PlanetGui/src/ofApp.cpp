#include "ofApp.h"
#include "Object.h"





void ofApp::setup() {
	ofBackground(0, 0, 0);
	//ofSetFrameRate(75);


	gui.setup(); // most of the time you don't need a name
	gui.add(flatworlds.setup("flat", false));
	gui.add(G.setup("G setup", .000006743, .000001000, .000008000));
	gui.add(NPlanet.setup("Planets:", 5, 1, 10));
	gui.setDefaultTextColor((0, 0, 0));

	dt = 0;
	ofVec3f sunpos = { 0,0,0 };

	sun = Object(sunpos, ofRandom(1000000000, 1000000000000), ofRandom(20, 30), ofColor(255, 255, 0));


	planets = new Object[NOBJECT];
	for (int i = 0; i < NOBJECT; i++) {
		ofVec3f location = { ofRandom(50,150), ofRandom(50, 150), ofRandom(50, 150) };
		float mass = ofRandom(0.8, 1.1);
		float dim = ofRandom(8, 16);
		ofColor color;
		color.set(ofRandom(255), ofRandom(255), ofRandom(255));
		planets[i] = Object(&sun, location, mass, dim, color, G);
	}

}

//--------------------------------------------------------------
void ofApp::update() {

	dt = ofGetElapsedTimef();
	ofResetElapsedTimeCounter();
	for (int i = 1; i < NPlanet; i++) {

		planets[i].update(dt, G);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	camera.begin();
	//ofNoFill();
	ofEnableDepthTest();
	sun.draw(flatworlds);
	for (int i = 1; i < NPlanet; i++) {

		planets[i].draw(flatworlds);
	}
	ofDisableDepthTest();
	camera.end();
	gui.draw();
	
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
