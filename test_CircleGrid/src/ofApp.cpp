#include "ofApp.h"

void ofApp::setup() {
    ofxAudioVisualApp::setup();
    
    gui.add(numSpirals.set("Spirals", 5, 1, 10));
    gui.add(spiralRadius.set("Radius", 20, 10, 500));
        
    theta = -90;
}

void ofApp::draw() {
    int numSpiralsPerRow = ofGetWidth() / spiralRadius.get()*2;
    int numRows = max(numSpirals.get() / numSpiralsPerRow, 1);
    for(int y = 0; y < numRows; y++) {
        for(int x = 0; x < numSpiralsPerRow; x++) {
            ofPushMatrix();
            float xPosition = ofMap(x, 0, numSpiralsPerRow, spiralRadius, ofGetWidth() - spiralRadius);
            float yPosition = ofMap(y, 0, numRows, spiralRadius, ofGetHeight() - spiralRadius);
            ofTranslate(xPosition, yPosition);
            ofRotate(theta, 0, 0, 1);
            for(int i = 0; i < drawBins.size(); i++) {
                ofColor col = ofColor(ofMap(drawBins[i], 0, 0.1, 0, 255, true));
                float drawRadius = spiralRadius;
                if(col.r + col.g + col.b == 0) drawRadius = 0;
                ofDrawCircle(0, ofMap(i, 0, drawBins.size(), 0, drawRadius), ofMap(drawBins[i], 0, 0.01, 0, 2, true));
            }
            ofPopMatrix();
        }
    }
    theta += 0.1;
    ofxAudioVisualApp::draw();
}
