#ifndef _BALL // if this class hasn't been defined, the program can define it
#define _BALL // by using this if statement you prevent the class to be called more than once which would confuse the compiler
#include "ofMain.h" // we need to include this to have a reference to the openFrameworks framework

class Circle {

public: // place public functions or variables declarations here

// methods, equivalent to specific functions of your class objects
    void setup(float _x, float _y, float _mass, int _dim, int _id, Circle* _others, int _N);   // setup method, use this to setup your object's initial state
    void update(float gravity, float _dt);  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing
    void collide();
    void drag();
    void colisions();
    Circle *others;

    // variables
    int id;
    float spring = 25;
    float dt = 0;
    float friction = -0.9;
    int dim;        // size
    int N;

    ofVec2f location;
    ofVec2f velocity;
    ofVec2f force;
    float mass;



    ofColor color;  // color using ofColor type

    Circle();  // constructor - used to initialize an object, if no properties are passed the program sets them to the default value
private: // place private functions or variables declarations here
}; // don't forget the semicolon!
#endif
