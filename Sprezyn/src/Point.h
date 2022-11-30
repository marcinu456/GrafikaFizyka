#pragma once
#include <ofVec2f.h>

class Point
{
public:
	Point(float x, float y, float mass, bool isStatic);
	~Point();
	void updateVerlet();
	void updateEuler();

	ofVec2f v_positionOld;
	ofVec2f v_position;
	ofVec2f v_positionNew;

	ofVec2f v_velocity; 
	ofVec2f v_forces;
	float m_mass;// po³o¿enie, prêdkoœæ, si³y
	bool m_isStatic; // czy ma siê poruszaæ
	float dt;
};

