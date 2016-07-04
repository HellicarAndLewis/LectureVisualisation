#include "ofApp.h"

void ofApp::setup() {
    ofxAudioVisualApp::setup();
    x = 0;
}

void ofApp::draw() {
    ofxAudioVisualApp::draw();

    ofPushMatrix();
    for(int i = 0; i < drawBins.size(); i++) {
        ofSetColor(ofMap(drawBins[i], 0, 0.1, 0, 255, true));
        ofDrawCircle(x, ofMap(i, 0, drawBins.size(), 0, ofGetHeight()), 2);
    }
    ofPopMatrix();
    x += 1;
    if(x > ofGetWidth())
        x = 0;
}