#include "ofApp.h"

void ofApp::setup() {
    ofxAudioVisualApp::setup();
    gui.add(threshold.set("Threshold", 0.0038, 0, 0.009));
    gui.add(symmetrical.set("Symmetrical", true));
    
    x = 0;
    y = 0;
    
    ofAddListener(settings.parameterChangedE(), this, &ofApp::onSettingChanged);
}

void ofApp::draw() {
    ofxAudioVisualApp::draw();
    
    float scaleFactor = 1;
    
    int symmetryFactor = symmetrical ? 2 : 1;

    ofPushMatrix();
    ofPushStyle();
    ofTranslate(0, ofGetHeight() * 0.1 * y);
    for(int i = 0; i < drawBins.size() * (0.1/symmetryFactor); i++) {
        ofColor col;
        if(drawBins[i] > threshold){
//            col = ofxAudioVisualApp::getColorFromSpectrum(i); // changed on shoot day 18/8/2016
            col = ofxAudioVisualApp::getColor(i);
        }else{
            col = (0,0,0);
        }
        
        ofSetColor(col);
        if(symmetrical){
            ofDrawCircle(x, ofMap(i, 0, drawBins.size(), 0, ofGetHeight() * scaleFactor) + (ofGetHeight() * 0.05), 2);
            ofDrawCircle(x, (ofGetHeight() * 0.05) - ofMap(i, 0, drawBins.size(), 0, ofGetHeight() * scaleFactor) , 2);
        }else{
            ofDrawCircle(x, ofMap(i, 0, drawBins.size(), 0, ofGetHeight() * scaleFactor), 2);
        }
    }
    ofPopStyle();
    ofPopMatrix();
    
    x += 1;
    if(x > ofGetWidth()) {
        x = 0;
        y++;
        
        if(y > 9){
            y = 0;
        }
    }
}

void ofApp::keyPressed(int key) {
    ofxAudioVisualApp::keyPressed(key);
    
    switch (key) {
        case 's':
            symmetrical = !symmetrical;
            break;
        default:
            break;
    }
}

void ofApp::onSettingChanged(ofAbstractParameter &p){
    string name = p.getName();
    if(name == "Play!") {
        x = 0;
        y = 0;
    }
}