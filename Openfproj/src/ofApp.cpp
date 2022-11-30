#include "ofApp.h"
#include <math.h>
//--------------------------------------------------------------
void ofApp::setup(){

	circle = new Circle[NCIRCLE];
	for (int i = 0; i < NCIRCLE; i++) {
		int size = ofRandom(5, 10); // defining the size of each ball based on its place in the array
		int randomX = ofRandom(0, ofGetWidth()); //generate a random value bigger than 0 and smaller than our application screen width
		int randomY = ofRandom(0, ofGetHeight()); //generate a random value bigger than 0 and smaller than our application screen height
		float randomMass = ofRandom(0, 5);
		circle[i].setup(randomX, randomY, randomMass, size,i,circle, NCIRCLE);
	}

	dt = 0;
	g = (9.81*50);
	windowheight = ofGetWindowHeight();
	windowwidth = ofGetWindowWidth();
}

//--------------------------------------------------------------
void ofApp::update(){
	dt = ofGetElapsedTimef();
	ofResetElapsedTimeCounter();
	for (int i = 0; i < NCIRCLE; i++) {
		
		circle[i].update(g,dt);
	}


}

//--------------------------------------------------------------
void ofApp::draw(){

	for (int i = 0; i < NCIRCLE; i++) {
		circle[i].draw();
	}
	ofSetColor(0, 0, 250, 100);
	ofDrawRectangle(0, ofGetWindowHeight() / 2, ofGetWindowWidth(), ofGetWindowHeight() / 2);
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

