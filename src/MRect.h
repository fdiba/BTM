#ifndef _MRECT
#define _MRECT
#include "ofMain.h"

class MRect {
	
	public:
	
		void setup(float _x, float _y, string _name);
		void update();
		void draw();

		MRect();

		float x;
		float y;
		float speedX;
		float speedY;
		
		float dim;
		float maxDim;

		ofColor color;

		string name;

	private:

};
#endif
