#include "Point.h"

Point::Point(float _x, float _y, float _pointSize, float _mass,int _id, bool _isStatic)
{

	positionOld = { _x,_y };
	position = { _x,_y };
	velocity = { 0,0 };
	forces = { 0,0 };
	pointSize = _pointSize;
	mass = _mass;
	isStatic = _isStatic;
	id = _id;

}

Point::~Point()
{
}

void Point::updateGravity(float G, float groundHeight)
{
	forces.y = mass * (G * 10);
	forces.x = 0;
	if (position.y > groundHeight - pointSize)
	{
		velocity.y = 0;
		if (position.y > groundHeight - pointSize)
			position.y = groundHeight - pointSize;
	}
}


void Point::updateVerlet(float _dt)
{
	if (!isStatic)
	{
		positionNew = 2 * position - positionOld + (_dt * _dt * forces / mass);
		positionOld = position;
		position = positionNew;
	}
}

