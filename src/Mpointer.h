#ifndef _MPOINTER
#define _MPOINTER

#include "ofMain.h"
#include "Particle.h"

class MPointer {
	public:
		void setup(float _cx, float _cy, float _c_radius, float _radius);
		void update();
		void draw();

		void detectCollisionWith(vector <Particle> &particles);

		ofVec2f center;
		float c_radius;

		ofVec2f pos;
		float speed;

		float radius;
		ofColor color;
		float alpha;

		

		bool visible;

		MPointer();

	private:

		float angle;
		
};
#endif

