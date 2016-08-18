#include "ofApp.h"

void ofApp::setup() {
    ofxAudioVisualApp::setup();
    gui.add(threshold.set("Threshold", 0.001, 0, 0.009));
    
    y = 10;
    size = 2;
    
    ofAddListener(settings.parameterChangedE(), this, &ofApp::onSettingChanged);
}

void ofApp::draw() {
    ofxAudioVisualApp::draw();

    theta = 0;
    
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    for(int i = 0; i < drawBins.size(); i++) {
        ofPushMatrix();
        ofRotate(theta);
        
        ofColor col;
        if(drawBins[i] > threshold){
            col = ofxAudioVisualApp::getColorFromSpectrum(i);
        }else{
            col = (0,0,0);
        }
        
        ofSetColor(col);
        ofDrawCircle(0, y, size);
        
        ofPopMatrix();
        theta = i * 360/drawBins.size();
    }
    ofPopStyle();
    ofPopMatrix();
    
    y += 0.1;
    size += 0.00095;
    if(y > ofGetHeight()/2){
        y = 10;
        size = 0;
        ofSetColor(0);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    }
}

void ofApp::onSettingChanged(ofAbstractParameter &p){
    string name = p.getName();
    if(name == "Play!") {
        y = 10;
        size = 0;
    }
}