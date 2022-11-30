#include "Object.h"


Object::Object() :
    sun(this), location(0,0,0), mass(0), dim(0), color(0,0,0), velocity(0, 0, 0)
{
}


Object::Object(ofVec3f _location, float _mass, float _dim, const ofColor _color):
    location(_location), mass(_mass), dim(_dim), color(_color), velocity(0, 0, 0), sun(this)
{
}

Object::Object(Object* _sun, ofVec3f _location, float _mass, float _dim, const ofColor _color, float _G):
    sun(_sun),location(_location),mass(_mass),dim(_dim),color(_color), G(_G),
    velocity( _location.x / _location.length() * sqrt(G * _sun->mass / _location.length()),
              -_location.y / _location.length() * sqrt(G * _sun->mass / _location.length()),
              _location.z / _location.length() * sqrt(G * _sun->mass / _location.length())
    ) 
{
}


ofVec3f Object::ugravitationfunc(float G)
{
    float m1 = sun->mass;
    float m2 = mass;
    float r = (location - sun->location).length();
    float gravity = (G * m1 * m2) / (r * r);
    ofVec3f uvector = ((sun->location - location) / (location - sun->location).length());
    return gravity * uvector;
}


void Object::update(float _dt, float _G) {
    
    location += velocity * _dt;
   // ofVec3f ugravitation = (_G * sun->mass * mass / pow((location - sun->location).length(), 2) * ((sun->location - location) / (location - sun->location).length()));
    velocity += _dt * ugravitationfunc(_G);
}

void Object::draw(bool _flatworlds) {
    ofSetColor(color);
 
    if(_flatworlds)
        ofDrawCircle(location, dim);
    else
        ofDrawSphere(location, dim);

}