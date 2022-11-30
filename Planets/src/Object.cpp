#include "Object.h"


Object::Object() :
    location(0,0,0), mass(0), dim(0), color(0,0,0), velocity(0, 0, 0)
{
    sun = this;
}


Object::Object(ofVec3f _location, float _mass, float _dim, const ofColor _color):
    location(_location), mass(_mass), dim(_dim), color(_color), velocity(0, 0, 0), sun(this)
{
}

Object::Object(Object* _sun, ofVec3f _location, float _mass, float _dim, const ofColor _color, int _id):
    sun(_sun),location(_location),mass(_mass),dim(_dim),color(_color), id(_id),
    velocity( _location.x / _location.length() * std::sqrt(G * _sun->mass / _location.length()),
              -_location.y / _location.length() * std::sqrt(G * _sun->mass / _location.length()),
              _location.z / _location.length() * std::sqrt(G * _sun->mass / _location.length())
    ) 
{
}



void Object::update(float _dt) {
    ofRotateY(ofGetElapsedTimef() * 10);
    location += velocity * _dt;
    velocity += _dt * (G * sun->mass / pow((location - sun->location).length(), 2) * ((sun->location - location) / (location - sun->location).length()));
}

void Object::draw() {
    ofSetColor(color);
    ofEnableDepthTest();
    if(id==2)
        ofDrawCircle(location, dim);
    else
        ofDrawSphere(location, dim);

}