#ifndef _PARTICLE
#define _PARTICLE

#include "ofMain.h"

class Particle {
	public:
		void setup(float _x, float _y);
		void update();
		void draw();

		float x;
		float y;

		float velX;
		float velY;

		int dim;
		int dim_max;
		ofColor color;
		float alpha;

		float lifespan;
		bool alive;

		Particle();

	private:
};
#endif

