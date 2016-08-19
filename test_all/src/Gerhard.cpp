#include "Gerhard.h"

void Gerhard::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold, bool symmetrical) {
    float scaleFactor = 1;
    
    ofPushMatrix();
    ofPushStyle();
    for(int i = 0; i < drawBins->size(); i++) {
        ofColor col;
        if(drawBins->at(i) > threshold){
            col = app->getColor(i);
        }else{
            col = (0,0,0);
        }
        
        ofSetColor(col);
        if(symmetrical){
            ofDrawCircle(x, ofMap(i, 0, drawBins->size(), 0, ofGetHeight() * scaleFactor) + ofGetHeight()/2, 2);
            ofDrawCircle(x, ofGetHeight()/2 - ofMap(i, 0, drawBins->size(), 0, ofGetHeight() * scaleFactor), 2);
        }else{
            ofDrawCircle(x, ofMap(i, 0, drawBins->size(), 0, ofGetHeight() * scaleFactor), 2);
        }
    }
    ofPopStyle();
    ofPopMatrix();
    
    x += 1;
    if(x > ofGetWidth())
        x = 0;
}