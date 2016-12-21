#include "Particle.h"
Particle::Particle() {

}


void Particle::setup() {
	x = ofGetWidth()/2;
	y = ofGetHeight()/2;

	color.set(255);
	dim = 3;
}


void Particle::update() {
}

void Particle::draw() {
	ofSetColor(color);
	ofDrawCircle(x, y, dim);
}
