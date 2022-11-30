#include "Spring.h"

Spring::Spring(int _i, int _j, std::vector<Point*>& points)
{
	i = _i;
	j = _j;
	length = points[i]->position.distance(points[j]->position);
}


Spring::~Spring()
{
}

void Spring::draw()
{

}

void Spring::update(std::vector<Point*>& myPoints,float KS)
{
	// count the distance between connected points
	Point* p1 = myPoints[i];
	Point* p2 = myPoints[j];
	ofVec2f pos1 = p1->position;
	ofVec2f pos2 = p2->position;
	float dist = pos1.distance(pos2);

	if (dist != 0)
	{
		// velocity from positions
		p1->velocity = p1->position - p1->positionOld;
		p2->velocity = p2->position - p2->positionOld;
		ofVec2f vn = p1->velocity - p2->velocity;	// velocity subtraction
		ofVec2f dpos = pos1 - pos2;						// position subtraction

		// Force
		ofVec2f f = ((dist - length) * KS) +(vn * dpos);
		ofVec2f F = f * (dpos / dist);
		p1->forces -= F;
		p2->forces += F;

	}
}
