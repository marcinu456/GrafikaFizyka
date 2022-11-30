#include "Player.h"
#include <ofGraphics.h>
Player::Player(float x, float y, float radius):v_position({x,y}), m_radius(radius), isHoldingLine(false)
{
}


Player::~Player()
{
}

void Player::updatePosition()
{
	if (!isHoldingLine)
		v_position += v_speed;
	else if (grabbedPoint)
	{
		v_position = grabbedPoint->v_position;
	}
}

void Player::draw()
{
	ofSetColor(0, 0, 255);
	ofDrawCircle(v_position, m_radius);
	ofSetColor(255, 255, 255);
}