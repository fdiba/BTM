#include "Particle.h"
Particle::Particle() {

}


void Particle::setup(float _x, float _y) {

	pos.set(_x, _y);
	vel.set(ofRandom(-.5, .5), ofRandom(-.5, .5));

	color.set(255);
	dim_max = 3;
	lifespan = ofRandom(.5, 1.);
	alive = true;

}
void Particle::getAwayFrom(ofVec2f target) {

	alpha = 255;
	dim = dim_max;

	//TODO use squareDistance !!
	float dist = pos.distance(target);

	float speed = .2;//TODO MAKE PARAM state2
	float radius = 150; //TODO MAKE PARAM state2

	if (dist < radius) {

		ofVec2f v = target - pos;
		v.normalize();
		v *= -speed;

		vel += v;

		color.set(255,0,0);

	} else if (dist > radius+10) {

		ofVec2f v = target - pos;
		v.normalize();
		v *= speed;

		vel += v;

		color.set(0, 0, 255);

	}


	//----

	pos += vel;
	vel *= .9;



}
void Particle::update() {

	pos += vel;

	alpha = ofMap(lifespan, 0, 1, 300, -300);
	alpha = ofClamp(alpha, 0, 255);

	dim = ofMap(alpha, 0, 255, 1, dim_max);

	lifespan -= .001;

	if (lifespan <= 0) alive = false;

}

void Particle::draw() {
	ofSetColor(color, alpha);
	ofDrawCircle(pos.x, pos.y, dim);
}
