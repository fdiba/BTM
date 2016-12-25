#include "MPointer.h"
MPointer::MPointer() {

}


void MPointer::setup(float _cx, float _cy, float _c_radius, float _radius) {

	center.set(_cx, _cy);
	c_radius = _c_radius;

	pos.set(_cx + _c_radius, _cy);
	angle = 0;


	color.set(255);
	radius = _radius;
	visible = true;
	alpha=60;

}
//TODO calculate angle not distance
void MPointer::detectCollisionWith(vector <Particle> &particles) {

	//cout << "size: " << particles.size() << endl;

	for (int i = 0; i < particles.size(); i++) {

		//float dist = pos.squareDistance(particles[i].pos);
		float dist = pos.distance(particles[i].pos);
		if (dist < radius) {
			particles[i].color.set(255, 255, 0);
		}

		

	}

}
void MPointer::update() {
	
	angle+=.001;

	pos.x = cos(angle)*c_radius;
	pos.y = sin(angle)*c_radius;

	pos += center;


	//float x = cos(radians(angle)) * radius;
	//float y = sin(radians(angle)) * radius;


}

void MPointer::draw() {
	ofSetColor(color, alpha);
	ofDrawCircle(pos.x, pos.y, radius);
}
