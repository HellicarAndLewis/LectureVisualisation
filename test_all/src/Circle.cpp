#include "Circle.h"

void Circle::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold){
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotate(theta, 0, 0, 1);
    for(int i = 0; i < drawBins->size(); i++) {
        ofSetColor(app->getColor(i));
        ofDrawCircle(0, ofMap(i, 0, drawBins->size(), 0, 500), ofMap(drawBins->at(i), 0, 0.01, 0, 2, true));
    }
    ofPopMatrix();
    theta += 0.1;
}