#pragma once

#include <vector>
#include "Point.h"

class Spring
{
public:
	Spring(int i, int j, std::vector<Point*> &points);
	~Spring();
	void draw();

	int i, j; // indeksy punktów
	float length, nx, ny; //d³ugoœæ i normalne
};

