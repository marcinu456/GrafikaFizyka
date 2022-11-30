#include "Spring.h"
#include <ofVec2f.h>
#include "Point.h"

Spring::Spring(int i, int j, std::vector<Point*> &points)
{
	this->i = i;
	this->j = j;
	length = points[this->i]->v_position.distance(points[this->j]->v_position);
}


Spring::~Spring()
{
}

void Spring::draw()
{

}
