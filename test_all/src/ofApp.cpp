#include "ofApp.h"

//----------------------- App -----------------------------------------------

void ofApp::setup() {
    ofxAudioVisualApp::setup();
    
    ofAddListener(settings.parameterChangedE(), this, &ofApp::onSettingChanged);
    
    isGerhard.set("Gerhard", true);
    isGerhardStrip.set("Gerhard Strip", false);
    isCircle.set("Circle", false);
    isHistory.set("History", false);
    isStream.set("Stream", false);
    
    visGroup.push_back(&isGerhard);
    visGroup.push_back(&isGerhardStrip);
    visGroup.push_back(&isCircle);
    visGroup.push_back(&isHistory);
    visGroup.push_back(&isStream);
    
    for (auto vis : visGroup){
        visualizations.add(*vis);
    }
    
    gui2.add(visualizations);
    ofAddListener(visualizations.parameterChangedE(), this, &ofApp::onVisualizationChanged);
    
    ofAddListener(startEndBin.parameterChangedE(), this, &ofApp::onBinSizeChanged);
    
    reset();
    resetting = false;
    history.setup(fft);
    stream.setup();
}

void ofApp::draw() {
    ofxAudioVisualApp::draw();
    
    if (resetting){
        ofPushStyle();
        ofSetColor(0);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        ofPopStyle();
        resetting = false;
    }
    
    if (isGerhard){
        gerhard.draw(this, &drawBins, threshold, symmetrical);
    }else if (isCircle){
        circle.draw(this, &drawBins, threshold);
    }else if (isHistory){
        history.draw(this, &drawBins, threshold);
    }else if (isGerhardStrip){
        gStrip.draw(this, &drawBins, threshold, symmetrical);
    }else if (isStream){
        stream.draw(this, &drawBins, threshold);
    }
}

//----------------------- GUI -----------------------------------------------

void ofApp::setupGui(){
    ofxAudioVisualApp::setupGui();
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
        reset();
    }
}

void ofApp::onVisualizationChanged(ofAbstractParameter &p){
    string name = p.getName();
    
    for (int i = 0; i < visGroup.size(); i++){
        if (visGroup[i]->getName() == name){
            visGroup[i]->setWithoutEventNotifications(true);
        }else{
            visGroup[i]->setWithoutEventNotifications(false);
        }
    }
    
    reset();
}

void ofApp::onBinSizeChanged(ofAbstractParameter &p){
    history.resetMesh();
}

void ofApp::reset(){
    x = 0;
    gerhard.x = 0;
    circle.theta = -90;
    gStrip.setXY(0, 0);
    stream.x = 0;
    
    resetting = true;
}