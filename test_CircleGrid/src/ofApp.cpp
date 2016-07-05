#include "ofApp.h"

void ofApp::setup() {
    ofxAudioVisualApp::setup();
    
    gui.add(numSpirals.set("Spirals", 5, 1, 10));
    gui.add(spiralRadius.set("Radius", 20, 10, 500));
        
    theta = -90;
    
    spiralRadius = ofRandom(300, 500);
    xPosition = ofRandom(spiralRadius, ofGetWidth() - spiralRadius);
    yPosition = ofRandom(spiralRadius, ofGetHeight() - spiralRadius);
}

void ofApp::draw() {
    ofPushMatrix();
    ofTranslate(xPosition, yPosition);
    ofRotate(theta, 0, 0, 1);
    for(int i = 0; i < drawBins.size(); i++) {
        ofColor col = ofxAudioVisualApp::setColorLerp(i);
        float drawRadius = spiralRadius;
        if(col.r + col.g + col.b == 0) drawRadius = 0;
        ofDrawCircle(0, ofMap(i, 0, drawBins.size(), 0, drawRadius), ofMap(drawBins[i], 0, 0.01, 0, 2, true));
    }
    ofPopMatrix();
    theta += 1.0;
    if(theta >= 360) {
        theta = 0.0;
        spiralRadius = ofRandom(300, 500);
        xPosition = ofRandom(spiralRadius, ofGetWidth() - spiralRadius);
        yPosition = ofRandom(spiralRadius, ofGetHeight() - spiralRadius);
        colLow = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(127));
        colHigh = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(127));
    }
    ofxAudioVisualApp::draw();
}
