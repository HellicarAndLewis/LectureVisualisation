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
    
    gui.add(size.set("size",3.3, 0.0, 5.0));
    buffer.allocate(ofGetScreenWidth(), ofGetScreenHeight());
}

void ofApp::draw() {
    shader.begin();
    shader.setUniform1f("time", ofGetElapsedTimef()*size);
    shader.setUniform2f("resolution", ofVec2f(ofGetWidth(), ofGetHeight()));
    shader.setUniform1f("size", size);
    image.draw(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    ofxAudioVisualApp::draw();
}