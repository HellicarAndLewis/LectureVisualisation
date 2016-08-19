#include "ofApp.h"

//----------------------- App -----------------------------------------------

void ofApp::setup() {
    ofxAudioVisualApp::setup();
    
    x = 0;
    
    ofAddListener(settings.parameterChangedE(), this, &ofApp::onSettingChanged);
    history.setup(fft);
}

void ofApp::draw() {
    ofxAudioVisualApp::draw();

//    gerhard.draw(this, &drawBins, threshold, symmetrical);
//    circle.draw(this, &drawBins, threshold);
//    history.draw(this, &drawBins, threshold);
    gStrip.draw(this, &drawBins, threshold, symmetrical);
}

//----------------------- GUI -----------------------------------------------

void ofApp::setupGui(){
    ofxAudioVisualApp::setupGui();
    
    gui2.add(threshold.set("Threshold", 0.0038, 0, 0.009));
    gui2.add(symmetrical.set("Symmetrical", true));
}

void ofApp::drawGui(ofEventArgs & args){
    ofxAudioVisualApp::drawGui(args);
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
        gerhard.x = 0;
    }
}