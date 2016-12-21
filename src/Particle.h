#ifndef _PARTICLE
#define _PARTICLE

#include "ofMain.h"

class Particle {
	public:
		void setup();
		void update();
		void draw();

		float x;
		float y;
		float speedX;
		float speedY;

		int dim;
		ofColor color;

		Particle();

	private:
};
#endif

