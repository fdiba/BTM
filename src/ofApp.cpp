#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("midi test");

	//ofSetWindowShape(1024, 768);
	ofSetWindowPosition(2024, 200);
	//ofSetFullscreen(true);

	instr_channel = 1;

	midiIn.listPorts();
	midiIn.openPort(1);

	midiIn.addListener(this);
	midiIn.setVerbose(true);

	mrect.setup(60, 80, "kick 60");
}
//--------------------------------------------------------------
void ofApp::exit() {

	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}
//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {

	// make a copy of the latest message
	midiMessage = msg;

	string str = ofxMidiMessage::getStatusString(midiMessage.status);
	if (str.find("Note Off") == -1) {
		//cout << "Channel: " << midiMessage.pitch << endl;
		switch (midiMessage.pitch) {
		case 60: //kick
			mrect.dim = 40;
			break;
		case 62: //snare
			break;
		case 64: //hh closed
			break;
		case 65: //hh open
			break;
		case 67: //clap
			break;
		case 69: //conga
			break;
		case 71: //cymbal
			break;
		case 72: //rim
			break;
		default:
			cout << "Channel: " << midiMessage.pitch << endl;
			break;
		}
	}


}
//--------------------------------------------------------------
void ofApp::update(){
	mrect.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	mrect.draw();

	displayMidiInfos();
	
}
void ofApp::displayMidiInfos() {

	float xPos = 420;

	ofSetColor(0);

	// draw the last recieved message contents to the screen
	text << "Received: " << ofxMidiMessage::getStatusString(midiMessage.status);
	ofDrawBitmapString(text.str(), xPos, 20);
	text.str(""); // clear

	text << "channel: " << midiMessage.channel;
	ofDrawBitmapString(text.str(), xPos, 34);
	text.str(""); // clear

	text << "pitch: " << midiMessage.pitch;
	ofDrawBitmapString(text.str(), xPos, 48);
	text.str(""); // clear
	ofDrawRectangle(xPos, 58, ofMap(midiMessage.pitch, 0, 127, 0, ofGetWidth() - xPos - 10), 20);

	text << "velocity: " << midiMessage.velocity;
	ofDrawBitmapString(text.str(), xPos, 96);
	text.str(""); // clear
	ofDrawRectangle(xPos, 105, ofMap(midiMessage.velocity, 0, 127, 0, ofGetWidth() - xPos - 10), 20);

	text << "control: " << midiMessage.control;
	ofDrawBitmapString(text.str(), xPos, 144);
	text.str(""); // clear
	ofDrawRectangle(xPos, 154, ofMap(midiMessage.control, 0, 127, 0, ofGetWidth() - 40), 20);

	text << "value: " << midiMessage.value;
	ofDrawBitmapString(text.str(), xPos, 192);
	text.str(""); // clear
	if (midiMessage.status == MIDI_PITCH_BEND) {
		ofDrawRectangle(xPos, 202, ofMap(midiMessage.value, 0, MIDI_MAX_BEND, 0, ofGetWidth() - 40), 20);
	}
	else {
		ofDrawRectangle(xPos, 202, ofMap(midiMessage.value, 0, 127, 0, ofGetWidth() - 40), 20);
	}

	text << "delta: " << midiMessage.deltatime;
	ofDrawBitmapString(text.str(), xPos, 240);
	text.str(""); // clear

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
	mrect.dim = 40;
	cout << "Time: " << ofGetElapsedTimef() << endl;
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