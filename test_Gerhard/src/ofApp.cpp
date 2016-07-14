#include "ofApp.h"

void ofApp::setup() {
    ofxAudioVisualApp::setup();
    x = 0;
}

void ofApp::draw() {
    ofxAudioVisualApp::draw();

    ofPushMatrix();
    for(int i = 0; i < drawBins.size(); i++) {
        ofColor col = ofxAudioVisualApp::getColorFromSpectrum(i);
        ofSetColor(col);
        ofDrawCircle(x, ofMap(i, 0, drawBins.size(), 0, ofGetHeight()), 2);
    }
    ofPopMatrix();
    x += 1;
    if(x > ofGetWidth())
        x = 0;
}