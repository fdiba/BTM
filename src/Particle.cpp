#include "Particle.h"
Particle::Particle() {

}


void Particle::setup(float _x, float _y) {

	pos.set(_x, _y);
	vel.set(ofRandom(-.5, .5), ofRandom(-.5, .5));

	color.set(255);
	radius_max = 3;
	lifespan = ofRandom(.5, 1.);
	alive = true;

}
void Particle::separateFromEachOthers(int index, vector <Particle> &particles) {

	for (int j = 0; j < particles.size(); j++){

		if (j != index) {

			//TODO use squareDistance !!
			float dist = pos.distance(particles[j].pos);
			//float dist = pos.squareDistance(particles[j].pos);

			if (dist < radius + particles[j].radius) {
				
				ofVec2f v = particles[j].pos - pos;
				v.normalize();
				v *= -1;//TODO PARAM

				vel += v;

				color.set(0, 255, 0);

			}

		}

	}


}
void Particle::getAwayFrom(ofVec2f target, float c_radius, float c_max_radius) {

	alpha = 255;
	radius = radius_max;

	//TODO use squareDistance !!
	float dist = pos.distance(target);

	float speed = .2;//TODO MAKE PARAM state2

	if (dist < c_radius) {

		ofVec2f v = target - pos;
		v.normalize();
		v *= -speed;

		vel += v;

		color.set(255,0,0);

	} else if (dist > c_radius+10) {

		ofVec2f v = target - pos;
		v.normalize();
		v *= speed;

		vel += v;

		color.set(0, 0, 255);

	}

	//----

	alpha = ofMap(dist, 0, c_max_radius, -100, 500);
	alpha = ofClamp(alpha, 0, 255);
	
}
void Particle::editPosWithVel() {
	pos += vel;
	vel *= .9;
}
void Particle::update() {

	pos += vel;

	alpha = ofMap(lifespan, 0, 1, 300, -300);
	alpha = ofClamp(alpha, 0, 255);

	radius = ofMap(alpha, 0, 255, 1, radius_max);

	lifespan -= .001;

	if (lifespan <= 0) alive = false;

}

void Particle::draw() {
	ofSetColor(color, alpha);
	ofDrawCircle(pos.x, pos.y, radius);
}
