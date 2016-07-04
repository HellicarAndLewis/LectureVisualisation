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
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    float x = 0;
    float y = ofGetHeight()/2;
    for(int i = 0; i < fft->getBinSize(); i++) {
        mesh.addVertex(ofVec3f(x, y, 0));
        x += ofGetScreenWidth()/fft->getBinSize()*2;
    }
    yOffset = 10;
    
    ofSetFrameRate(200);
}

void ofApp::draw() {
    for(int i = 0; i < drawBins.size(); i++) {
        ofVec3f vertex = mesh.getVertex(i);
        float newHeight = ofMap(drawBins[i], 0.0, 0.01, 0, ofGetHeight()/2, true);
        mesh.setVertex(i, ofVec3f(vertex.x, yOffset + newHeight, vertex.z));
    }
    yOffset += 10;
    if(yOffset > ofGetHeight()) {
        yOffset = 0;
    }
    
    ofSetColor(255);
    mesh.draw();
    
    ofxAudioVisualApp::draw();
}