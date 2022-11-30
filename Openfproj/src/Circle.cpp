#include "Circle.h"



Circle::Circle() {
}


void Circle::setup(float _x, float _y, float _mass, int _dim, int _id, Circle* _others,int _N) {
    dim = _dim;
    id = _id;
    others = _others;
    location = { _x,_y };
    mass = _mass;
    velocity = { ofRandom(-10, 10) ,ofRandom(0, 10) }; // V
    color.set(ofRandom(255), ofRandom(255), ofRandom(255));
    N = _N;
    force = { 0,0 };


}

void Circle::update(float gravity, float _dt) {

    dt = _dt;
    location += velocity * dt;
    colisions();
    
    force.y += gravity * mass;
    collide();
    drag();

    velocity += (force / mass) * dt;
    force = {0,0};
}

void Circle::draw() {
    ofSetColor(color);
    ofDrawCircle(location, dim);
}





void Circle::drag(){
    if (location.y > ofGetWindowHeight() / 2) {
        float N = 0.01;
        float Stokes = -6 * 3.14 * N * dim;
        ofVec2f drag = { Stokes * velocity.x, Stokes * velocity.y };
        force += drag;

    }
}


void Circle::colisions() {

    if (location.y + dim > ofGetWindowHeight()) {
        location.y = ofGetWindowHeight() - dim;
        velocity.y *= friction;
    }
    else if (location.y - dim < 0) {
        location.y = dim;
        velocity.y = -velocity.y;
    }
 
    if (location.x + dim > ofGetWindowWidth() || location.x < dim) {
            velocity.x = -velocity.x;
    }
}

void Circle::collide() { //https://processing.org/examples/bouncybubbles.html
    for (int i = id + 1; i < N; i++) {
        float dx = others[i].location.x - location.x;
        float dy = others[i].location.y - location.y;
        float distance = sqrt(dx * dx + dy * dy);
        float minDist = others[i].dim / 2 + dim / 2;
        if (distance < minDist) {
            float angle = atan2(dy, dx);
            float targetX = location.x + cos(angle) * minDist;
            float targetY = location.y + sin(angle) * minDist;
            float ax = (targetX - others[i].location.x) * spring;
            float ay = (targetY - others[i].location.y) * spring;
            velocity.x -= ax;
            velocity.x -= ay;

            others[i].velocity.x += ay;
            others[i].velocity.y += ax;
        }
    }
}