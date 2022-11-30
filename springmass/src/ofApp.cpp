#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(0, 0, 0);
	ofSetFrameRate(60);
	pointSize = 10;

	groundHeight = 750;
	springColor = { 225,255,255 };


	//createLine(200, 100);

	gui.setup();
	gui.add(G.setup("Gravity", 9, 0, 10));
	gui.add(KS.setup("KS", 1055, 0, 1200));
	gui.add(MouseF.setup("MouseF", 1, 1, 10));
	gui.add(run_sim.setup("run_sim", false));
	gui.add(add_point.setup("add_point", false));
	gui.add(static_point.setup("static_point", true));
	gui.add(add_spring.setup("add_spring", false));
	gui.add(delete_point.setup("delete_point dont use"));
}

//--------------------------------------------------------------
void ofApp::update(){
	if (run_sim) {
		// Gravity Points
		for (auto& p : Points_vec)
		{
			p->updateGravity(G, groundHeight);
		}

		// Springs
		for (auto& s : Springs_vec)
		{
			s->update(Points_vec, KS);
		}

		if (selectedPoint)
		{
			ofVec2f mousePos = { float(mouseX), float(mouseY) };
			ofVec2f dragForce = (mousePos - selectedPoint->position)* MouseF;
			selectedPoint->forces += dragForce;
		}

		// Verlet Points
		float dt = 0.025;
		for (auto& p : Points_vec)
		{
			p->updateVerlet(dt);
		}
	}
	if (delete_point) {
		Springs_vec.clear();
		Points_vec.clear();
		p_id = 0;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	drawPoints();
	drawSprings();
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
	for (auto const& p : Points_vec)
	{
		ofVec2f mousePos = ofVec2f(x, y);
		ofVec2f tempPos = mousePos - p->position;
		float dist = tempPos.length();

		if (dist < pointSize)
		{
			if (run_sim)
				selectedPoint = p;
			else {
				if (test == 0 && once == true) {
					selectedPoint = p;
					std::cout << "test1\n";
					test++;
					once = false;
				}
				if (test == 1 && once == true) {
					selectedPoint2 = p;
					std::cout << "test2\n";
					test--;
					once = false;
				}
			}
		}

		if (add_spring && selectedPoint != nullptr && selectedPoint2 != nullptr && once == true) {
			if(selectedPoint!=selectedPoint2)
				Springs_vec.push_back(new Spring(selectedPoint->id, selectedPoint2->id, Points_vec));
			std::cout << selectedPoint->id << " 1\n";
			std::cout << selectedPoint2->id << " 2\n";
			selectedPoint = nullptr;
			selectedPoint2 = nullptr;
			once = false;
		}

	}

	if (add_point) {
		Points_vec.push_back(new Point(x, y, pointSize, 1, p_id, static_point));
		selectedPoint = Points_vec.back();
		p_id++;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (run_sim) {
		selectedPoint = nullptr;
		selectedPoint2 = nullptr;
	}
	once = true;

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


void ofApp::drawSprings()
{
	ofSetColor(springColor);
	ofSetLineWidth(3);
	for (auto const& s : Springs_vec)
	{
		ofVec2f pos1 = Points_vec[s->i]->position;
		ofVec2f pos2 = Points_vec[s->j]->position;
		ofDrawLine(pos1, pos2);
	}
}

void ofApp::drawPoints()
{
	ofSetColor(springColor);
	for (auto const& p : Points_vec)
		ofDrawCircle(p->position, pointSize);
	ofSetColor(255, 0, 0);

	if (selectedPoint != nullptr)
		ofDrawCircle(selectedPoint->position, pointSize);
	if (selectedPoint2 != nullptr)
		ofDrawCircle(selectedPoint2->position, pointSize);

}


void ofApp::createLine(float x, float y)
{

	int currentSize = Points_vec.size();


	Points_vec.push_back(new Point(x, y, pointSize, 1, p_id++, true));
	Points_vec.push_back(new Point(x + 50, y, pointSize, 1, p_id++, false));
	Points_vec.push_back(new Point(x + 100, y, pointSize, 1, p_id++, false));
	Points_vec.push_back(new Point(x + 150, y, pointSize, 1, p_id++, false));
	Points_vec.push_back(new Point(x + 200, y, pointSize, 1, p_id++, false));
	Points_vec.push_back(new Point(x + 250, y, pointSize, 1, p_id++, true));
	//Points_vec.push_back(new Point(x + 200, y, 1, true));
	Points_vec.push_back(new Point(x, y + 50, pointSize, 1, p_id++, false));
	Points_vec.push_back(new Point(x + 50, y + 50, pointSize, 1, p_id++, false));
	Points_vec.push_back(new Point(x + 100, y + 50, pointSize, 1, p_id++, false));
	Points_vec.push_back(new Point(x + 150, y + 50, pointSize, 1, p_id++, false));
	Points_vec.push_back(new Point(x + 200, y + 50, pointSize, 1, p_id++, false));
	Points_vec.push_back(new Point(x + 250, y + 50, pointSize, 1, p_id++, false));
	//Points_vec.push_back(new Point(x + 200, y, 1, true));
	Points_vec.push_back(new Point(x, y + 100, pointSize, 1, p_id++, false));
	Points_vec.push_back(new Point(x + 50, y + 100, pointSize, 1, p_id++, false));
	Points_vec.push_back(new Point(x + 100, y + 100, pointSize, 1, p_id++, false));
	Points_vec.push_back(new Point(x + 150, y + 100, pointSize, 1, p_id++, false));
	Points_vec.push_back(new Point(x + 200, y + 100, pointSize, 1, p_id++, false));
	Points_vec.push_back(new Point(x + 250, y + 100, pointSize, 1, p_id++, false));




	Springs_vec.push_back(new Spring(currentSize, currentSize + 1, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 1, currentSize + 2, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 2, currentSize + 3, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 3, currentSize + 4, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 4, currentSize + 5, Points_vec));
	//	Springs_vec.push_back(new Spring(currentSize + 5, currentSize + 6, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 6, currentSize + 7, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 7, currentSize + 8, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 8, currentSize + 9, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 9, currentSize + 10, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 10, currentSize + 11, Points_vec));
	//	Springs_vec.push_back(new Spring(currentSize + 5, currentSize + 6, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 12, currentSize + 13, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 13, currentSize + 14, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 14, currentSize + 15, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 15, currentSize + 16, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 16, currentSize + 17, Points_vec));
	//	Springs_vec.push_back(new Spring(currentSize + 5, currentSize + 6, Points_vec));
	Springs_vec.push_back(new Spring(currentSize, currentSize + 6, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 6, currentSize + 12, Points_vec));
	//	Springs_vec.push_back(new Spring(currentSize + 5, currentSize + 6, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 1, currentSize + 7, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 7, currentSize + 13, Points_vec));
	//	Springs_vec.push_back(new Spring(currentSize + 5, currentSize + 6, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 2, currentSize + 8, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 8, currentSize + 14, Points_vec));
	//	Springs_vec.push_back(new Spring(currentSize + 5, currentSize + 6, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 3, currentSize + 9, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 9, currentSize + 15, Points_vec));
	//	Springs_vec.push_back(new Spring(currentSize + 5, currentSize + 6, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 4, currentSize + 10, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 10, currentSize + 16, Points_vec));
	//	Springs_vec.push_back(new Spring(currentSize + 5, currentSize + 6, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 5, currentSize + 11, Points_vec));
	Springs_vec.push_back(new Spring(currentSize + 11, currentSize + 17, Points_vec));
}