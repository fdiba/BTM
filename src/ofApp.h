#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

#include "MRect.h"
#include "Particle.h"

class ofApp : public ofBaseApp, public ofxMidiListener {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void displayMidiInfos();

		void newMidiMessage(ofxMidiMessage& eventArgs);
		void exit();

		ofxMidiIn midiIn;
		ofxMidiMessage midiMessage;
		stringstream text;

		int instr_channel;

		ofVideoGrabber videoGrabber;
		int camWidth;
		int camHeight;

		vector <Particle> particles;

		ofImage img;

		MRect mrect;
		
};
