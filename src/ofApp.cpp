#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);
	//ofSetBackgroundAuto(false);

	p_state = -1;

	//-------- midi control
	max_particles = 150;//state1

	max_radius = 150;//state2
	initState2();

	std::stringstream strm;
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());

	//ofSetWindowTitle("midi test");

	//ofSetWindowShape(1024, 768);
	//ofSetWindowPosition(2024, 200);
	//ofSetFullscreen(true);

	//--------------

	camWidth = 320;  // try to grab at this size.
	camHeight = 240;

	vector<ofVideoDevice> devices = videoGrabber.listDevices();

	for (int i = 0; i < devices.size(); i++) {
		if (devices[i].bAvailable) {
			//log the device
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
		} else {
			//log the device and note it as unavailable
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
		}
	}

	videoGrabber.setDeviceID(0);
	videoGrabber.setDesiredFrameRate(60);
	videoGrabber.initGrabber(camWidth, camHeight);

	ofSetVerticalSync(true);

	//---------------
	instr_channel = 1;

	midiIn.listPorts();
	midiIn.openPort(1);

	midiIn.addListener(this);
	midiIn.setVerbose(true);

	mrect.setup(60, 80, "kick 60");

	//---------- state3
	mpointer.setup(ofGetWidth() / 2, ofGetHeight() / 2, 150, 40);
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

	//-----------------
	videoGrabber.update();

	if (videoGrabber.isFrameNew()) {
		ofPixels & pixels = videoGrabber.getPixels();
	}

	//------------------
	//will create multiple particles at the same time
	if (particles.size()<max_particles) {
		Particle p;
		p.setup(ofGetWidth() / 2, ofGetHeight() / 2);
		particles.push_back(p);
	}

	switch (p_state) {
	case 1:
		
		starDustAnimation();
		break;
	case 2:
		if (ofGetElapsedTimeMillis() % 1000 == 0)initState2(); //TODO 1000 param state2

		pulseAnimation();
		break;
	case 3:
		mpointer.update();
		circleAnimation();
		mpointer.detectCollisionWith(particles);
		break;
	defaut:
		break;
	}

	
	


}
//--------------------------------------------------------------
void ofApp::circleAnimation() { //state3

	ofVec2f center(ofGetWidth() / 2, ofGetHeight() / 2);

	for (int i = 0; i < particles.size(); i++) {
		particles[i].getAwayFrom(center, max_radius, max_radius);
		particles[i].separateFromEachOthers(i, particles);
		particles[i].editPosWithVel();
	}

}
void ofApp::pulseAnimation() { //state2

	ofVec2f center(ofGetWidth()/2, ofGetHeight()/2);

	if (radius > 0)radius-=.2;

	for (int i = 0; i < particles.size(); i++) {
		particles[i].getAwayFrom(center, radius, max_radius);
		//particles[i].separateFromEachOthers(i, particles);
		particles[i].editPosWithVel();
	}

}
void ofApp::starDustAnimation() { //state1

	for (int i = 0; i < particles.size(); i++) {
		particles[i].update();
		if (!particles[i].alive)particles.erase(particles.begin() + i);
	}
}
//--------------------------------------------------------------
void ofApp::draw(){

	//---------
	//mrect.draw();

	
	//-------------------
	//displayMidiInfos();

	//-------------------
	//ofSetHexColor(0xffffff);
	//videoGrabber.draw(20, ofGetHeight()-(camHeight+20));

	//-----------
	//ofSetHexColor(0x000000);
	//ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	if (p_state == 3) {
		mpointer.draw();
	}

	for (int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}

	
	
}
void ofApp::displayMidiInfos() {

	float xPos = 420;

	ofSetColor(255);

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
//-----------------------------
void ofApp::initState2() {
	radius = max_radius;
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	//cout << "Key: " << key << endl;

	if (key == '1' || key == '2' || key == '3') {
		
		p_state = key-'0';

		cout << "p_state: " << p_state << endl;

		if (key == '2')initState2();


	} else if (key == 's') {
		img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());

		//
		string str;
		string name = "of_oblivion_" ;
		string date = ofToString(ofGetUnixTime());
		string extension = ".png";
		str.append(name);
		str.append(date);
		str.append(extension);
		
		img.save(str);
	}

	

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
	//cout << "Time: " << ofGetElapsedTimef() << endl;
	//cout << "Time: " << ofGetElapsedTimeMillis() << endl;
	cout << "p size: " << particles.size() << "/" << max_particles << endl;

	switch (p_state){
	case 2:
		initState2();
		break;
	default:
		break;
	}

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
