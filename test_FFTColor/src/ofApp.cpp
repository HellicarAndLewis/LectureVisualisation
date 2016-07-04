#include "ofApp.h"

void ofApp::draw() {
    ofxAudioVisualApp::draw();
	ofSetColor(255);
	ofPushMatrix();
	ofTranslate(16, 16);
	

	ofDrawBitmapString("Frequency Domain", 0, 0);
	plot(drawBins, -plotHeight, plotHeight / 2);
	ofPopMatrix();
	string msg = ofToString((int) ofGetFrameRate()) + " fps";
	ofDrawBitmapString(msg, ofGetWidth() - 80, ofGetHeight() - 20);
}
