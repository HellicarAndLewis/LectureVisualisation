#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofxAudioVisualApp::setup();

	gui.setup("settings", "settings/settings.xml");
	gui.add(month.set("Month", 4, 1, 12));
	gui.add(day.set("Day", 5, 1, 31));
	gui.add(hour.set("Hour", 0, 0, 24));
	gui.add(minute.set("Minute", 0, 0, 60));
	gui.add(duration.set("Duration", 60, 0, 180));
	gui.loadFromFile("settings/settings.xml");

	velocity = ofVec2f(0.0, 0.0);
	position = ofVec2f(0.0, 0.0);
}

//--------------------------------------------------------------
void ofApp::update(){
	ofxAudioVisualApp::update();

	velocity.x = hour/2 - ofMap(ofxAudioVisualApp::getAverageVolume(drawBins), 0.0, 0.002, 0.0, hour);
	velocity.y = day/2 - ofMap(ofxAudioVisualApp::getAverageVolume(drawBins), 0.0, 0.002, 0.0, day);

	position += velocity;

	if (position.x > ofGetWidth() || position.y > ofGetHeight()) {
		position.x = ofRandom(0.0, ofGetWidth());
		position.y = ofRandom(0.0, ofGetHeight());
	}
	if (position.x < 0 || position.y < 0) {
		position.x = ofRandom(0.0, ofGetWidth());
		position.y = ofRandom(0.0, ofGetHeight());
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofPushMatrix();
	ofTranslate(position);
	ofDrawCircle(0, 0, ofMap(ofxAudioVisualApp::getAverageVolume(drawBins), 0.0, 0.002, 0.0, month));
	ofPopMatrix();

	gui.draw();
	//ofxAudioVisualApp::draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	ofxAudioVisualApp::keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::guiKeyPressed(ofKeyEventArgs & args) {

}

//--------------------------------------------------------------
void onSettingChanged(ofAbstractParameter &p) {
	string name = p.getName();
}


//--------------------------------GUI---------------------------
void ofApp::setupGui() {
	ofxAudioVisualApp::setupGui();
}

//--------------------------------GUI---------------------------
void ofApp::drawGui(ofEventArgs & args) {
	ofxAudioVisualApp::drawGui(args);
}
