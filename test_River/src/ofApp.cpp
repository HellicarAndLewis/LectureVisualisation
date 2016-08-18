#include "ofApp.h"
void ofApp::setup() {
    ofxAudioVisualApp::setup();
    x = 0;
    ofSetRectMode(OF_RECTMODE_CENTER);
    numBins = 16;
}

void ofApp::draw() {
    float halfBins[numBins];
    int j = 0;
    int step = 1024 / numBins;
    for(int i = 0; i < drawBins.size() - step; i += step) {
        if (isinf(halfBins[j])){
            halfBins[j] = 0;
        }
        for(int k = 0; k < step; k++) {
            halfBins[j] += drawBins[k];
        }
        halfBins[j] /= step;
        j++;
    }
    maxHeight = ofGetHeight() / numBins;

    int y = maxHeight/2;

    for(int i = 0; i < numBins; i++) {
        ofSetColor(255);
        float height = ofMap(halfBins[i], 0, 0.1, 0, maxHeight, true);
        ofDrawRectangle(x, y, 2, height);
        y += maxHeight;
    }
    x++;
    if(x > ofGetWidth())
        x = 0;
    
    ofxAudioVisualApp::draw();
}