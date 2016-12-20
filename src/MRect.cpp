#include "MRect.h"

MRect::MRect(){
}

void MRect::setup(float _x, float _y, string _name) {

	/*x = ofRandom(0, ofGetWidth());
	y = ofRandom(0, ofGetHeight());*/

	x = _x;
	y = _y;

	speedX = ofRandom(-1, 1);
	speedY = ofRandom(-1, 1);

	maxDim = 60;
	dim=maxDim;

	//color.set(ofRandom(255), ofRandom(255), ofRandom(255));
	color.set(255, 0, 0);

	name = _name;
}

void MRect::update() {
	if (dim > 0)dim-=.1;

	/*x = ofRandom(0, ofGetWidth());
	y = ofRandom(0, ofGetHeight());
	color.set(ofRandom(255), ofRandom(255), ofRandom(255));*/
}

void MRect::draw() {
	ofSetColor(color);
	ofDrawRectangle(x-dim/2, y-dim/2, dim, dim);

	ofSetColor(0x000000);
	ofDrawBitmapString(name, x - maxDim / 2 + 7, y - maxDim / 2);
}
