#include "Point.h"
#include <ofGraphics.h>


Point::Point(float x, float y, float mass, bool isStatic)
{
	
	v_positionOld = { x,y };
	v_position = { x,y };
	v_velocity = { 0,0 };
	v_forces = { 0,0 };
	m_mass = mass;
	m_isStatic = isStatic;
	dt = 0.025;

}

Point::~Point()
{
}


void Point::updateVerlet()
{
	if (!m_isStatic)
	{
		v_positionNew = 2 * v_position - v_positionOld + (dt*dt*v_forces / m_mass);
		v_positionOld = v_position;
		v_position = v_positionNew;
	}
}

void Point::updateEuler()
{
	if (!m_isStatic)
	{
		v_velocity += v_forces * dt;
		v_positionNew = v_position + v_velocity * dt;
		v_positionOld = v_position;
		v_position = v_positionNew;
	}
}
