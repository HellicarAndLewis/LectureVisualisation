#include "ofApp.h"

//----------------------- App -----------------------------------------------

void ofApp::setup() {
    ofxAudioVisualApp::setup();
    theta = -90;
}

void ofApp::draw() {
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotate(theta, 0, 0, 1);
    for(int i = 0; i < drawBins.size(); i++) {
        //ofSetColor(ofMap(drawBins[i], 0, 0.1, 0, 255, true)); // Changed on shoot day 18/8/2016
//        ofxAudioVisualApp::setColorLerp(i);
        ofSetColor(ofxAudioVisualApp::getColor(i));
        ofDrawCircle(0, ofMap(i, 0, drawBins.size(), 0, 500), ofMap(drawBins[i], 0, 0.01, 0, 2, true));
    }
    ofPopMatrix();
    theta += 0.1;
    
    ofxAudioVisualApp::draw();
}

//----------------------- GUI -----------------------------------------------

void ofApp::setupGui(){
    ofxAudioVisualApp::setupGui();
}

void ofApp::drawGui(ofEventArgs & args){
    ofxAudioVisualApp::drawGui(args);
}