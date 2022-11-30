#pragma once

#include <vector>
#include "Point.h"

class Spring
{
public:
	Spring(int i, int j, std::vector<Point*>& points);
	~Spring();
	void draw();
	void update(std::vector<Point*>& myPoints, float KS);

	int i, j; 
	float length; 
};

