#ifndef _PARTICLE
#define _PARTICLE

#include "ofMain.h"

class Particle {
	public:
		void setup(float _x, float _y);
		void update();
		void draw();

		void getAwayFrom(ofVec2f target, float c_radius, float c_max_radius);
		void separateFromEachOthers(int index, vector <Particle> particles);
		void editPosWithVel();

		ofVec2f pos;
		ofVec2f vel;

		int radius;
		int radius_max;
		ofColor color;
		float alpha;

		float lifespan;
		bool alive;

		Particle();

	private:

		
};
#endif

