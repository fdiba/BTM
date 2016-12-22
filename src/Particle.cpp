#include "Particle.h"
Particle::Particle() {

}


void Particle::setup(float _x, float _y) {
	x = _x;
	y = _y;

	velX = ofRandom(-.5, .5);
	velY = ofRandom(-.5, .5);

	color.set(255);
	dim_max = 3;
	lifespan = ofRandom(.5, 1.);
	alive = true;

}


void Particle::update() {

	x += velX;
	y += velY;

	alpha = ofMap(lifespan, 0, 1, 300, -300);
	alpha = ofClamp(alpha, 0, 255);

	dim = ofMap(alpha, 0, 255, 1, dim_max);

	lifespan -= .001;

	if (lifespan <= 0) alive = false;

}

void Particle::draw() {
	ofSetColor(color, alpha);
	ofDrawCircle(x, y, dim);
}
