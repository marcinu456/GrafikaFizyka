#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(75); //Set screen frame rate

	partsystem.setup();

	gui.setup();
	gui.add(addEmit.setup("add emit",true));
	gui.add(whichEmit.setup("which emit", false));
}

//--------------------------------------------------------------
void ofApp::update() {
	//Compute dt
	float dt = ofGetElapsedTimef();
	ofResetElapsedTimeCounter();
	partsystem.update(dt);
}

//--------------------------------------------------------------
void ofApp::draw(){
	partsystem.draw();
	//gui.draw();
	
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

	partsystem.mousePressed(x,y,button);
	
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
