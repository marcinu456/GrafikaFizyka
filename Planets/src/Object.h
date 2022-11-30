#ifndef _BALL // if this class hasn't been defined, the program can define it
#define _BALL // by using this if statement you prevent the class to be called more than once which would confuse the compiler
#include "ofMain.h" // we need to include this to have a reference to the openFrameworks framework
class Object {

public: // place public functions or variables declarations here

// methods, equivalent to specific functions of your class objects
    void update(float _dt);  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing
    Object* sun;
  
    int id;
    float dim;
    float mass;
    ofVec3f location;
    ofVec3f velocity;
    ofColor color;

    float G = .000006743;

    Object(); // default constructor 
    Object(ofVec3f _location, float _mass, float _dim, const ofColor _color);  // sun constructor 
    Object(Object* _sun, ofVec3f _location, float _mass, float _dim, const ofColor _color, int _id);//planet construvtor
private: // place private functions or variables declarations here
}; // don't forget the semicolon!
#endif
