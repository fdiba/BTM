#ifndef _MPOINTER
#define _MPOINTER

#include "ofMain.h"

class MPointer {
	public:
		void setup(float _x, float _y);
		void update();
		void draw();

		ofVec2f pos;
		float speed;

		int radius;
		ofColor color;
		float alpha;

		bool visible;

		MPointer();

	private:

		
};
#endif

