#include "Gerhard.h"

void Gerhard::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold, bool symmetrical) {
    ofPushMatrix();
    ofPushStyle();
    
    int binSize = abs(app->endBin - app->startBin);
    for(int i = app->startBin, j = 0; j < binSize; i++, j++){
        ofColor col;
        
        if(drawBins->at(i) > threshold){
            col = app->getColor(i);
        }else{
            col = (0,0,0);
        }
        
        ofSetColor(col);
        if(symmetrical){
            ofDrawCircle(x, ofMap(i, app->startBin, binSize, 0, ofGetHeight()) + ofGetHeight()/2, 2);
            ofDrawCircle(x, ofGetHeight()/2 - ofMap(i, app->startBin, binSize, 0, ofGetHeight()), 2);
        }else{
            ofDrawCircle(x, ofMap(i, app->startBin, binSize, 0, ofGetHeight()), 2);
        }
    }
    
//    for(int i = 0; i < drawBins->size(); i++) {
//        ofColor col;
//        if(drawBins->at(i) > threshold){
//            col = app->getColor(i);
//        }else{
//            col = (0,0,0);
//        }
//        
//        ofSetColor(col);
//        if(symmetrical){
//            ofDrawCircle(x, ofMap(i, 0, drawBins->size(), 0, ofGetHeight()) + ofGetHeight()/2, 2);
//            ofDrawCircle(x, ofGetHeight()/2 - ofMap(i, 0, drawBins->size(), 0, ofGetHeight()), 2);
//        }else{
//            ofDrawCircle(x, ofMap(i, 0, drawBins->size(), 0, ofGetHeight()), 2);
//        }
//    }
    
    ofPopStyle();
    ofPopMatrix();
    
    x += 1 * app->drawSpeed;
    if(x > ofGetWidth())
        x = 0;
}