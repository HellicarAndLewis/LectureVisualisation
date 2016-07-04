//
//  ofApp.cpp
//  Skeleton
//
//  Created by cafe on 04/07/2016.
//
//

#include "ofApp.h"

void ofApp::setup() {
    ofxAudioVisualApp::setup();
    
    image.load("images/stones.jpg");
    shader.load("shaders/colors");
    buffer.allocate(ofGetScreenWidth(), ofGetScreenHeight());
}

void ofApp::draw() {
//    plot(drawBins, -plotHeight, plotHeight / 2);
    cout<<getAverageVolume(drawBins)<<endl;
    shader.begin();
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform2f("resolution", ofVec2f(ofGetWidth(), ofGetHeight()));
    shader.setUniform1f("size", ofMap(getAverageVolume(drawBins), 0, 0.01, 256.0, 16.0, true));
    image.draw(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    ofxAudioVisualApp::draw();
}