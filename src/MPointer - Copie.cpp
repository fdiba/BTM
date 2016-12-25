#include "MPointer.h"
Particle::MPointer() {

}


void MPointer::setup(float _x, float _y) {

	pos.set(_x, _y);

	color.set(255);
	radius = 3;
	visible = true;
	alpha=255;

}

void MPointer::update() {


}

void Particle::draw() {
	ofSetColor(color, alpha);
	ofDrawCircle(pos.x, pos.y, radius);
}
