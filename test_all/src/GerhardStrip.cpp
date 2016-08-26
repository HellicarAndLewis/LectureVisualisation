#include "GerhardStrip.h"

void GerhardStrip::draw(ofxAudioVisualApp* app, vector<float>* drawBins, float threshold, bool symmetrical){
    int symmetryFactor = symmetrical ? 2 : 1;
    
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(0, ofGetHeight() * 0.1 * y);
    
    int binSize = abs(app->endBin - app->startBin);
    for(int i = app->startBin, j = 0; j < binSize * (0.1/symmetryFactor); i++, j++) {
        ofColor col;
        if(drawBins->at(i) > threshold){
            col = app->getColor(i);
        }else{
            col = (0,0,0);
        }
        
        ofSetColor(col);
        if(symmetrical){
            ofDrawCircle(x, ofMap(i, app->startBin, app->endBin, 0, ofGetHeight(), true) + (ofGetHeight() * 0.05), 2);
            ofDrawCircle(x, (ofGetHeight() * 0.05) - ofMap(i, app->startBin, app->endBin, 0, ofGetHeight(), true) , 2);
        }else{
            ofDrawCircle(x, ofMap(i, app->startBin, app->endBin, 0, ofGetHeight(), true), 2);
        }
    }

    
//    for(int i = 0; i < drawBins->size() * (0.1/symmetryFactor); i++) {
//        ofColor col;
//        if(drawBins->at(i) > threshold){
//            col = app->getColor(i);
//        }else{
//            col = (0,0,0);
//        }
//        
//        ofSetColor(col);
//        if(symmetrical){
//            ofDrawCircle(x, ofMap(i, 0, drawBins->size(), 0, ofGetHeight()) + (ofGetHeight() * 0.05), 2);
//            ofDrawCircle(x, (ofGetHeight() * 0.05) - ofMap(i, 0, drawBins->size(), 0, ofGetHeight()) , 2);
//        }else{
//            ofDrawCircle(x, ofMap(i, 0, drawBins->size(), 0, ofGetHeight()), 2);
//        }
//    }
    
    ofPopStyle();
    ofPopMatrix();
    
    x += 1 * app->drawSpeed;
    if(x > ofGetWidth()) {
        x = 0;
        y++;
        
        if(y > 9){
            y = 0;
        }
    }
}

void GerhardStrip::reset(){
    x = 0;
    y = 0;
}