#include "ofApp.h"

void ofApp::setup() {
    ofxAudioVisualApp::setup();
    
    circleStyles = {"normal", "noise", "volume"};
    currentStyle = circleStyles[0];
    
    for (int i = 0; i < circleStyles.size(); i++){
        ofParameter<bool>* style;
        style = new ofParameter<bool>;
        style->set(circleStyles[i], i==0 ? true : false);
        styleGroup.add(*style);
    }
    
    verticallyCentered = false;
    horizontallyCentered = false;
    
    gui.add(numSpirals.set("Spirals", 5, 1, 10));
    gui.add(spiralRadius.set("Radius", 20, 10, 500));
    gui.add(styleGroup);
    gui.add(verticallyCentered.set("Vertical Center", false));
    gui.add(horizontallyCentered.set("Horizontal Center", false));
    
    
    reinitialize();
    noiseOffset = ofRandom(-100, 100);
    
    ofAddListener(settings.parameterChangedE(), this, &ofApp::onSettingChanged);
    ofAddListener(styleGroup.parameterChangedE(), this, &ofApp::onStyleChanged);
}

void ofApp::draw() {
    ofPushMatrix();
    ofTranslate(xPosition, yPosition);
    ofRotate(theta, 0, 0, 1);
    
    for(int i = 0; i < drawBins.size(); i++) {
        ofPushStyle();
        ofColor col = ofxAudioVisualApp::setColorLerp(i);
//        ofColor col = ofxAudioVisualApp::getColorFromSpectrum(i);
        
        float drawRadius;
        if (currentStyle == "normal"){
            drawRadius = spiralRadius;
        } else if (currentStyle == "noise"){
            drawRadius = spiralRadius * ofNoise((noiseOffset+theta)/100) + spiralRadius*0.25;
        } else if (currentStyle == "volume"){
            drawRadius = ofMap(getAverageVolume(drawBins), 0, 0.008, 0, spiralRadius, true);
        }
        
        if(col.r + col.g + col.b == 0) drawRadius = 0;
        ofSetColor(col);
        ofDrawCircle(0, ofMap(i, 0, drawBins.size(), 0, drawRadius), ofMap(drawBins[i], 0, 0.01, 0, 2, true));
        ofPopStyle();
    }
    ofPopMatrix();
    
    theta += 1.0;
    if(theta >= 360) {
        reinitialize();
        colLow = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(127));
        colHigh = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(127));
        noiseOffset = ofRandom(-100, 100);
    }
    ofxAudioVisualApp::draw();
}

void ofApp::keyPressed(int key) {
    ofxAudioVisualApp::keyPressed(key);
    
    switch (key) {
        case 'h':
            horizontallyCentered = !horizontallyCentered;
            break;
        case 'v':
            verticallyCentered = !verticallyCentered;
            break;
        default:
            break;
    }
}

void ofApp::onSettingChanged(ofAbstractParameter &p){
    string name = p.getName();
    if(name == "Play!") {
        reinitialize();
    }
}

void ofApp::onStyleChanged(ofAbstractParameter &p){
    string name = p.getName();
    
    for (int i = 0; i < circleStyles.size(); i++){
        if (name == circleStyles[i]){
            currentStyle = circleStyles[i];
            break;
        }
    }
    
    for (int i = 0; i < styleGroup.size(); i++){
        string it = styleGroup.getName(i);
        if (name != it){
            styleGroup.get<bool>(circleStyles[i]).setWithoutEventNotifications(false);
        }
    }
}

void ofApp::reinitialize(){
    spiralRadius = ofRandom(300, 500);
    theta = 0.0;
    xPosition = horizontallyCentered ? ofGetWidth()/2 : ofRandom(0, ofGetWidth());
    yPosition = verticallyCentered ? ofGetHeight()/2 : ofRandom(0, ofGetHeight());
}
