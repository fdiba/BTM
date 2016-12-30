#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(255);

	message = false;

	midiOut.listPorts();
	midiOut.openPort(4);

	channel = 0;
	number = 0;
}

//--------------------------------------------------------------
void ofApp::exit() {
	midiOut.closePort();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(0);
	stringstream text;
	text << "connected to port " << midiOut.getPort()
		<< " \"" << midiOut.getName() << "\"" << endl
		<< "is virtual?: " << midiOut.isVirtual() << endl << endl
		<< "sending to channel " << channel << endl << endl;
	ofDrawBitmapString(text.str(), 20, 20);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	if (message) midiOut.sendControlChange(channel, number, 255);
	else midiOut.sendControlChange(channel, number, 0);

	message = !message;
	cout << "message: " << message << endl;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
