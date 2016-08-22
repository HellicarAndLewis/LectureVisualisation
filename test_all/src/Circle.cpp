#include "Circle.h"

void Circle::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold){
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotate(theta, 0, 0, 1);
    
    int binSize = abs(app->endBin - app->startBin);
    for(int i = app->startBin, j = 0; j < binSize; i++, j++) {
        ofColor col;
        if(drawBins->at(i) > threshold){
            col = app->getColor(i);
        }else{
            col = (0,0,0);
        }
        ofSetColor(col);
        ofDrawCircle(0, ofMap(i, app->startBin, binSize, 0, 500, true), 2);
    }
    
//    for(int i = 0; i < drawBins->size(); i++) {
//        ofSetColor(app->getColor(i));
//        ofDrawCircle(0, ofMap(i, 0, drawBins->size()/8, 0, 500)/8, ofMap(drawBins->at(i), 0, 0.01, 0, 2, true));
//    }
    
    ofPopMatrix();
    
    theta += 0.1 * app->drawSpeed;
}