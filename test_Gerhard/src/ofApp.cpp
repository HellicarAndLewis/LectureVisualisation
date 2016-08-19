#include "ofApp.h"

//----------------------- App -----------------------------------------------

void ofApp::setup() {
    ofxAudioVisualApp::setup();
    x = 0;
}

void ofApp::draw() {
    ofxAudioVisualApp::draw();

    ofPushMatrix();
    for(int i = 0; i < drawBins.size(); i++) {
        ofColor col = ofxAudioVisualApp::getColorFromSpectrum(i);
//        ofColor col = ofxAudioVisualApp::setColorLerp(i);
        ofSetColor(col);
        ofDrawCircle(x, ofMap(i, 0, drawBins.size(), 0, ofGetHeight()), 2);
    }
    ofPopMatrix();
    x += 1;
    if(x > ofGetWidth())
        x = 0;
}

//----------------------- GUI -----------------------------------------------

void ofApp::setupGui(){
    ofxAudioVisualApp::setupGui();
}

void ofApp::drawGui(ofEventArgs & args){
    ofxAudioVisualApp::drawGui(args);
}