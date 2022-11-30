#pragma once

#include "ofMain.h"
#include "Point.h"
#include "Spring.h"
#include <ofVec2f.h>
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		


		void drawSprings(); 
		void drawPoints();	  


		void createLine(float x, float y);


		vector<Point*> Points_vec;
		vector<Spring*> Springs_vec;
		Point* selectedPoint;
		Point* selectedPoint2;
		

		ofxFloatSlider G;	//Gravity
		ofxFloatSlider KS;	//K
		ofxFloatSlider MouseF;	

		float pointSize; 
		float groundHeight; 
		ofColor springColor; 
	
		ofxToggle run_sim;
		ofxToggle add_point;
		ofxToggle static_point;
		ofxToggle add_spring;
		ofxButton delete_point;
		ofxPanel gui;
		int p_id = 0;
		int test = 0;
		bool once = true;

};
